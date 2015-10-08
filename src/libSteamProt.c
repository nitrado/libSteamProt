#include "libSteamProt.h"
#include "../bzlib/bzlib.h"

#if defined(_WIN32) || defined(_WIN64)
#pragma comment(lib,"ws2_32.lib") //Winsock Library
#endif

#define safe_string_copy(dst, src) \
    memset(dst, 0, SP_STRING_LENGTH); \
    strncpy(dst, src, SP_STRING_LENGTH-1);

#define safe_string_append(dst, src) \
    { \
    int StringLength = strnlen(src, SP_STRING_LENGTH); \
    memcpy(&dst[Pos], src, StringLength); \
    dst[Pos + StringLength] = 0; \
    Pos += StringLength + 1; \
    }

RCON_DATA* SP_API RCON_DATA_create() {
    RCON_DATA* pRconData = (RCON_DATA*)malloc(sizeof(RCON_DATA));
    memset(pRconData, 0, sizeof(RCON_DATA));
    pRconData->m_LoggedIn = 0;
    pRconData->m_pCommandQueue = NULL;
    return pRconData;
}

/*RCON_COMMAND* SP_API RCON_COMMAND_create(RCON_DATA* pRconData, int ID, const char* Request) {
    struct RCON_COMMAND* pRconCommand;

    pRconCommand = (struct RCON_COMMAND*)malloc(sizeof(RCON_COMMAND));
    memset(pRconCommand, 0, sizeof(RCON_COMMAND));
    
    pRconCommand->m_ID = ID;
    pRconCommand->m_State = SP_RCON_COMMAND_STATE_NONE;
    safe_string_copy(pRconCommand->m_Request, Request);

    if(!pRconData->m_pCommandQueue) {
        pRconData->m_pCommandQueue = pRconCommand;
    } else {
        pRconCommand->m_pNext = pRconData->m_pCommandQueue;
        pRconData->m_pCommandQueue = pRconCommand;
    }
}

void SP_API RCON_DATA_destory(RCON_DATA* pRconData, RCON_COMMAND* pRconCommand) {
    struct RCON_COMMAND* pRconCommandIterator;
    
    pRconCommandIterator = pRconData->m_pCommandQueue;

    do {
        // Root
        if(pRconCommandIterator == pRconData->m_pCommandQueue && pRconCommandIterator == pRconCommand) {
            pRconData->m_pCommandQueue = pRconData->m_pCommandQueue->m_pNext;
            free(pRconCommand);
            return;
        }

        if(pRconCommandIterator->m_pNext && pRconCommandIterator->m_pNext == pRconCommand) {
            pRconCommandIterator->m_pNext = pRconCommandIterator->m_pNext->m_pNext;
        }

        pRconCommandIterator = pRconCommand->m_pNext;
    } while(pRconCommandIterator);
}*/

void SP_API RCON_DATA_destory(RCON_DATA* pRconData) {
    if(pRconData)
        free(pRconData);
}

WRITE_BUF* SP_API WRITE_BUF_create() {
    return (WRITE_BUF*)malloc(sizeof(WRITE_BUF));
}

A2S_INFO* SP_API A2S_INFO_create() {
    return (A2S_INFO*)malloc(sizeof(A2S_INFO));
}

A2S_PLAYER* SP_API A2S_PLAYER_create() {
    return (A2S_PLAYER*)malloc(sizeof(A2S_PLAYER));
}

A2S_RULES* SP_API A2S_RULES_create() {
    return (A2S_RULES*)malloc(sizeof(A2S_RULES));
}

void SP_API A2S_INFO_destory(A2S_INFO* pInfo) {
    if(pInfo)
        free(pInfo);
}

void SP_API WRITE_BUF_destroy(WRITE_BUF* pWriteBuf) {
    if(pWriteBuf)
        free(pWriteBuf);
}

void SP_API A2S_PLAYER_destory(A2S_PLAYER* pPlayer) {
    if(pPlayer)
        free(pPlayer);
}

void SP_API A2S_RULES_destory(A2S_RULES* pRules) {
    if(pRules)
        free(pRules);
}

PLAYER_STRUCT* SP_API A2S_PLAYER_GET(A2S_PLAYER* pPlayer, unsigned char Index) {
    return &pPlayer->m_Players[Index];
}

RULE_STRUCT* SP_API A2S_RULES_GET(A2S_RULES* pRules, unsigned char Index) {
    return &pRules->m_Rules[Index];
}

void SP_API WRITE_BUF_setCount(WRITE_BUF* pWriteBuf, unsigned char Count) {
    pWriteBuf->m_Count = Count;
}

void SP_API WRITE_BUF_setSize(WRITE_BUF* pWriteBuf, unsigned char Index, short Size) {
    pWriteBuf->m_Size[Index] = Size;
}

unsigned char SP_API WRITE_BUF_getCount(WRITE_BUF* pWriteBuf) {
    return pWriteBuf->m_Count;
}

short SP_API WRITE_BUF_getSize(WRITE_BUF* pWriteBuf, unsigned char Index) {
    return pWriteBuf->m_Size[Index];
}

void SP_API A2S_INFO_setPort(A2S_INFO* pInfo, short Port) {
    pInfo->m_Port = Port;
}

short SP_API A2S_INFO_getPort(A2S_INFO* pInfo) {
    return pInfo->m_Port;
}

void SP_API A2S_INFO_setSteamID(A2S_INFO* pInfo, long long SteamID) {
    pInfo->m_SteamID = SteamID;
}

long long SP_API A2S_INFO_getSteamID(A2S_INFO* pInfo) {
    return pInfo->m_SteamID;
}

void SP_API A2S_INFO_setSourceTV_Port(A2S_INFO* pInfo, short Port) {
    pInfo->m_SourceTV_Port = Port;
}

short SP_API A2S_INFO_getSourceTV_Port(A2S_INFO* pInfo) {
    return pInfo->m_SourceTV_Port;
}

void SP_API A2S_INFO_setSourceTV_Name(A2S_INFO* pInfo, const char* Name) {
    safe_string_copy(pInfo->m_SourceTV_Name, Name);
}

const char* SP_API A2S_INFO_getSourceTV_Name(A2S_INFO* pInfo) {
    return pInfo->m_SourceTV_Name;
}

void SP_API A2S_INFO_setKeywords(A2S_INFO* pInfo, const char* Keywords) {
    safe_string_copy(pInfo->m_Keywords, Keywords);
}

const char* SP_API A2S_INFO_getKeywords(A2S_INFO* pInfo) {
    return pInfo->m_Keywords;
}

void SP_API A2S_INFO_setGameID(A2S_INFO* pInfo, long long GameID) {
    pInfo->m_GameID = GameID;
}

long long SP_API A2S_INFO_getGameID(A2S_INFO* pInfo) {
    return pInfo->m_GameID;
}

void SP_API A2S_INFO_setProtocol(A2S_INFO* pInfo, unsigned char Protocol) {
    pInfo->m_Protocol = Protocol;
}

unsigned char SP_API A2S_INFO_getProtocol(A2S_INFO* pInfo) {
    return pInfo->m_Protocol;
}

void SP_API A2S_INFO_setName(A2S_INFO* pInfo, const char* Name) {
    safe_string_copy(pInfo->m_Name, Name);
}

const char* SP_API A2S_INFO_getName(A2S_INFO* pInfo) {
    return pInfo->m_Name;
}

void SP_API A2S_INFO_setMap(A2S_INFO* pInfo, const char* Map) {
    safe_string_copy(pInfo->m_Map, Map);
}

const char* SP_API A2S_INFO_getMap(A2S_INFO* pInfo) {
    return pInfo->m_Map;
}

void SP_API A2S_INFO_setFolder(A2S_INFO* pInfo, const char* Folder) {
    safe_string_copy(pInfo->m_Folder, Folder);
}

const char* SP_API A2S_INFO_getFolder(A2S_INFO* pInfo) {
    return pInfo->m_Folder;
}

void SP_API A2S_INFO_setGame(A2S_INFO* pInfo, const char* Game) {
    safe_string_copy(pInfo->m_Game, Game);
}

const char* SP_API A2S_INFO_getGame(A2S_INFO* pInfo) {
    return pInfo->m_Game;
}

void SP_API A2S_INFO_setID(A2S_INFO* pInfo, short ID) {
    pInfo->m_ID = ID;
}

short SP_API A2S_INFO_getID(A2S_INFO* pInfo) {
    return pInfo->m_ID;
}

void SP_API A2S_INFO_setPlayers(A2S_INFO* pInfo, unsigned char Players) {
    pInfo->m_Players = Players;
}

unsigned char SP_API A2S_INFO_getPlayers(A2S_INFO* pInfo) {
    return pInfo->m_Players;
}

void SP_API A2S_INFO_setMaxPlayers(A2S_INFO* pInfo, unsigned char MaxPlayers) {
    pInfo->m_MaxPlayers = MaxPlayers;
}

unsigned char SP_API A2S_INFO_getMaxPlayers(A2S_INFO* pInfo) {
    return pInfo->m_MaxPlayers;
}

void SP_API A2S_INFO_setBots(A2S_INFO* pInfo, unsigned char Bots) {
    pInfo->m_Bots = Bots;
}

unsigned char SP_API A2S_INFO_getBots(A2S_INFO* pInfo) {
    return pInfo->m_Bots;
}

void SP_API A2S_INFO_setServertype(A2S_INFO* pInfo, unsigned char Servertype) {
    pInfo->m_Servertype = Servertype;
}

unsigned char SP_API A2S_INFO_getServertype(A2S_INFO* pInfo) {
    return pInfo->m_Servertype;
}

void SP_API A2S_INFO_setEnvironment(A2S_INFO* pInfo, unsigned char Environment) {
    pInfo->m_Environment = Environment;
}

unsigned char SP_API A2S_INFO_getEnvironment(A2S_INFO* pInfo) {
    return pInfo->m_Environment;
}

void SP_API A2S_INFO_setVisibility(A2S_INFO* pInfo, unsigned char Visibility) {
    pInfo->m_Visibility = Visibility;
}

unsigned char SP_API A2S_INFO_getVisibility(A2S_INFO* pInfo) {
    return pInfo->m_Visibility;
}

void SP_API A2S_INFO_setVAC(A2S_INFO* pInfo, unsigned char VAC) {
    pInfo->m_VAC = VAC;
}

unsigned char SP_API A2S_INFO_getVAC(A2S_INFO* pInfo) {
    return pInfo->m_VAC;
}

void SP_API A2S_INFO_setVersion(A2S_INFO* pInfo, const char* Version) {
    safe_string_copy(pInfo->m_Version, Version);
}

const char* SP_API A2S_INFO_getVersion(A2S_INFO* pInfo) {
    return pInfo->m_Version;
}

void SP_API A2S_INFO_setEDF(A2S_INFO* pInfo, unsigned char EDF) {
    pInfo->m_EDF = EDF;
}

unsigned char SP_API A2S_INFO_getEDF(A2S_INFO* pInfo) {
    return pInfo->m_EDF;
}

void SP_API PLAYER_STRUCT_setName(PLAYER_STRUCT* pPlayerStruct, const char* Name) {
    safe_string_copy(pPlayerStruct->m_Name, Name);
}

const char* SP_API PLAYER_STRUCT_getName(PLAYER_STRUCT* pPlayerStruct) {
    return pPlayerStruct->m_Name;
}

void SP_API PLAYER_STRUCT_setScore(PLAYER_STRUCT* pPlayerStruct, long Score) {
    pPlayerStruct->m_Score = Score;
}

long SP_API PLAYER_STRUCT_getScore(PLAYER_STRUCT* pPlayerStruct) {
    return pPlayerStruct->m_Score;
}

void SP_API PLAYER_STRUCT_setDuration(PLAYER_STRUCT* pPlayerStruct, float Duration) {
    pPlayerStruct->m_Duration = Duration;
}

float SP_API PLAYER_STRUCT_getDuration(PLAYER_STRUCT* pPlayerStruct) {
    return pPlayerStruct->m_Duration;
}

void SP_API RULE_STRUCT_setName(RULE_STRUCT* pRuleStruct, const char* Name) {
    safe_string_copy(pRuleStruct->m_Name, Name);
}

const char* SP_API RULE_STRUCT_getName(RULE_STRUCT* pRuleStruct) {
    return pRuleStruct->m_Name;
}

void SP_API RULE_STRUCT_setValue(RULE_STRUCT* pRuleStruct, const char* Value) {
    safe_string_copy(pRuleStruct->m_Value, Value);
}

const char* SP_API RULE_STRUCT_getValue(RULE_STRUCT* pRuleStruct) {
    return pRuleStruct->m_Value;
}

void SP_API A2S_RULES_setRuleCount(A2S_RULES* pRules, short RuleCount) {
    pRules->m_RuleCount = RuleCount;
}

short SP_API A2S_RULES_getRuleCount(A2S_RULES* pRules) {
    return pRules->m_RuleCount;
}

void SP_API A2S_PLAYER_setPlayerCount(A2S_PLAYER* pPlayer, unsigned char PlayerCount) {
    pPlayer->m_PlayerCount = PlayerCount;
}

unsigned char SP_API A2S_PLAYER_getPlayerCount(A2S_PLAYER* pPlayer) {
    return pPlayer->m_PlayerCount;
}

void SP_API SPLIT_STRUCT_setID(SPLIT_STRUCT* pSplitStruct, long ID) {
    pSplitStruct->m_ID |= (ID & 0x7FFFFFFFF);
}

void SP_API SPLIT_STRUCT_setCompressed(SPLIT_STRUCT* pSplitStruct) {
    pSplitStruct->m_ID |= 0x80000000;
}

unsigned char SP_API SPLIT_STRUCT_isCompressed(SPLIT_STRUCT* pSplitStruct) {
    return !!(pSplitStruct->m_ID & 0x80000000);
}

long SP_API SPLIT_STRUCT_getID(SPLIT_STRUCT* pSplitStruct) {
    return pSplitStruct->m_ID;
}

void SP_API SPLIT_STRUCT_setTotal(SPLIT_STRUCT* pSplitStruct, unsigned char Total) {
    pSplitStruct->m_Total = Total;
}

unsigned char SP_API SPLIT_STRUCT_getTotal(SPLIT_STRUCT* pSplitStruct) {
    return pSplitStruct->m_Total;
}

unsigned char SP_API SPLIT_STRUCT_getNumber(SPLIT_STRUCT* pSplitStruct) {
    return pSplitStruct->m_Number;
}

short SP_API SPLIT_STRUCT_getSize(SPLIT_STRUCT* pSplitStruct) {
    return pSplitStruct->m_Size;
}

void SP_API SPLIT_STRUCT_setNumber(SPLIT_STRUCT* pSplitStruct, unsigned char Number) {
    pSplitStruct->m_Number = Number;
}

void SP_API SPLIT_STRUCT_setSize(SPLIT_STRUCT* pSplitStruct, short Size) {
    pSplitStruct->m_Size = Size;
}

void SP_API WRITE_BUF_INIT(WRITE_BUF* pWriteBuf) {
    memset(pWriteBuf, 0, sizeof(WRITE_BUF));
}

void SP_API A2S_RULES_INIT(A2S_RULES* pRules) {
    memset(pRules, 0, sizeof(A2S_RULES));
}

void SP_API SPLIT_STRUCT_INIT(SPLIT_STRUCT* pSplit) {
    memset(pSplit, 0, sizeof(SPLIT_STRUCT));
}

int SP_API SPLIT_STRUCT_WRITE(SPLIT_STRUCT* pSplit, unsigned char* pBuf, int* pBufLen) {
    int Pos = 0;
    long Header, ID;
    short Size;

    Header = htonl(0xFEFFFFFF);
    memcpy(&pBuf[Pos], &Header, sizeof(Header));
    Pos += 4;
    ID = SPLIT_STRUCT_getID(pSplit);
    memcpy(&pBuf[Pos], &ID, sizeof(ID));
    Pos += 4;
    pBuf[Pos++] = SPLIT_STRUCT_getTotal(pSplit);
    pBuf[Pos++] = SPLIT_STRUCT_getNumber(pSplit);
    if(!SPLIT_STRUCT_isCompressed(pSplit)) {
        Size = SPLIT_STRUCT_getSize(pSplit);
        memcpy(&pBuf[Pos], &Size, sizeof(Size));
        Pos += 2;
    }

    *pBufLen = Pos;

    return STEAMPROT_OK;
}

extern unsigned int crc32(unsigned int crc, const void *buf, unsigned int size);

int SP_API A2S_RULES_WRITE(A2S_RULES* pRules, WRITE_BUF* pWriteBuf) {
    unsigned char pBuf[SP_MAX_PACKET_SIZE], j;
    int Pos, BufLen, NewBufLen, BufLenLeft;
    long Header, DecompressedSize;
    short RuleCount, i;
    unsigned char* pPacketBuf;
#if SP_COMPRESSED
    bz_stream BZStream;
    unsigned char CompressedBuf[SP_MAX_PACKET_SIZE];
    unsigned int CompressedSize, CRC;
#endif
    /*FILE* fp;
    char FILENAME[255];*/

    Pos = 0;
    memset(pBuf, 0, SP_MAX_PACKET_SIZE);
    Header = htonl(0xFFFFFFFF);
    memcpy(&pBuf[Pos], &Header, sizeof(Header));
    Pos += 4;
    pBuf[Pos++] = SP_RESPONSE_RULES;
    RuleCount = A2S_RULES_getRuleCount(pRules);
    memcpy(&pBuf[Pos], &RuleCount, sizeof(RuleCount));
    Pos += 2;

    for(i = 0; i < A2S_RULES_getRuleCount(pRules); i++) {
        RULE_STRUCT* pRuleStruct = &pRules->m_Rules[i];
        safe_string_append(pBuf, RULE_STRUCT_getName(pRuleStruct));
        safe_string_append(pBuf, RULE_STRUCT_getValue(pRuleStruct));
    }

    if(Pos > SP_SPLIT_SIZE) {
        SPLIT_STRUCT split;
        SPLIT_STRUCT_INIT(&split);
        SPLIT_STRUCT_setSize(&split, SP_SPLIT_SIZE);
        SPLIT_STRUCT_setID(&split, rand());
#if SP_COMPRESSED
        if(Pos > SP_COMPRESSED_MIN_SIZE) {
            CompressedSize = sizeof(CompressedBuf);
            if(BZ2_bzBuffToBuffCompress(CompressedBuf, &CompressedSize, pBuf, Pos, 9, 0, 30) == BZ_OK) {
                DecompressedSize = Pos;
                CRC = crc32(0, pBuf, Pos);
                memcpy(&pBuf[0], &DecompressedSize, sizeof(DecompressedSize));
                memcpy(&pBuf[4], &CRC, sizeof(CRC));
                memcpy(&pBuf[8], &CompressedBuf, CompressedSize);
                Pos = CompressedSize + 8;
                SPLIT_STRUCT_setCompressed(&split);
            }
        }
#endif
        SPLIT_STRUCT_setTotal(&split, (unsigned char)ceilf((float)Pos / SP_SPLIT_SIZE));
        BufLen = 0, NewBufLen = 0;

        for(j = 0; j < SPLIT_STRUCT_getTotal(&split); j++) {
            pPacketBuf = pWriteBuf->m_Buffer[j];
            SPLIT_STRUCT_setNumber(&split, j);
            SPLIT_STRUCT_WRITE(&split, pPacketBuf, &BufLen);
                
            BufLenLeft = Pos - SPLIT_STRUCT_getNumber(&split) * SP_SPLIT_SIZE; 
            memcpy(&pPacketBuf[BufLen], &pBuf[j*SP_SPLIT_SIZE], (BufLenLeft <= SP_SPLIT_SIZE?BufLenLeft:SP_SPLIT_SIZE));
            pWriteBuf->m_Size[j] = (BufLenLeft <= SP_SPLIT_SIZE?BufLenLeft:SP_SPLIT_SIZE) + BufLen;
            
            /*sprintf(FILENAME, "PACKET_%d.bin", j);
            fp = fopen(FILENAME, "wb");
            fwrite(pPacketBuf, pWriteBuf->m_Size[j], 1, fp);
            fclose(fp);*/
        }

        WRITE_BUF_setCount(pWriteBuf, SPLIT_STRUCT_getTotal(&split));
    } else {
        memcpy(pBuf, pWriteBuf->m_Buffer[0], Pos);
        pWriteBuf->m_Size[0] = Pos;
    }

    return STEAMPROT_OK;
}

void SP_API A2S_PLAYER_INIT(A2S_PLAYER* pPlayer) {
    memset(pPlayer, 0, sizeof(A2S_PLAYER));
}

int SP_API A2S_PLAYER_WRITE(A2S_PLAYER* pPlayer, WRITE_BUF* pWriteBuf) {
    int Pos;
    unsigned char* pBuf;
    unsigned char i;
    long Header, Score;
    float Duration;

    Pos = 0;
    pBuf = pWriteBuf->m_Buffer[0];
    Header = htonl(0xFFFFFFFF);
    memcpy(&pBuf[Pos], &Header, sizeof(Header));
    Pos += 4;
    pBuf[Pos++] = SP_RESPONSE_PLAYER;
    pBuf[Pos++] = A2S_PLAYER_getPlayerCount(pPlayer);
    for(i = 0; i < A2S_PLAYER_getPlayerCount(pPlayer); i++) {
        PLAYER_STRUCT* pPlayerStruct = &pPlayer->m_Players[i];
        pBuf[Pos++] = i;
        safe_string_append(pBuf, PLAYER_STRUCT_getName(pPlayerStruct));
        Score = PLAYER_STRUCT_getScore(pPlayerStruct);
        memcpy(&pBuf[Pos], &Score, sizeof(Score));
        Pos += 4;
        Duration = PLAYER_STRUCT_getDuration(pPlayerStruct);
        memcpy(&pBuf[Pos], &Duration, sizeof(Duration));
        Pos += 4;
    }
    pWriteBuf->m_Size[0] = Pos;
    WRITE_BUF_setCount(pWriteBuf, 1);

    return STEAMPROT_OK;
}

void SP_API A2S_INFO_INIT(A2S_INFO* pInfo) {
    memset(pInfo, 0, sizeof(A2S_INFO));
}

int SP_API A2S_INFO_WRITE(A2S_INFO* pInfo, WRITE_BUF* pWriteBuf) {
    int Pos;
    long Header;
    unsigned char* pBuf;
    short ID, Port, SourceTV_Port;
    long long SteamdID, GameID;

    pBuf = pWriteBuf->m_Buffer[0];

    Pos = 0;
    Header = htonl(0xFFFFFFFF);
    memcpy(&pBuf[Pos], &Header, sizeof(Header));
    Pos += 4;
    pBuf[Pos++] = SP_RESPONSE_INFO;
    pBuf[Pos++] = A2S_INFO_getProtocol(pInfo);
    safe_string_append(pBuf, A2S_INFO_getName(pInfo));
    safe_string_append(pBuf, A2S_INFO_getMap(pInfo));
    safe_string_append(pBuf, A2S_INFO_getFolder(pInfo));
    safe_string_append(pBuf, A2S_INFO_getGame(pInfo));
    ID = A2S_INFO_getID(pInfo);
    memcpy(&pBuf[Pos], &ID, sizeof(ID));
    Pos += 2;
    pBuf[Pos++] = A2S_INFO_getPlayers(pInfo);
    pBuf[Pos++] = A2S_INFO_getMaxPlayers(pInfo);
    pBuf[Pos++] = A2S_INFO_getBots(pInfo);
    pBuf[Pos++] = A2S_INFO_getServertype(pInfo);
    pBuf[Pos++] = A2S_INFO_getEnvironment(pInfo);
    pBuf[Pos++] = A2S_INFO_getVisibility(pInfo);
    pBuf[Pos++] = A2S_INFO_getVAC(pInfo);
    safe_string_append(pBuf, A2S_INFO_getVersion(pInfo));
    pBuf[Pos++] = A2S_INFO_getEDF(pInfo);
    if(A2S_INFO_getEDF(pInfo) & SP_EDF_PORT) {
        Port = A2S_INFO_getPort(pInfo);
        memcpy(&pBuf[Pos], &Port, sizeof(Port));
        Pos += 2;
    }
    if(A2S_INFO_getEDF(pInfo) & SP_EDF_STEAMID) {
        SteamdID = A2S_INFO_getSteamID(pInfo);
        memcpy(&pBuf[Pos], &SteamdID, sizeof(SteamdID));
        Pos += 8;
    }
    if(A2S_INFO_getEDF(pInfo) & SP_EDF_SOURCETV) {
        SourceTV_Port = A2S_INFO_getSourceTV_Port(pInfo);
        memcpy(&pBuf[Pos], &SourceTV_Port, sizeof(SourceTV_Port));
        Pos += 2;
        safe_string_append(pBuf, A2S_INFO_getSourceTV_Name(pInfo));
    }
    if(A2S_INFO_getEDF(pInfo) & SP_EDF_KEYWORDS) {
        safe_string_append(pBuf, A2S_INFO_getKeywords(pInfo));
    }
    if(A2S_INFO_getEDF(pInfo) & SP_EDF_GAMEID) {
        GameID = A2S_INFO_getGameID(pInfo);
        memcpy(&pBuf[Pos], &GameID, sizeof(GameID));
        Pos += 8;
    }

    pWriteBuf->m_Size[0] = Pos;
    WRITE_BUF_setCount(pWriteBuf, 1);

    return STEAMPROT_OK;
}

int SP_API HandlePacket(WRITE_BUF* pWriteBuf, unsigned char* pBuf, int BufLen, FillInfoCallback FillInfo, FillPlayerCallback FillPlayer, FillRulesCallback FillRules) {
    int Pos;
    long Header;
    unsigned char Command;

    if(BufLen < 5) {
        return STEAMPROT_ERROR;
    }

    Pos = 0;
    Header = 0xFFFFFFFF;
    if(memcmp(&pBuf[Pos], &Header, sizeof(Header)) == 0) {
        Pos += 4;
        Command = pBuf[Pos];
        switch(Command) {
        case SP_REQUEST_INFO:
            if(FillInfo == NULL)
                return STEAMPROT_ERROR;
            FillInfo(pWriteBuf);
            return STEAMPROT_OK;
        case SP_REQUEST_PLAYER:
            if(FillPlayer == NULL)
                return STEAMPROT_ERROR;
            FillPlayer(pWriteBuf);
            return STEAMPROT_OK;
        case SP_REQUEST_RULES:
            if(FillRules == NULL)
                return STEAMPROT_ERROR;
            FillRules(pWriteBuf);
            return STEAMPROT_OK;
        default:
            return STEAMPROT_ERROR;
        }
    } else {
        return STEAMPROT_ERROR;
    }
}

typedef struct {
    int m_Size;
    int m_ID;
    int m_Type;
    unsigned char* m_Body;
} RCON_PACKET;

int SP_API RCON_WRITE(WRITE_BUF* pWriteBuf, int ID, int Type, const char* Message) {
    int Pos, Size, StringLength;
    int* pSize;
    unsigned char* pBuf;

    pBuf = pWriteBuf->m_Buffer[pWriteBuf->m_Count];

    Pos = 0;
    StringLength = strnlen(Message, SP_RCON_MAX_LENGTH - 12);
    pSize = (int*)&pBuf[Pos];
    Pos += 4;
    memcpy(&pBuf[Pos], &ID, sizeof(ID));
    Pos += 4;
    memcpy(&pBuf[Pos], &Type, sizeof(Type));
    Pos += 4;
    memcpy(&pBuf[Pos], Message, StringLength);
    Pos += StringLength;
    memset(&pBuf[Pos], 0, 2); // empty
    Pos += 2;

    *pSize = StringLength + 10;

    pWriteBuf->m_Size[pWriteBuf->m_Count] = Pos;
    pWriteBuf->m_Count++;

    return STEAMPROT_OK;
}

int SP_API HandleRconPacket(WRITE_BUF* pWriteBuf, unsigned char* pBuf, int BufLen, IsRconPasswordValidCallback IsRconPasswordValid, HandleRconBodyCallback HandleRconBody, RCON_DATA* pRconData) {
    int Pos, Size, ID, Type, StringLength;
    char Body[SP_RCON_MAX_LENGTH];
    memset(Body, 0, SP_RCON_MAX_LENGTH);

    Pos = 0;
    if(BufLen < 14) {
        return STEAMPROT_ERROR;
    }

    memcpy(&Size, &pBuf[Pos], sizeof(Size));
    Pos += 4;
    if(BufLen >= Size) {
        memcpy(&ID, &pBuf[Pos], sizeof(ID));
        Pos += 4;
        memcpy(&Type, &pBuf[Pos], sizeof(Type));
        Pos += 4;
        //StringLength = Size - 12 - 1 /* empty string */;
        StringLength = strnlen(&pBuf[Pos], BufLen - 12);
        memcpy(Body, &pBuf[Pos], StringLength);
        Pos += StringLength + 1 /* empty */;

        switch(Type) {
        case SP_SERVERDATA_AUTH:
            // Handle rcon auth
            RCON_WRITE(pWriteBuf, ID, SP_SERVERDATA_RESPONSE_VALUE, "");

            if(IsRconPasswordValid(Body)) {
                pRconData->m_LoggedIn = 1;
                return RCON_WRITE(pWriteBuf, ID, SP_SERVERDATA_AUTH_RESPONSE, "");
            } else {
                pRconData->m_LoggedIn = 0;
                return RCON_WRITE(pWriteBuf, -1, SP_SERVERDATA_AUTH_RESPONSE, "");
            }
        case SP_SERVERDATA_EXECCOMMAND:
            // Handle rcon command
            if(!pRconData->m_LoggedIn)
                return RCON_WRITE(pWriteBuf, -1, SP_SERVERDATA_AUTH_RESPONSE, "");

            printf("Cmd: %s\n", Body);

            return RCON_WRITE(pWriteBuf, ID, SP_SERVERDATA_RESPONSE_VALUE, HandleRconBody(Body));
        default:
            return STEAMPROT_OK;
        }
    } else {
        return STEAMPROT_ERROR;
    }
}

