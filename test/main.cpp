// steamprot.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctime>
#include <Windows.h>

#include "../src/libSteamProt.h"

#if defined(_WIN32) || defined(_WIN64)
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#endif

#define BUFLEN 1500  //Max length of buffer
#define PORT 27015   //The port on which to listen for incoming data

int UDPServer();

A2S_INFO Info;
A2S_PLAYER Player;
A2S_RULES Rules;

void FillInfo(WRITE_BUF* pWriteBuf) {
    A2S_INFO* pInfo;
    pInfo = &Info;
    A2S_INFO_INIT(pInfo);

    A2S_INFO_setProtocol(pInfo, 0x11);
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
}

float Duration = 0.f;

void FillPlayer(WRITE_BUF* pWriteBuf) {
    A2S_PLAYER* pPlayer;
    pPlayer = &Player;
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
}

void FillRules(WRITE_BUF* pWriteBuf) {
    A2S_RULES* pRules;
    pRules = &Rules;
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
}

int main(int argc, const char* argv[])
{
    // Start UDP Server
    UDPServer();

	return 0;
}

int UDPServer() {
    SOCKET s;
    struct sockaddr_in server, si_other;
    int slen , recv_len;
    char buf[BUFLEN];
    WSADATA wsa;

    srand((unsigned int) time (NULL));

    slen = sizeof(si_other) ;

    //Initialise winsock
    printf("\nInitialising Winsock...");
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        exit(EXIT_FAILURE);
    }
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
    server.sin_port = htons( PORT );

    //Bind
    if( bind(s ,(struct sockaddr *)&server , sizeof(server)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
        exit(EXIT_FAILURE);
    }
    puts("Bind done");

    WRITE_BUF WriteBuf;
    WRITE_BUF_INIT(&WriteBuf);

    SP_Protocol_Callbacks Callbacks;
    Callbacks.FillInfo = FillInfo;
    Callbacks.FillPayer = FillPlayer;
    Callbacks.FillRules = FillRules;

    //keep listening for data
    while(1)
    {
        printf("Waiting for data...");
        fflush(stdout);

        //clear the buffer by filling null, it might have previously received data
        memset(buf,'\0', BUFLEN);

        //try to receive some data, this is a blocking call
        if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen)) == SOCKET_ERROR)
        {
            printf("recvfrom() failed with error code : %d" , WSAGetLastError());
            exit(EXIT_FAILURE);
        }

        //print details of the client/peer and the data received
        printf("Received packet from %s:%d\n", inet_ntoa(si_other.sin_addr), ntohs(si_other.sin_port));
        printf("Data: %s\n" , buf);

        if(HandlePacket(&WriteBuf, (byte*)buf, recv_len, Callbacks) == STEAMPROT_OK) {
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
