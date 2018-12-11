#include "public.h"

void Main_Init(void)
{
	u8 fontok=0; 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);  //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	usart3_init(115200);  //初始化串口3波特率为115200
	LED_Init();					//初始化LED  
 	LCD_Init();					//LCD初始化  
 	KEY_Init();					//按键初始化  
	KeyBoard_Init();		//	矩阵键盘初始化
	Relay_Init();				//继电器控制初始化
	//W25QXX_Init();				//初始化W25Q128
	tp_dev.init();				//初始化触摸屏
	usmart_dev.init(168);		//初始化USMART
	my_mem_init(SRAMIN);		//初始化内部内存池 
	my_mem_init(SRAMCCM);		//初始化CCM内存池 
	//exfuns_init();				//为fatfs相关变量申请内存  
  //f_mount(fs[0],"0:",1); 		//挂载SD卡 
 	//f_mount(fs[1],"1:",1); 		//挂载FLASH.
	LCD_ShowString(30,80,300,16,16,"Initialize DHT11,DS18B20,MQ135");
	while(DS18B20_Init()||DHT11_Init())	//DS18B20
	{
		POINT_COLOR=BLACK;
		LCD_ShowString(30,130,200,16,16,"Initialing...Please Wait.");
		delay_ms(200);
		LCD_Fill(30,130,239,130+16,WHITE);
 		delay_ms(200);
	}   
	//fontok=font_init();		
	Rheostat_Init();
}