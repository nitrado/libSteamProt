#ifndef __LIBSTEAMPROT__
#define __LIBSTEAMPROT__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(_WIN32) || defined(WIN32)
#include <Windows.h>
#define SP_API WINAPI
#ifdef _DLL
#define SP_EXTERN __declspec(dllexport)
#else
#define SP_EXTERN extern
#endif
#else
#define SP_API
#define SP_EXTERN extern
#endif

#define SP_PLAYER_MAX            64
#define SP_RULE_MAX              255
#define SP_STRING_LENGTH         255
#define SP_MAX_PACKET_SIZE       16384
#define SP_SPLIT_SIZE            1248
#define STEAMPROT_OK             0
#define STEAMPROT_ERROR          -1

#define SP_SERVERTYPE_DEDICATED  'd'
#define SP_SERVERTYPE_LISTEN     'l'
#define SP_SERVERTYPE_PROXY      'p'

#define SP_ENVIRONMENT_LINUX     'l'
#define SP_ENVIRONMENT_WINDOWS   'w'
#define SP_ENVIRONMENT_MAC       'm'

#define SP_REQUEST_RULES         'V'
#define SP_RESPONSE_RULES        'E'
#define SP_REQUEST_INFO          'T'
#define SP_RESPONSE_INFO         'I'
#define SP_REQUEST_PLAYER        'U'
#define SP_RESPONSE_PLAYER       'D'

#define SP_EDF_GAMEID            0x01
#define SP_EDF_STEAMID           0x10
#define SP_EDF_KEYWORDS          0x20
#define SP_EDF_SOURCETV          0x40
#define SP_EDF_PORT              0x80

/*
    RCON
*/
#define SP_RCON_MAX_LENGTH           4096 - 12

#define SP_RCON_COMMAND_STATE_NONE      0
#define SP_RCON_COMMAND_STATE_PROCESS   1
#define SP_RCON_COMMAND_STATE_PROCESSED 2
#define SP_RCON_COMMAND_STATE_ERROR     3

#define SP_SERVERDATA_AUTH           3
#define SP_SERVERDATA_AUTH_RESPONSE  2
#define SP_SERVERDATA_CONSOLE_LOG    4
#define SP_SERVERDATA_EXECCOMMAND    2
#define SP_SERVERDATA_RESPONSE_VALUE 0

#ifndef SP_COMPRESSED
#define SP_COMPRESSED 0
#endif

#ifndef SP_COMPRESSED_MIN_SIZE
#define SP_COMPRESSED_MIN_SIZE   SP_SPLIT_SIZE * 2
#endif

typedef struct {
    unsigned char m_Buffer[16][SP_MAX_PACKET_SIZE];
    short m_Size[16];
    unsigned char m_Count;

    //short m_Size;
} WRITE_BUF;

typedef void (SP_API *FillPlayerCallback)(WRITE_BUF* pWriteBuf);
typedef void (SP_API *FillInfoCallback)(WRITE_BUF* pWriteBuf);
typedef void (SP_API *FillRulesCallback)(WRITE_BUF* pWriteBuf);

typedef char (SP_API *IsRconPasswordValidCallback)(const char* Password);
typedef const char* (SP_API *HandleRconBodyCallback)(const char* Body);

typedef struct {
    //unsigned char Header;
    unsigned char m_Protocol;
    char m_Name[SP_STRING_LENGTH];
    char m_Map[SP_STRING_LENGTH];
    char m_Folder[SP_STRING_LENGTH];
    char m_Game[SP_STRING_LENGTH];
    short m_ID;
    unsigned char m_Players;
    unsigned char m_MaxPlayers;
    unsigned char m_Bots;
    unsigned char m_Servertype;
    unsigned char m_Environment;
    unsigned char m_Visibility;
    unsigned char m_VAC;
    char m_Version[SP_STRING_LENGTH];
    unsigned char m_EDF;

    // Extra Data
    short m_Port;
    long long m_SteamID;
    short m_SourceTV_Port;
    char m_SourceTV_Name[SP_STRING_LENGTH];
    char m_Keywords[SP_STRING_LENGTH];
    long long m_GameID;
} A2S_INFO;

/*typedef struct {
    unsigned int m_ID;
    char m_Request[SP_STRING_LENGTH];
    char m_Response[SP_RCON_MAX_LENGTH];
    char m_State;
    struct RCON_COMMAND* m_pNext;
} RCON_COMMAND;*/

typedef struct {
    char m_LoggedIn;
    struct RCON_COMMAND* m_pCommandQueue;
} RCON_DATA;

typedef struct {
    unsigned char m_Index;
    char m_Name[SP_STRING_LENGTH];
    long m_Score;
    float m_Duration;
} PLAYER_STRUCT;

typedef struct {
    //unsigned char Header;
    unsigned char m_PlayerCount;
    PLAYER_STRUCT m_Players[SP_PLAYER_MAX];
} A2S_PLAYER;

typedef struct {
    char m_Name[SP_STRING_LENGTH];
    char m_Value[SP_STRING_LENGTH];
} RULE_STRUCT;

typedef struct {
    //unsigned char Header;
    short m_RuleCount;
    RULE_STRUCT m_Rules[SP_RULE_MAX];
} A2S_RULES;

typedef struct {
    long m_ID;
    unsigned char m_Total;
    unsigned char m_Number;
    short m_Size;
} SPLIT_STRUCT;

SP_EXTERN RCON_DATA* SP_API RCON_DATA_create();
SP_EXTERN WRITE_BUF* SP_API WRITE_BUF_create();
SP_EXTERN A2S_INFO* SP_API A2S_INFO_create();
SP_EXTERN A2S_PLAYER* SP_API A2S_PLAYER_create();
SP_EXTERN A2S_RULES* SP_API A2S_RULES_create();
SP_EXTERN void SP_API RCON_DATA_destory(RCON_DATA* pRconData);
SP_EXTERN void SP_API A2S_INFO_destory(A2S_INFO* pInfo);
SP_EXTERN void SP_API A2S_PLAYER_destory(A2S_PLAYER* pPlayer);
SP_EXTERN void SP_API A2S_RULES_destory(A2S_RULES* pRules);
SP_EXTERN void SP_API WRITE_BUF_destroy(WRITE_BUF* pWriteBuf);

/*
    A2S_PLAYER Functions
*/
SP_EXTERN void SP_API A2S_PLAYER_INIT(A2S_PLAYER* pPlayer);
SP_EXTERN int SP_API A2S_PLAYER_WRITE(A2S_PLAYER* pPlayer, WRITE_BUF* pWriteBuf);
SP_EXTERN PLAYER_STRUCT* SP_API A2S_PLAYER_GET(A2S_PLAYER* pPlayer, unsigned char Index);

SP_EXTERN void SP_API PLAYER_STRUCT_setName(PLAYER_STRUCT* pPlayerStruct, const char* Name);
SP_EXTERN void SP_API PLAYER_STRUCT_setScore(PLAYER_STRUCT* pPlayerStruct, long Score);
SP_EXTERN void SP_API PLAYER_STRUCT_setDuration(PLAYER_STRUCT* pPlayerStruct, float Duration);
SP_EXTERN void SP_API A2S_PLAYER_setPlayerCount(A2S_PLAYER* pPlayer, unsigned char PlayerCount);

SP_EXTERN const char* SP_API PLAYER_STRUCT_getName(PLAYER_STRUCT* pPlayerStruct);
SP_EXTERN long SP_API PLAYER_STRUCT_getScore(PLAYER_STRUCT* pPlayerStruct);
SP_EXTERN float SP_API PLAYER_STRUCT_getDuration(PLAYER_STRUCT* pPlayerStruct);
SP_EXTERN unsigned char SP_API A2S_PLAYER_getPlayerCount(A2S_PLAYER* pPlayer);

/*
    A2S_RULES Functions
*/
SP_EXTERN void SP_API A2S_RULES_INIT(A2S_RULES* pRules);
SP_EXTERN int SP_API A2S_RULES_WRITE(A2S_RULES* pRules, WRITE_BUF* pWriteBuf);
SP_EXTERN RULE_STRUCT* SP_API A2S_RULES_GET(A2S_RULES* pRules, unsigned char Index);

SP_EXTERN void SP_API RULE_STRUCT_setName(RULE_STRUCT* pRuleStruct, const char* Name);
SP_EXTERN void SP_API RULE_STRUCT_setValue(RULE_STRUCT* pRuleStruct, const char* Value);
SP_EXTERN void SP_API A2S_RULES_setRuleCount(A2S_RULES* pRules, short RuleCount);

SP_EXTERN const char* SP_API RULE_STRUCT_getName(RULE_STRUCT* pRuleStruct);
SP_EXTERN const char* SP_API RULE_STRUCT_getValue(RULE_STRUCT* pRuleStruct);
SP_EXTERN short SP_API A2S_RULES_getRuleCount(A2S_RULES* pRules);

/*
    A2S_INFO Functions
*/
SP_EXTERN void SP_API A2S_INFO_INIT(A2S_INFO* pInfo);
SP_EXTERN int SP_API A2S_INFO_WRITE(A2S_INFO* pInfo, WRITE_BUF* pWriteBuf);

SP_EXTERN void SP_API A2S_INFO_setProtocol(A2S_INFO* pInfo, unsigned char Protocol);
SP_EXTERN void SP_API A2S_INFO_setPort(A2S_INFO* pInfo, short Port);
SP_EXTERN void SP_API A2S_INFO_setSteamID(A2S_INFO* pInfo, long long SteamID);
SP_EXTERN void SP_API A2S_INFO_setSourceTV_Port(A2S_INFO* pInfo, short Port);
SP_EXTERN void SP_API A2S_INFO_setSourceTV_Name(A2S_INFO* pInfo, const char* Name);
SP_EXTERN void SP_API A2S_INFO_setKeywords(A2S_INFO* pInfo, const char* Keywords);
SP_EXTERN void SP_API A2S_INFO_setGameID(A2S_INFO* pInfo, long long GameID);
SP_EXTERN void SP_API A2S_INFO_setName(A2S_INFO* pInfo, const char* Name);
SP_EXTERN void SP_API A2S_INFO_setMap(A2S_INFO* pInfo, const char* Map);
SP_EXTERN void SP_API A2S_INFO_setFolder(A2S_INFO* pInfo, const char* Folder);
SP_EXTERN void SP_API A2S_INFO_setGame(A2S_INFO* pInfo, const char* Game);
SP_EXTERN void SP_API A2S_INFO_setID(A2S_INFO* pInfo, short ID);
SP_EXTERN void SP_API A2S_INFO_setPlayers(A2S_INFO* pInfo, unsigned char Players);
SP_EXTERN void SP_API A2S_INFO_setMaxPlayers(A2S_INFO* pInfo, unsigned char MaxPlayers);
SP_EXTERN void SP_API A2S_INFO_setBots(A2S_INFO* pInfo, unsigned char Bots);
SP_EXTERN void SP_API A2S_INFO_setServertype(A2S_INFO* pInfo, unsigned char Servertype);
SP_EXTERN void SP_API A2S_INFO_setEnvironment(A2S_INFO* pInfo, unsigned char Environment);
SP_EXTERN void SP_API A2S_INFO_setVisibility(A2S_INFO* pInfo, unsigned char Visibility);
SP_EXTERN void SP_API A2S_INFO_setVAC(A2S_INFO* pInfo, unsigned char VAC);
SP_EXTERN void SP_API A2S_INFO_setVersion(A2S_INFO* pInfo, const char* Version);
SP_EXTERN void SP_API A2S_INFO_setEDF(A2S_INFO* pInfo, unsigned char EDF);

SP_EXTERN short SP_API A2S_INFO_getPort(A2S_INFO* pInfo);
SP_EXTERN long long SP_API A2S_INFO_getSteamID(A2S_INFO* pInfo);
SP_EXTERN short SP_API A2S_INFO_getSourceTV_Port(A2S_INFO* pInfo);
SP_EXTERN const char* SP_API A2S_INFO_getSourceTV_Name(A2S_INFO* pInfo);
SP_EXTERN const char* SP_API A2S_INFO_getKeywords(A2S_INFO* pInfo);
SP_EXTERN long long SP_API A2S_INFO_getGameID(A2S_INFO* pInfo);
SP_EXTERN unsigned char SP_API A2S_INFO_getProtocol(A2S_INFO* pInfo);
SP_EXTERN const char* SP_API A2S_INFO_getName(A2S_INFO* pInfo);
SP_EXTERN const char* SP_API A2S_INFO_getMap(A2S_INFO* pInfo);
SP_EXTERN const char* SP_API A2S_INFO_getFolder(A2S_INFO* pInfo);
SP_EXTERN const char* SP_API A2S_INFO_getGame(A2S_INFO* pInfo);
SP_EXTERN short SP_API A2S_INFO_getID(A2S_INFO* pInfo);
SP_EXTERN unsigned char SP_API A2S_INFO_getPlayers(A2S_INFO* pInfo);
SP_EXTERN unsigned char SP_API A2S_INFO_getMaxPlayers(A2S_INFO* pInfo);
SP_EXTERN unsigned char SP_API A2S_INFO_getBots(A2S_INFO* pInfo);
SP_EXTERN unsigned char SP_API A2S_INFO_getServertype(A2S_INFO* pInfo);
SP_EXTERN unsigned char SP_API A2S_INFO_getEnvironment(A2S_INFO* pInfo);
SP_EXTERN unsigned char SP_API A2S_INFO_getVisibility(A2S_INFO* pInfo);
SP_EXTERN unsigned char SP_API A2S_INFO_getVAC(A2S_INFO* pInfo);
SP_EXTERN const char* SP_API A2S_INFO_getVersion(A2S_INFO* pInfo);
SP_EXTERN unsigned char SP_API A2S_INFO_getEDF(A2S_INFO* pInfo);

/*
    SPLIT_STRUCT Functions
*/
SP_EXTERN void SP_API SPLIT_STRUCT_INIT(SPLIT_STRUCT* pSplit);
SP_EXTERN int SP_API SPLIT_STRUCT_WRITE(SPLIT_STRUCT* pSplit, unsigned char* pBuf, int* pBufLen);

SP_EXTERN void SP_API SPLIT_STRUCT_setID(SPLIT_STRUCT* pSplitStruct, long ID);
SP_EXTERN void SP_API SPLIT_STRUCT_setCompressed(SPLIT_STRUCT* pSplitStruct);
SP_EXTERN void SP_API SPLIT_STRUCT_setTotal(SPLIT_STRUCT* pSplitStruct, unsigned char Total);
SP_EXTERN void SP_API SPLIT_STRUCT_setNumber(SPLIT_STRUCT* pSplitStruct, unsigned char Number);
SP_EXTERN void SP_API SPLIT_STRUCT_setSize(SPLIT_STRUCT* pSplitStruct, short Size);

SP_EXTERN unsigned char SP_API SPLIT_STRUCT_isCompressed(SPLIT_STRUCT* pSplitStruct);
SP_EXTERN long SP_API SPLIT_STRUCT_getID(SPLIT_STRUCT* pSplitStruct);
SP_EXTERN unsigned char SP_API SPLIT_STRUCT_getTotal(SPLIT_STRUCT* pSplitStruct);
SP_EXTERN unsigned char SP_API SPLIT_STRUCT_getNumber(SPLIT_STRUCT* pSplitStruct);
SP_EXTERN short SP_API SPLIT_STRUCT_getSize(SPLIT_STRUCT* pSplitStruct);

/*
    WRITE_BUF Functions
*/
SP_EXTERN void SP_API WRITE_BUF_INIT(WRITE_BUF* pWriteBuf);

SP_EXTERN void SP_API WRITE_BUF_setCount(WRITE_BUF* pWriteBuf, unsigned char Count);
SP_EXTERN void SP_API WRITE_BUF_setSize(WRITE_BUF* pWriteBuf, unsigned char Index, short Size);

SP_EXTERN unsigned char SP_API WRITE_BUF_getCount(WRITE_BUF* pWriteBuf);
SP_EXTERN short SP_API WRITE_BUF_getSize(WRITE_BUF* pWriteBuf, unsigned char Index);

/*
    Handle Socket Data
*/
SP_EXTERN int SP_API HandlePacket(WRITE_BUF* pWriteBuf, unsigned char* pBuf, int BufLen, FillInfoCallback FillInfo, FillPlayerCallback FillPlayer, FillRulesCallback FillRules);
SP_EXTERN int SP_API HandleRconPacket(WRITE_BUF* pWriteBuf, unsigned char* pBuf, int BufLen, IsRconPasswordValidCallback IsRconPasswordValid, HandleRconBodyCallback HandleRconBody, RCON_DATA* pRconData);

#ifdef __cplusplus
}
#endif

#endif // __LIBSTEAMPROT__
