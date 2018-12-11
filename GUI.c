#include "public.h"
#include "GUI.h"

void GUI_based(void)
{
	LCD_Clear(BLACK);
	POINT_COLOR=YELLOW;
	Show_Str(144,20,200,24,"Ь��ͬѧ��������",24,1);
	LCD_ShowString(144,20,200,24,24,"Guide For Shoes Cab");
	Show_Str(164,50,200,16,"Guide For Shoes Cab",16,1);
	LCD_DrawLine(0,85,480,85);
	POINT_COLOR=WHITE;
	Show_Str_Mid(0,110,"��ӭʹ��Ь��ͬѧ���ܼҾӲ�Ʒ,����Ʒ",24,480);
	Show_Str_Mid(0,160,"����STM32������,�����ڲ�����,�ϴ�,����",24,480);
	Show_Str_Mid(0,210,"Ь���ڲ��ĸ����ʪ,����ɱ��,���¿���",24,480);
	Show_Str_Mid(0,260,"ģ��,�����Զ�������Զ�̿��Ʋ���,ʵ��",24,480);
	Show_Str(10,310,130,24,"�߶����ܻ�",24,1);
	POINT_COLOR=YELLOW;
	Show_Str(144,400,200,24,"�������ʹ�ý���",24,1);
	POINT_COLOR=WHITE;
	Show_Str_Mid(0,450,"��ϵͳ����ʹ��Ь���ϵľ�����̽��п���",24,480);
	POINT_COLOR=WHITE;
	Show_Str(10,500,230,24,"��A���빤������ģʽ",24,1);
	Show_Str(250,500,230,24,"��B���������ֵģʽ",24,1);
	Show_Str(10,600,230,24,"��C������������ģʽ",24,1);
	Show_Str(250,600,230,24,"��D�����ֶ�����ģʽ",24,1);
	POINT_COLOR=YELLOW;	
	Show_Str(370,785,110,12,"Company:Fish Rush",12,1);
}


void GUI_ShowParam(void)
{
	LCD_Clear(BLACK);
	POINT_COLOR=YELLOW;
	Show_Str(144,20,200,24,"������ع���ģʽ",24,1);
	Show_Str(164,50,200,16,"Watch For Shoes Cab",16,1);
	LCD_DrawLine(240,70,240,790);
	POINT_COLOR = WHITE;
	Show_Str_Mid(0,70,"�������������״̬",24,240);
	Show_Str(20,120,100,16,"�¶�:",16,1);
	Show_Str(20,180,100,16,"ʪ��:",16,1);
	Show_Str(20,240,100,16,"��ζŨ��:",16,1);
	Show_Str(20,300,100,16,"��������:",16,1);
	Show_Str(20,360,100,16,"�����ʪ:",16,1);
	Show_Str(20,420,100,16,"����ģʽ:",16,1);
	Show_Str(20,480,100,16,"����ģʽ:",16,1);
	
	Show_Str_Mid(240,70,"��������״̬",24,240);
	Show_Str(260,120,100,16,"״̬:",16,1); 		//����״̬
	Show_Str(260,180,100,16,"IP��ַ:",16,1);
	Show_Str(260,240,100,16,"�˿ں�:",16,1);
	Show_Str(260,300,100,16,"��ǰʱ��:",16,1);
	
	Show_Str(250,500,230,24,"��A���ص�������",24,1);
	
	POINT_COLOR=YELLOW;
	Show_Str(370,785,110,12,"Company:Fish Rush",12,1);

}

void GUI_Internet(void)
{
	LCD_Clear(BLACK);
	POINT_COLOR=YELLOW;
	Show_Str(144,20,200,24,"��Ʒ��������ģʽ",24,1);
	Show_Str(164,50,200,16,"Internet Config Mode",16,1);
	LCD_DrawLine(0,85,480,85);
	POINT_COLOR = WHITE;
	Show_Str_Mid(0,150,"��B����·����IP��ַ",24,240);
	Show_Str_Mid(0,250,"��C����·������������",24,240);
	Show_Str_Mid(0,350,"��Dȷ�ϲ�����",24,240);
	Show_Str_Mid(0,450,"��A���ص�������",24,240);
	POINT_COLOR=YELLOW;
	Show_Str(370,785,110,12,"Company:Fish Rush",12,1);
}

void GUI_Control(void)
{
	LCD_Clear(BLACK);
	POINT_COLOR=YELLOW;
	Show_Str(144,20,200,24,"�ֶ����ƹ���ģʽ",24,1);
	Show_Str(164,50,200,16,"CTRL For Shoes Cab",16,1);
	LCD_DrawLine(240,70,240,790);	
	POINT_COLOR=WHITE;
	Show_Str_Mid(0,70,"��ǰ״̬",24,240);
	Show_Str(20,120,100,16,"�����ʪ:",16,1);
	Show_Str(20,180,100,16,"����ģʽ:",16,1);
	Show_Str(20,240,100,16,"����ģʽ:",16,1);
	Show_Str_Mid(240,150,"��B��/�رո���",24,240);
	Show_Str_Mid(240,250,"��C��/�رպ���",24,240);
	Show_Str_Mid(240,350,"��D��/�رճ���",24,240);
	Show_Str_Mid(240,450,"��A���ؿ�ʼ����",24,240);
	
	POINT_COLOR=YELLOW;
	Show_Str(370,785,110,12,"Company:Fish Rush",12,1);	
}
