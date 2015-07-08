using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApplication1
{
    class Program
    {
        public static void FillInfoCallback(IntPtr pWriteBuf)
        {
            IntPtr pInfo = libSteamProt.A2S_INFO_create();
            libSteamProt.A2S_INFO_INIT(pInfo);

            libSteamProt.A2S_INFO_setProtocol(pInfo, 0x11);
            libSteamProt.A2S_INFO_setName(pInfo, "Sample Server".ToCharArray());
            libSteamProt.A2S_INFO_setMap(pInfo, "demo".ToCharArray());
            libSteamProt.A2S_INFO_setFolder(pInfo, "csgo".ToCharArray());
            libSteamProt.A2S_INFO_setGame(pInfo, "Counter-Strike: Global Offensive".ToCharArray());
            libSteamProt.A2S_INFO_setID(pInfo, 730);
            libSteamProt.A2S_INFO_setPlayers(pInfo, 0);
            libSteamProt.A2S_INFO_setMaxPlayers(pInfo, 64);
            libSteamProt.A2S_INFO_setBots(pInfo, 0);
            libSteamProt.A2S_INFO_setServertype(pInfo, Convert.ToByte('d'));
            libSteamProt.A2S_INFO_setEnvironment(pInfo, Convert.ToByte('l'));
            libSteamProt.A2S_INFO_setVisibility(pInfo, 0);
            libSteamProt.A2S_INFO_setVAC(pInfo, 1);
            libSteamProt.A2S_INFO_setVersion(pInfo, "1.34.9.2".ToCharArray());
            libSteamProt.A2S_INFO_setEDF(pInfo, 0x20 | 0x01 | 0x10 | 0x80);
            libSteamProt.A2S_INFO_setPort(pInfo, 27015);
            libSteamProt.A2S_INFO_setKeywords(pInfo, "CSDM,FFA,mousesports,mouz,secure".ToCharArray());
            libSteamProt.A2S_INFO_setSteamID(pInfo, 730);
            libSteamProt.A2S_INFO_setGameID(pInfo, 730);

            /* Read string from info object
            string str = Marshal.PtrToStringAnsi(libSteamProt.A2S_INFO_getName(pInfo));
            Console.WriteLine("Server: {0}", str);*/

            libSteamProt.A2S_INFO_WRITE(pInfo, pWriteBuf);
            libSteamProt.A2S_INFO_destory(pInfo);
        }

        public static void FillPlayerCallback(IntPtr pWriteBuf)
        {
            IntPtr pPlayer = libSteamProt.A2S_PLAYER_create();
            libSteamProt.A2S_PLAYER_INIT(pPlayer);

            libSteamProt.A2S_PLAYER_setPlayerCount(pPlayer, 10);

            for(byte i = 0; i < libSteamProt.A2S_PLAYER_getPlayerCount(pPlayer); i++) {
                IntPtr pPlayerStruct = libSteamProt.A2S_PLAYER_GET(pPlayer, i);
                string PlayerName = "player_" + i;
                libSteamProt.PLAYER_STRUCT_setName(pPlayerStruct, PlayerName.ToCharArray());
                libSteamProt.PLAYER_STRUCT_setDuration(pPlayerStruct, 0.1f);
                libSteamProt.PLAYER_STRUCT_setScore(pPlayerStruct, i);
            }

            libSteamProt.A2S_PLAYER_WRITE(pPlayer, pWriteBuf);
            libSteamProt.A2S_PLAYER_destory(pPlayer);
        }

        public static void FillRulesCallback(IntPtr pWriteBuf)
        {
            IntPtr pRules = libSteamProt.A2S_RULES_create();
            libSteamProt.A2S_RULES_INIT(pRules);

            libSteamProt.A2S_RULES_setRuleCount(pRules, 177);

            for(byte i = 0; i < libSteamProt.A2S_RULES_getRuleCount(pRules); i++) {
                IntPtr pRuleStruct = libSteamProt.A2S_RULES_GET(pRules, i);
                string Key = "key_" + i;
                string Value = "value_" + i;
                libSteamProt.RULE_STRUCT_setName(pRuleStruct, Key.ToCharArray());
                libSteamProt.RULE_STRUCT_setValue(pRuleStruct, Value.ToCharArray());
            }

            libSteamProt.A2S_RULES_WRITE(pRules, pWriteBuf);
            libSteamProt.A2S_RULES_destory(pRules);
        }

        static void Main(string[] args)
        {
            IntPtr pWriteBuf = libSteamProt.WRITE_BUF_create();
            libSteamProt.WRITE_BUF_INIT(pWriteBuf);

            // simulate info, player, rules request
            byte[][] packets = new byte[3][] { new byte[] { 0xFF, 0xFF, 0xFF, 0xFF, 0x54 }, new byte[] { 0xFF, 0xFF, 0xFF, 0xFF, 0x55 }, new byte[] { 0xFF, 0xFF, 0xFF, 0xFF, 0x56 } };

            for (int i = 0; i < 3; i++)
            {
                libSteamProt.FillInfoCallbackDelegate InfoDel = FillInfoCallback;
                libSteamProt.FillPlayerCallbackDelegate PlayerDel = FillPlayerCallback;
                libSteamProt.FillRulesCallbackDelegate RulesDel = FillRulesCallback;

                int ret = libSteamProt.HandlePacket(pWriteBuf, packets[i], 5, InfoDel, PlayerDel, RulesDel);
                if (ret == 0)
                {
                    libSteamProt.WRITE_BUF WriteBuf = (libSteamProt.WRITE_BUF)Marshal.PtrToStructure(pWriteBuf, typeof(libSteamProt.WRITE_BUF));
                    for (int j = 0; j < WriteBuf.Count; j++)
                    {
                        Console.WriteLine("Count: {2}/{0} Size: {1}", WriteBuf.Count, WriteBuf.Size[j], (j+1));
                        Console.WriteLine(BitConverter.ToString(WriteBuf.Buffer[j].Buffer, 0, WriteBuf.Size[j]));

                        // Write data to socket here
                    } 
                }
                else
                {
                    Console.WriteLine("Return {0}", ret);
                }
            }

            libSteamProt.WRITE_BUF_destroy(pWriteBuf);

            Console.ReadLine();
        }
    }
}
