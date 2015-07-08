using System;
using System.Reflection;
using System.Runtime.InteropServices;
using System.Security;
using System.Text;

static class libSteamProt
{
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void FillInfoCallbackDelegate(IntPtr pWriteBuf);

    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void FillPlayerCallbackDelegate(IntPtr pWriteBuf);

    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void FillRulesCallbackDelegate(IntPtr pWriteBuf);

    [StructLayout(LayoutKind.Sequential)]
    public struct WRITE_BUF_SUB
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16384)]
        public byte[] Buffer;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct WRITE_BUF
    {
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public WRITE_BUF_SUB[] Buffer;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 16)]
        public short[] Size;
        public byte Count;
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct Callbacks
    {
        public IntPtr FillInfoCallback;
        public IntPtr FillPlayerCallback;
        public IntPtr FillRulesCallback;
    }

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern IntPtr A2S_INFO_create();

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern IntPtr A2S_PLAYER_create();

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern IntPtr A2S_RULES_create();

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_destory(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_PLAYER_destory(IntPtr pPlayer);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_RULES_destory(IntPtr pRules);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_INIT(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern int A2S_INFO_WRITE(IntPtr pInfo, IntPtr pWriteBuf);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_setProtocol(IntPtr pInfo, byte Protocol);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_setPort(IntPtr pInfo, short Port);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_setSteamID(IntPtr pInfo, ulong SteamID);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_setSourceTV_Port(IntPtr pInfo, short Port);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_setSourceTV_Name(IntPtr pInfo, char[] Name);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_setKeywords(IntPtr pInfo, char[] Keywords);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_setGameID(IntPtr pInfo, ulong GameID);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_setName(IntPtr pInfo, char[] Name);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_setMap(IntPtr pInfo, char[] Map);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_setFolder(IntPtr pInfo, char[] Folder);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_setGame(IntPtr pInfo, char[] Game);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_setID(IntPtr pInfo, short ID);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_setPlayers(IntPtr pInfo, byte Players);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_setMaxPlayers(IntPtr pInfo, byte MaxPlayers);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_setBots(IntPtr pInfo, byte Bots);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_setServertype(IntPtr pInfo, byte Servertype);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_setEnvironment(IntPtr pInfo, byte Environment);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_setVisibility(IntPtr pInfo, byte Visibility);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_setVAC(IntPtr pInfo, byte VAC);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_setVersion(IntPtr pInfo, char[] Version);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_INFO_setEDF(IntPtr pInfo, byte EDF);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern short A2S_INFO_getPort(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern ulong A2S_INFO_getSteamID(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern short A2S_INFO_getSourceTV_Port(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern IntPtr A2S_INFO_getSourceTV_Name(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern IntPtr A2S_INFO_getKeywords(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern ulong A2S_INFO_getGameID(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern byte A2S_INFO_getProtocol(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern IntPtr A2S_INFO_getName(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern IntPtr A2S_INFO_getMap(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern IntPtr A2S_INFO_getFolder(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern IntPtr A2S_INFO_getGame(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern short A2S_INFO_getID(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern byte A2S_INFO_getPlayers(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern byte A2S_INFO_getMaxPlayers(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern byte A2S_INFO_getBots(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern byte A2S_INFO_getServertype(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern byte A2S_INFO_getEnvironment(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern byte A2S_INFO_getVisibility(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern byte A2S_INFO_getVAC(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern IntPtr A2S_INFO_getVersion(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern byte A2S_INFO_getEDF(IntPtr pInfo);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_PLAYER_INIT(IntPtr pPlayer);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern int A2S_PLAYER_WRITE(IntPtr pPlayer, IntPtr pWriteBuf);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern IntPtr A2S_PLAYER_GET(IntPtr pPlayer, byte Index);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void PLAYER_STRUCT_setName(IntPtr pPlayerStruct, char[] Name);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void PLAYER_STRUCT_setDuration(IntPtr pPlayerStruct, float Duration);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void PLAYER_STRUCT_setScore(IntPtr pPlayerStruct, int Score);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_PLAYER_setPlayerCount(IntPtr pPlayer, byte PlayerCount);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern IntPtr PLAYER_STRUCT_getName(IntPtr pPlayerStruct);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern int PLAYER_STRUCT_getScore(IntPtr pPlayerStruct);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern float PLAYER_STRUCT_getDuration(IntPtr pPlayerStruct);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern byte A2S_PLAYER_getPlayerCount(IntPtr pPlayer);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_RULES_INIT(IntPtr pRules);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern IntPtr A2S_RULES_GET(IntPtr pRules, byte Index);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern int A2S_RULES_WRITE(IntPtr pRules, IntPtr pWriteBuf);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void RULE_STRUCT_setName(IntPtr pRuleStruct, char[] Name);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void RULE_STRUCT_setValue(IntPtr pRuleStruct, char[] Value);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void A2S_RULES_setRuleCount(IntPtr pRules, short RuleCount);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern IntPtr RULE_STRUCT_getName(IntPtr pRuleStruct);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern IntPtr RULE_STRUCT_getValue(IntPtr pRuleStruct);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern short A2S_RULES_getRuleCount(IntPtr pRules);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void WRITE_BUF_INIT(IntPtr pWriteBuf);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern IntPtr WRITE_BUF_create();

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void WRITE_BUF_destroy(IntPtr pWriteBuf);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void WRITE_BUF_setCount(IntPtr pWriteBuf, byte Count);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern void WRITE_BUF_setSize(IntPtr pWriteBuf, byte Index, short Size);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern byte WRITE_BUF_getCount(IntPtr pWriteBuf);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern short WRITE_BUF_getSize(IntPtr pWriteBuf, byte Index);

    [DllImport("libSteamProt", CharSet = CharSet.Ansi, CallingConvention = CallingConvention.StdCall)]
    public static extern int HandlePacket(IntPtr pWriteBuf, byte[] pBuf, int BufLen, FillInfoCallbackDelegate FillInfo, FillPlayerCallbackDelegate FillPlayer, FillRulesCallbackDelegate FillRules);
}
