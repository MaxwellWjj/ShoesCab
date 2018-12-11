#include "public.h"
#include "GUI.h"

void GUI_based(void)
{
	LCD_Clear(BLACK);
	POINT_COLOR=YELLOW;
	Show_Str(144,20,200,24,"鞋柜同学导航界面",24,1);
	LCD_ShowString(144,20,200,24,24,"Guide For Shoes Cab");
	Show_Str(164,50,200,16,"Guide For Shoes Cab",16,1);
	LCD_DrawLine(0,85,480,85);
	POINT_COLOR=WHITE;
	Show_Str_Mid(0,110,"欢迎使用鞋柜同学智能家居产品,本产品",24,480);
	Show_Str_Mid(0,160,"基于STM32控制器,测量内部参数,上传,控制",24,480);
	Show_Str_Mid(0,210,"鞋柜内部的干燥除湿,消毒杀菌,恒温控制",24,480);
	Show_Str_Mid(0,260,"模块,做到自动控制与远程控制并行,实现",24,480);
	Show_Str(10,310,130,24,"高度智能化",24,1);
	POINT_COLOR=YELLOW;
	Show_Str(144,400,200,24,"下面进行使用介绍",24,1);
	POINT_COLOR=WHITE;
	Show_Str_Mid(0,450,"该系统可以使用鞋柜上的矩阵键盘进行控制",24,480);
	POINT_COLOR=WHITE;
	Show_Str(10,500,230,24,"按A进入工作监视模式",24,1);
	Show_Str(250,500,230,24,"按B进入调整阈值模式",24,1);
	Show_Str(10,600,230,24,"按C进入网络配置模式",24,1);
	Show_Str(250,600,230,24,"按D进入手动控制模式",24,1);
	POINT_COLOR=YELLOW;	
	Show_Str(370,785,110,12,"Company:Fish Rush",12,1);
}


void GUI_ShowParam(void)
{
	LCD_Clear(BLACK);
	POINT_COLOR=YELLOW;
	Show_Str(144,20,200,24,"参数监控工作模式",24,1);
	Show_Str(164,50,200,16,"Watch For Shoes Cab",16,1);
	LCD_DrawLine(240,70,240,790);
	POINT_COLOR = WHITE;
	Show_Str_Mid(0,70,"物理参数及工作状态",24,240);
	Show_Str(20,120,100,16,"温度:",16,1);
	Show_Str(20,180,100,16,"湿度:",16,1);
	Show_Str(20,240,100,16,"臭味浓度:",16,1);
	Show_Str(20,300,100,16,"当地天气:",16,1);
	Show_Str(20,360,100,16,"干燥除湿:",16,1);
	Show_Str(20,420,100,16,"恒温模式:",16,1);
	Show_Str(20,480,100,16,"除臭模式:",16,1);
	
	Show_Str_Mid(240,70,"网络连接状态",24,240);
	Show_Str(260,120,100,16,"状态:",16,1); 		//连接状态
	Show_Str(260,180,100,16,"IP地址:",16,1);
	Show_Str(260,240,100,16,"端口号:",16,1);
	Show_Str(260,300,100,16,"当前时间:",16,1);
	
	Show_Str(250,500,230,24,"按A返回导航界面",24,1);
	
	POINT_COLOR=YELLOW;
	Show_Str(370,785,110,12,"Company:Fish Rush",12,1);

}

void GUI_Internet(void)
{
	LCD_Clear(BLACK);
	POINT_COLOR=YELLOW;
	Show_Str(144,20,200,24,"产品网络配置模式",24,1);
	Show_Str(164,50,200,16,"Internet Config Mode",16,1);
	LCD_DrawLine(0,85,480,85);
	POINT_COLOR = WHITE;
	Show_Str_Mid(0,150,"按B输入路由器IP地址",24,240);
	Show_Str_Mid(0,250,"按C输入路由器连接密码",24,240);
	Show_Str_Mid(0,350,"按D确认并连接",24,240);
	Show_Str_Mid(0,450,"按A返回导航界面",24,240);
	POINT_COLOR=YELLOW;
	Show_Str(370,785,110,12,"Company:Fish Rush",12,1);
}

void GUI_Control(void)
{
	LCD_Clear(BLACK);
	POINT_COLOR=YELLOW;
	Show_Str(144,20,200,24,"手动控制工作模式",24,1);
	Show_Str(164,50,200,16,"CTRL For Shoes Cab",16,1);
	LCD_DrawLine(240,70,240,790);	
	POINT_COLOR=WHITE;
	Show_Str_Mid(0,70,"当前状态",24,240);
	Show_Str(20,120,100,16,"干燥除湿:",16,1);
	Show_Str(20,180,100,16,"恒温模式:",16,1);
	Show_Str(20,240,100,16,"除臭模式:",16,1);
	Show_Str_Mid(240,150,"按B打开/关闭干燥",24,240);
	Show_Str_Mid(240,250,"按C打开/关闭恒温",24,240);
	Show_Str_Mid(240,350,"按D打开/关闭除臭",24,240);
	Show_Str_Mid(240,450,"按A返回开始界面",24,240);
	
	POINT_COLOR=YELLOW;
	Show_Str(370,785,110,12,"Company:Fish Rush",12,1);	
}
