#define R_Cmd_GoStart 0x00
#define R_Cmd_Ask 0xf1
#define R_Cmd_Link 0xf3
#define R_Cmd_Check 0xf0
#define R_Cmd_FindConfirm 0x10

#define Unit_Resistance 0x21
#define Unit_Capacity 0x22
#define Unit_Inductance 0x23
#define Unit_Dioxide 0x24

#define T_Cmd_PasswordWrong 0x10
#define T_Cmd_PasswordAccepted 0x11
#define T_Cmd_LinkFinished 0x12
#define T_Cmd_LinkWrong 0x13
#define T_Cmd_UnkownCmd 0x14

#ifdef central
const int Serial_Cmd_Port = 2; //"@3"这样的格式
const int Max_Serial_Cmd_Len = 20;
const char Serial_Cmd_Ask[] = "Ask";
const int Serial_Cmd_Ask_Len = 3;
const char Serial_Cmd_Find[] = "Find:"; //后面有6个值,包含数值和单位
const int Serial_Cmd_Find_Len = 5;
const int Serial_Cmd_Find_Extra = 6;
const char Serial_Cmd_Confirm[] = "Confirm"; 
const int Serial_Cmd_Confirm_Len = 7;
const char Serial_Cmd_Link[] = "Link:"; //后面有4个值,分别是十六进制表示的四个引脚
const int Serial_Cmd_Link_Len = 5;
const int Serial_Cmd_Link_Extra = 4;
const char Serial_Cmd_Check[] = "Check:"; //后面有4个值，是十六进制密码
const int Serial_Cmd_Check_Len = 6;
const int Serial_Cmd_Check_Extra = 4;
const char Serial_Cmd_Re[] = "Re:"; //后面6个值，是发送数据的十六进制
const int Serial_Cmd_Re_Len = 3;
const int Serial_Cmd_Re_Extra = 6;

const char Serial_Back_PortNotExist[] = "Port_Not_Exist";
const char Serial_Back_GoStartWrong[] = "GoStart_Wrong";
const char Serial_Back_SendWrong[] = "Send_Wrong";
const char Serial_Back_NoAnswer[] = "No_Answer";
const char Serial_Back_TreatyWrong[] = "Treaty_Wrong";
const char Serial_Back_WrongRepeatBack[] = "Wrong_Repeated_Back";
const char Serial_Back_NowayWrong[] = "Noway_Wrong";
const char Serial_Back_PasswordWrong[] = "Password_Wrong";
const char Serial_Back_PasswordAccepted[] = "Password_Accept";
const char Serial_Back_LinkFinished[] = "Link_Finished";
const char Serial_Back_LinkWrong[] = "Link_Wrong";
const char Serial_Back_Info[] = "Info:";
const char Serial_Back_UnknownCmd[] = "Unknown_Cmd";
const char Serial_Back_Confirm[] = "Confirm:";				
const char Serial_Back_Confirmed[] = "Confirmed";

#endif
