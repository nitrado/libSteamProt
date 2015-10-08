// steamprot.cpp : Defines the entry point for the console application.
//

#include <winsock2.h>
#include <Windows.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctime>

#include "../../src/libSteamProt.h"

#if defined(_WIN32) || defined(_WIN64)
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#endif

#define DEFAULT_BUFLEN 1500
#define DEFAULT_PORT 27015

DWORD UDPServer (LPVOID lpdwThreadParam );

void WINAPI FillInfo(WRITE_BUF* pWriteBuf) {
    A2S_INFO* pInfo = A2S_INFO_create();
    A2S_INFO_INIT(pInfo);

    A2S_INFO_setProtocol(pInfo, 0x2F);
    A2S_INFO_setName(pInfo, "Sample Server");
    A2S_INFO_setMap(pInfo, "demo");
    A2S_INFO_setFolder(pInfo, "csgo");
    A2S_INFO_setGame(pInfo, "Counter-Strike: Global Offensive");
    A2S_INFO_setID(pInfo, 730);
    A2S_INFO_setPlayers(pInfo, 0);
    A2S_INFO_setMaxPlayers(pInfo, 64);
    A2S_INFO_setBots(pInfo, 0);
    A2S_INFO_setServertype(pInfo, SP_SERVERTYPE_DEDICATED);
    A2S_INFO_setEnvironment(pInfo, SP_ENVIRONMENT_LINUX);
    A2S_INFO_setVisibility(pInfo, 0);
    A2S_INFO_setVAC(pInfo, 1);
    A2S_INFO_setVersion(pInfo, "1.34.9.2");
    A2S_INFO_setEDF(pInfo, SP_EDF_KEYWORDS | SP_EDF_GAMEID | SP_EDF_STEAMID | SP_EDF_PORT);
    A2S_INFO_setPort(pInfo, 27015);
    A2S_INFO_setKeywords(pInfo, "CSDM,FFA,mousesports,mouz,secure");
    A2S_INFO_setSteamID(pInfo, 730);
    A2S_INFO_setGameID(pInfo, 730);

    A2S_INFO_WRITE(pInfo, pWriteBuf);
    A2S_INFO_destory(pInfo);
}

float Duration = 0.f;

void WINAPI FillPlayer(WRITE_BUF* pWriteBuf) {
    A2S_PLAYER* pPlayer = A2S_PLAYER_create();
    A2S_PLAYER_INIT(pPlayer);

    A2S_PLAYER_setPlayerCount(pPlayer, 10);

    for(unsigned char i = 0; i < A2S_PLAYER_getPlayerCount(pPlayer); i++) {
        PLAYER_STRUCT* pPlayerStruct = &pPlayer->m_Players[i];
        char NAME[255];
        sprintf(NAME, "player_%d", i);
        PLAYER_STRUCT_setName(pPlayerStruct, NAME);
        PLAYER_STRUCT_setDuration(pPlayerStruct, (Duration+=0.1f));
        PLAYER_STRUCT_setScore(pPlayerStruct, i);
    }

    A2S_PLAYER_WRITE(pPlayer, pWriteBuf);
    A2S_PLAYER_destory(pPlayer);
}

void WINAPI FillRules(WRITE_BUF* pWriteBuf) {
    A2S_RULES* pRules = A2S_RULES_create();
    A2S_RULES_INIT(pRules);

    A2S_RULES_setRuleCount(pRules, 177);

    for(unsigned char i = 0; i < A2S_RULES_getRuleCount(pRules); i++) {
        RULE_STRUCT* pRuleStruct = &pRules->m_Rules[i];
        char KEY[255], VALUE[255];
        sprintf(KEY, "key_%d", i);
        sprintf(VALUE, "value_%d", (rand()%(100 - 1)) + 1);
        RULE_STRUCT_setName(pRuleStruct, KEY);
        RULE_STRUCT_setValue(pRuleStruct, VALUE);
    }

    A2S_RULES_WRITE(pRules, pWriteBuf);
    A2S_RULES_destory(pRules);
}

const char* WINAPI HandleRconBody(const char* Body) {
    if(strncmp("status", Body, SP_STRING_LENGTH) == 0) {
        return "status\n" \
            "hostname: test\n" \
            "map: de_dust\n";
    }
    return "none";
}

char WINAPI IsRconPasswordValid(const char* Password) {
    return (strcmp(Password, "testrcon") == 0);    
}

DWORD HandleClient (LPVOID lpdwThreadParam ) {
    int iResult;
    int iSendResult;
    char recvbuf[DEFAULT_BUFLEN];
    int recvbuflen = DEFAULT_BUFLEN;

    WRITE_BUF WriteBuf;

    RCON_DATA* pRconData = RCON_DATA_create();

    SOCKET ClientSocket = *((int*)lpdwThreadParam);

    // Receive until the peer shuts down the connection
    do {
        iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);
        if (iResult > 0) {
            printf("Bytes received: %d\n", iResult);

            WRITE_BUF_INIT(&WriteBuf);
            if(HandleRconPacket(&WriteBuf, (unsigned char*)recvbuf, iResult, IsRconPasswordValid, HandleRconBody, pRconData) == STEAMPROT_OK) {
                for(byte i = 0; i < WRITE_BUF_getCount(&WriteBuf); i++) {
                    iSendResult = send( ClientSocket, (const char*)WriteBuf.m_Buffer[i], WriteBuf.m_Size[i], 0 );
                    if (iSendResult == SOCKET_ERROR) {
                        printf("send failed with error: %d\n", WSAGetLastError());
                        closesocket(ClientSocket);
                        return 1;
                    }
                    printf("Bytes sent: %d\n", iSendResult);
                }
            }

        // Echo the buffer back to the sender
            
        }
        else if (iResult == 0)
            printf("Connection closing...\n");
        else  {
            printf("recv failed with error: %d\n", WSAGetLastError());
            closesocket(ClientSocket);
            return 1;
        }
    } while (iResult > 0);

    // shutdown the connection since we're done
    iResult = shutdown(ClientSocket, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        printf("shutdown failed with error: %d\n", WSAGetLastError());
        closesocket(ClientSocket);
        return 1;
    }

    // cleanup
    closesocket(ClientSocket);
    RCON_DATA_destory(pRconData);
}

int main(void) 
{
    WSADATA wsaData;
    int iResult;

    SOCKET ListenSocket = INVALID_SOCKET;
    SOCKET ClientSocket = INVALID_SOCKET;

    struct addrinfo *result = NULL;
    //struct addrinfo hints;
    struct sockaddr_in server;
    
    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed with error: %d\n", iResult);
        return 1;
    }

    CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&UDPServer, NULL, 0, 0);
    
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( DEFAULT_PORT );

    // Create a SOCKET for connecting to server
    ListenSocket = socket(AF_INET , SOCK_STREAM , 0 );
    if (ListenSocket == INVALID_SOCKET) {
        printf("socket failed with error: %ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }

    // Setup the TCP listening socket
    iResult = bind( ListenSocket, (struct sockaddr *)&server , sizeof(server));
    if (iResult == SOCKET_ERROR) {
        printf("bind failed with error: %d\n", WSAGetLastError());
        freeaddrinfo(result);
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    freeaddrinfo(result);

    iResult = listen(ListenSocket, SOMAXCONN);
    if (iResult == SOCKET_ERROR) {
        printf("listen failed with error: %d\n", WSAGetLastError());
        closesocket(ListenSocket);
        WSACleanup();
        return 1;
    }

    while(ClientSocket = accept(ListenSocket, NULL, NULL)) {
        if (ClientSocket == INVALID_SOCKET) {
            printf("accept failed with error: %d\n", WSAGetLastError());
            closesocket(ListenSocket);
            WSACleanup();
            break;
        }

        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)&HandleClient, &ClientSocket, 0, 0);
    }

    return 0;
}

DWORD UDPServer (LPVOID lpdwThreadParam ) {
    SOCKET s;
    struct sockaddr_in server, si_other;
    int slen , recv_len;
    char buf[DEFAULT_BUFLEN];

    srand((unsigned int) time (NULL));

    slen = sizeof(si_other) ;

    printf("Initialised.\n");

    //Create a socket
    if((s = socket(AF_INET , SOCK_DGRAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
    printf("Socket created.\n");

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons( DEFAULT_PORT );

    //Bind
    if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    puts("Bind done");

    WRITE_BUF WriteBuf;
    WRITE_BUF_INIT(&WriteBuf);

    //printf("%d %d\n", sizeof(WRITE_BUF), sizeof(SP_Protocol_Callbacks));

    //keep listening for data
    while(1)
    {
        //printf("Waiting for data...");
        fflush(stdout);

        //clear the buffer by filling null, it might have previously received data
        memset(buf,'\0', DEFAULT_BUFLEN);

        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, DEFAULT_BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code : %d" , WSAGetLastError());
            exit(EXIT_FAILURE);
        }

        //print details of the client/peer and the data received
        //printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        //printf("Data: %s\n" , buf);

        if(HandlePacket(&WriteBuf, (byte*)buf, recv_len, FillInfo, FillPlayer, FillRules) == STEAMPROT_OK) {
            for(byte i = 0; i < WRITE_BUF_getCount(&WriteBuf); i++) {
                if (sendto(s, (const char*)WriteBuf.m_Buffer[i], WriteBuf.m_Size[i], 0, (struct sockaddr*) &si_other, slen) == SOCKET_ERROR)
                {
                    printf("sendto() failed with error code : %d" , WSAGetLastError());
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    closesocket(s);
    WSACleanup();

    return 0;
}
