/************************************************
Project:	    "鞋柜同学"智能鞋柜控制系统
Version:			v2.0(Using RTOS)
Author:       Tony Wu
College:      HuaZhong University of Science and Technology
Using MCU:    STM32F407ZET6
OS:           FreeRTOS
Using Module: ESP-8266(Which is used for Wi-Fi connection), DHT11, DS18B20, MQ-135
Tools:				紫外光灯,负离子发生器,PTC加热片
Support:			正点原子
************************************************/

#include "wifi_base.h"
#include "public.h"
#include "stdlib.h"

#define TEMPERATURE 25  //初始温度阈值
#define HUMIDITY 60			//初始湿度阈值
#define AIRQUALITY 200  //初始空气质量阈值

/****************************************全局变量***********************************************/
extern __IO u32 ADC_ConvertedValue;  //MQ-135通过DMA-ADC转化的“空气质量”值
int flag_send = 0;//发送标志
int count = 0;//计数器
u8 atk_8266_wait_for_init(void);	//初始化等待界面
void Show_Welcome(void);	//欢迎界面
/****************************************全局变量***********************************************/

//工作
void ShoesCab_Working(void)
{

	u8 netpro=1;   //网络模式	
	u8 key;				 //按键
	int keyvalue = 0;  //矩阵键盘
	u8 ipbuf[16]; 	//ip缓存
	u8 *p;  				//ip缓存指针
	u8 res=0;
	u8 constate=0;
	u16 rlen=0;

	int temperature;  //温度
	int temperature_dht11; //dht11温度
	int humidity; //湿度
	int airquality;//空气质量
	
	//各开关状态标志
	int dry = 0;	int keepwarm = 0;	int deodorization = 0;
	
	//各开关状态数组
	const u8 *switch_state[2] = {"关闭","开启"};
	
	int state_flag = 0;//状态机标志
	int state_change = 0; //状态机切换
	
	int temperature_threshold; //温度阈值(可以在运行时改变)
	int humidity_threshold;    //湿度阈值(可以在运行时改变)
	int airquality_threshold;	 //空气质量阈值(可以在运行时改变)
	
	u32 true_temp = 20;
	
	Show_Welcome();
	
//*****************************************************ESP8266初始化********************************************************//	
	
  p=mymalloc(SRAMIN,32);				
	atk_8266_send_cmd("AT+CWMODE=1","OK",50);	
	atk_8266_send_cmd("AT+RST","OK",20);		
	delay_ms(1000);       
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	
	//连接Wifi
	sprintf((char*)p,"AT+CWJAP=\"%s\",\"%s\"",wifista_ssid,wifista_password);
	while(atk_8266_send_cmd(p,"WIFI GOT IP",300));				
	netpro=atk_8266_wait_for_init();	
	
	//连接服务器
	LCD_Clear(BLACK);
	POINT_COLOR=RED;
	Show_Str_Mid(0,30,"正在连接WIFI",16,240); 
	Show_Str(30,50,200,16,"正在配置WIFI模块,请稍等...",12,1);
	atk_8266_send_cmd("AT+CIPMUX=0","OK",20);   
	sprintf((char*)p,"AT+CIPSTART=\"TCP\",\"%s\",%s",(u8*)Server,(u8*)portnum);   
	while(atk_8266_send_cmd(p,"OK",200))
	{
			LCD_Clear(BLACK);
			POINT_COLOR=RED;
			Show_Str(30,80,400,24,"连接服务器失败,请检查服务器配置",24,0); 
	}	
	
	//获取连接信息
	atk_8266_get_wanip(ipbuf);
	
	//开启透传模式
	atk_8266_send_cmd("AT+CIPMODE=1","OK",200);
	
	//进入透传模式
	while(atk_8266_send_cmd("AT+CIPSEND","OK",100)){
		LCD_Clear(BLACK);
		POINT_COLOR=RED;
		Show_Str(30,80,400,24,"无法进入透传模式",24,0); 
	}
	
	GUI_based();	
	//Show_Str(30,700,300,16,p,16,1);			
	POINT_COLOR = WHITE;
	keyvalue = 20;
	
	//阈值初始化
	temperature_threshold = TEMPERATURE;
	humidity_threshold = HUMIDITY;
	airquality_threshold = AIRQUALITY;	

	//开启定时器,准备发送数据
	TIM3_Int_Init(1000-1,8400-1);	//定时器时钟84M，分频系数8400，所以84M/8400=10Khz的计数频率，计数1000次为100ms     

	//u3_printf("STM32OK\r\n");//与服务器建立连接
//*****************************************************ESP8266初始化********************************************************//	

//*********************************************************工作*************************************************************//	
	
	while(1)
	{			
		
		//矩阵键盘
		keyvalue = KeyBoard_GetValue();
		LCD_Fill(300,700,330,730,BLACK);
		LCD_ShowxNum(300,700,keyvalue,2,16,1);
		if(keyvalue==3) {state_flag = 0; state_change = 1;}//记得要改
		if(keyvalue==7&&state_flag == 0) {state_flag = 1; state_change = 1;}
		if(keyvalue==11&&state_flag ==0) {state_flag = 2; state_change = 1;}
		if(keyvalue==15&&state_flag ==0) {state_flag = 3; state_change = 1;}
		if(keyvalue==15&&state_flag == 3) {if(deodorization == 1)deodorization = 0; else deodorization = 1;LCD_Fill(140,240,220,260,BLACK);	} //手动开启除臭消毒功能
		if(keyvalue==11&&state_flag == 3) {if(keepwarm == 1 )keepwarm = 0; else keepwarm = 1;LCD_Fill(140,180,220,200,BLACK);}  //手动开启恒温功能
		if(keyvalue==7&&state_flag == 3) {if(dry == 1)dry = 0; else dry = 1; LCD_Fill(140,120,220,140,BLACK);}//手动开启干燥除湿功能
		
		//状态改变,界面切换
		if(state_change==1){
				switch(state_flag)
				{
					case 0: FirstTask(); break;
					case 1: WatchingParam(); break;
					case 2: InternetConfig(); break;
					case 3: ControlByuser(); break;
				}
				state_change = 0;
		}
		
		//状态机配合数据显示
		//1.参数监控模式
		if(state_flag == 1){
			true_temp = temperature/10;
			LCD_Fill(140,120,200,140,BLACK);
			LCD_Fill(140,180,200,200,BLACK);
			LCD_Fill(140,240,200,260,BLACK);
			LCD_ShowxNum(140,120,true_temp,2,16,1);
			LCD_ShowxNum(140,180,humidity,2,16,1);
			LCD_ShowxNum(140,240,airquality,3,16,1);
			Show_Str(110,300,125,16,"多云,气温7-15度",16,1);
			LCD_Fill(140,360,200,380,BLACK);
			LCD_Fill(140,420,200,440,BLACK);
			LCD_Fill(140,480,200,500,BLACK);
			Show_Str(140,360,50,16,(u8*)switch_state[dry],16,1);
			Show_Str(140,420,50,16,(u8*)switch_state[keepwarm],16,1);
			Show_Str(140,480,50,16,(u8*)switch_state[deodorization],16,1);
			Show_Str(350,120,80,16,"连接成功",16,1); 
			Show_Str(330,180,120,16,ipbuf,16,1); 
			Show_Str(380,240,80,16,"8008",16,1);
			Show_Str(350,300,130,16,"2018年12月9日",16,1);
		}
		
		//2.手动控制模式
		if(state_flag == 3){
				Show_Str(150,120,80,16,(u8*)switch_state[dry],16,1);
				Show_Str(150,180,80,16,(u8*)switch_state[keepwarm],16,1);
				Show_Str(150,240,80,16,(u8*)switch_state[deodorization],16,1);	
		}
		
		//自动恒温控制
		if(keepwarm == 1){
			if(temperature <= temperature_threshold) Heat = 1;
			else Heat = 0;
		}
		
		//控制GPIO到继电器,进而控制相应的开关
		if(dry == 1) Heat = 1;
		if(deodorization == 1) {Anion1 = 1;Anion2 = 1; Light1 = 1; Light2 = 1;}
		
		//发送数据
		if(flag_send ==1){	
			//传感器更新参数	
		  temperature=DS18B20_Get_Temp();	
		  DHT11_Read_Data(&temperature_dht11,&humidity);
		  airquality=ADC_ConvertedValue;
	    u3_printf("STM32OK\r\n");//与服务器建立连接	
			sprintf((char*)p,"Temperature %d , Humidity %d ,Airquality %d ,\r\n",temperature/10,humidity,airquality);
			Show_Str(30,750,200,16,p,16,1);
			u3_printf("%s",p);
			LED0 = ~LED0;
			delay_ms(50);
			flag_send = 0;
		}

		//如果接收到了数据
		if(USART3_RX_STA&0X8000)		
		{ 
			rlen=USART3_RX_STA&0X7FFF;	
			USART3_RX_BUF[rlen]=0;	
			POINT_COLOR=YELLOW;
			LCD_Fill(380,700,480,800,BLACK);
			Show_Str(380,700,100,16,USART3_RX_BUF,16,1);
			if(USART3_RX_BUF[0] == '1') {dry = 1;LCD_Fill(140,120,220,140,BLACK);}
			if(USART3_RX_BUF[0] == '0') {dry = 0;LCD_Fill(140,120,220,140,BLACK);}
			if(USART3_RX_BUF[1] == '1') {keepwarm = 1;LCD_Fill(140,180,220,200,BLACK);}
			if(USART3_RX_BUF[1] == '0') {keepwarm = 0;LCD_Fill(140,180,220,200,BLACK);}
			if(USART3_RX_BUF[2] == '1') {deodorization = 1;LCD_Fill(140,240,220,260,BLACK);}
			if(USART3_RX_BUF[2] == '0') {deodorization = 0;LCD_Fill(140,240,220,260,BLACK);}
			USART3_RX_STA=0;
		}
		
//*********************************************************工作*************************************************************//	

	}
}


//*********************************************************人机交互辅助函数*************************************************************//	

//初始化等待界面
u8 atk_8266_wait_for_init(void) 
{
	u8 key=0;
	u8 netpro=1;
	POINT_COLOR=BLUE;
	Show_Str_Mid(0,450,"按A进入",24,480);
	while(1)
	{
		key=KeyBoard_GetValue(); 
		if(key==3)break;        
		delay_ms(10);
		atk_8266_at_response(1);
	} 
	return netpro;
} 

//初始化完毕后的欢迎界面
void Show_Welcome(void)
{
	LCD_Clear(BLACK);
	POINT_COLOR=WHITE;
	Show_Str_Mid(0,380,"欢迎使用鞋柜同学智能家居管家",24,480);
}

//*********************************************************人机交互辅助函数*************************************************************//	


//**********************************************************定时器中断发送*************************************************************//	

//定时器3中断服务函数
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //溢出中断
	{
		LED1=!LED1;//DS1翻转
		count += 1;
		if(count == 100) {
			count = 0;
			LED1=!LED1;//DS1翻转
			if(flag_send==0)flag_send = 1;
		}
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //清除中断标志位
}


//**********************************************************定时器中断发送*************************************************************//	

