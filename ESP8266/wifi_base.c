/************************************************
Project:	    "Ь��ͬѧ"����Ь�����ϵͳ
Version:			v2.0(Using RTOS)
Author:       Tony Wu
College:      HuaZhong University of Science and Technology
Using MCU:    STM32F407ZET6
OS:           FreeRTOS
Using Module: ESP-8266(Which is used for Wi-Fi connection), DHT11, DS18B20, MQ-135
Tools:				������,�����ӷ�����,PTC����Ƭ
Support:			����ԭ��
************************************************/

#include "wifi_base.h"
#include "public.h"
#include "stdlib.h"

#define TEMPERATURE 25  //��ʼ�¶���ֵ
#define HUMIDITY 60			//��ʼʪ����ֵ
#define AIRQUALITY 200  //��ʼ����������ֵ

/****************************************ȫ�ֱ���***********************************************/
extern __IO u32 ADC_ConvertedValue;  //MQ-135ͨ��DMA-ADCת���ġ�����������ֵ
int flag_send = 0;//���ͱ�־
int count = 0;//������
u8 atk_8266_wait_for_init(void);	//��ʼ���ȴ�����
void Show_Welcome(void);	//��ӭ����
/****************************************ȫ�ֱ���***********************************************/

//����
void ShoesCab_Working(void)
{

	u8 netpro=1;   //����ģʽ	
	u8 key;				 //����
	int keyvalue = 0;  //�������
	u8 ipbuf[16]; 	//ip����
	u8 *p;  				//ip����ָ��
	u8 res=0;
	u8 constate=0;
	u16 rlen=0;

	int temperature;  //�¶�
	int temperature_dht11; //dht11�¶�
	int humidity; //ʪ��
	int airquality;//��������
	
	//������״̬��־
	int dry = 0;	int keepwarm = 0;	int deodorization = 0;
	
	//������״̬����
	const u8 *switch_state[2] = {"�ر�","����"};
	
	int state_flag = 0;//״̬����־
	int state_change = 0; //״̬���л�
	
	int temperature_threshold; //�¶���ֵ(����������ʱ�ı�)
	int humidity_threshold;    //ʪ����ֵ(����������ʱ�ı�)
	int airquality_threshold;	 //����������ֵ(����������ʱ�ı�)
	
	u32 true_temp = 20;
	
	Show_Welcome();
	
//*****************************************************ESP8266��ʼ��********************************************************//	
	
  p=mymalloc(SRAMIN,32);				
	atk_8266_send_cmd("AT+CWMODE=1","OK",50);	
	atk_8266_send_cmd("AT+RST","OK",20);		
	delay_ms(1000);       
	delay_ms(1000);
	delay_ms(1000);
	delay_ms(1000);
	
	//����Wifi
	sprintf((char*)p,"AT+CWJAP=\"%s\",\"%s\"",wifista_ssid,wifista_password);
	while(atk_8266_send_cmd(p,"WIFI GOT IP",300));				
	netpro=atk_8266_wait_for_init();	
	
	//���ӷ�����
	LCD_Clear(BLACK);
	POINT_COLOR=RED;
	Show_Str_Mid(0,30,"��������WIFI",16,240); 
	Show_Str(30,50,200,16,"��������WIFIģ��,���Ե�...",12,1);
	atk_8266_send_cmd("AT+CIPMUX=0","OK",20);   
	sprintf((char*)p,"AT+CIPSTART=\"TCP\",\"%s\",%s",(u8*)Server,(u8*)portnum);   
	while(atk_8266_send_cmd(p,"OK",200))
	{
			LCD_Clear(BLACK);
			POINT_COLOR=RED;
			Show_Str(30,80,400,24,"���ӷ�����ʧ��,�������������",24,0); 
	}	
	
	//��ȡ������Ϣ
	atk_8266_get_wanip(ipbuf);
	
	//����͸��ģʽ
	atk_8266_send_cmd("AT+CIPMODE=1","OK",200);
	
	//����͸��ģʽ
	while(atk_8266_send_cmd("AT+CIPSEND","OK",100)){
		LCD_Clear(BLACK);
		POINT_COLOR=RED;
		Show_Str(30,80,400,24,"�޷�����͸��ģʽ",24,0); 
	}
	
	GUI_based();	
	//Show_Str(30,700,300,16,p,16,1);			
	POINT_COLOR = WHITE;
	keyvalue = 20;
	
	//��ֵ��ʼ��
	temperature_threshold = TEMPERATURE;
	humidity_threshold = HUMIDITY;
	airquality_threshold = AIRQUALITY;	

	//������ʱ��,׼����������
	TIM3_Int_Init(1000-1,8400-1);	//��ʱ��ʱ��84M����Ƶϵ��8400������84M/8400=10Khz�ļ���Ƶ�ʣ�����1000��Ϊ100ms     

	//u3_printf("STM32OK\r\n");//���������������
//*****************************************************ESP8266��ʼ��********************************************************//	

//*********************************************************����*************************************************************//	
	
	while(1)
	{			
		
		//�������
		keyvalue = KeyBoard_GetValue();
		LCD_Fill(300,700,330,730,BLACK);
		LCD_ShowxNum(300,700,keyvalue,2,16,1);
		if(keyvalue==3) {state_flag = 0; state_change = 1;}//�ǵ�Ҫ��
		if(keyvalue==7&&state_flag == 0) {state_flag = 1; state_change = 1;}
		if(keyvalue==11&&state_flag ==0) {state_flag = 2; state_change = 1;}
		if(keyvalue==15&&state_flag ==0) {state_flag = 3; state_change = 1;}
		if(keyvalue==15&&state_flag == 3) {if(deodorization == 1)deodorization = 0; else deodorization = 1;LCD_Fill(140,240,220,260,BLACK);	} //�ֶ�����������������
		if(keyvalue==11&&state_flag == 3) {if(keepwarm == 1 )keepwarm = 0; else keepwarm = 1;LCD_Fill(140,180,220,200,BLACK);}  //�ֶ��������¹���
		if(keyvalue==7&&state_flag == 3) {if(dry == 1)dry = 0; else dry = 1; LCD_Fill(140,120,220,140,BLACK);}//�ֶ����������ʪ����
		
		//״̬�ı�,�����л�
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
		
		//״̬�����������ʾ
		//1.�������ģʽ
		if(state_flag == 1){
			true_temp = temperature/10;
			LCD_Fill(140,120,200,140,BLACK);
			LCD_Fill(140,180,200,200,BLACK);
			LCD_Fill(140,240,200,260,BLACK);
			LCD_ShowxNum(140,120,true_temp,2,16,1);
			LCD_ShowxNum(140,180,humidity,2,16,1);
			LCD_ShowxNum(140,240,airquality,3,16,1);
			Show_Str(110,300,125,16,"����,����7-15��",16,1);
			LCD_Fill(140,360,200,380,BLACK);
			LCD_Fill(140,420,200,440,BLACK);
			LCD_Fill(140,480,200,500,BLACK);
			Show_Str(140,360,50,16,(u8*)switch_state[dry],16,1);
			Show_Str(140,420,50,16,(u8*)switch_state[keepwarm],16,1);
			Show_Str(140,480,50,16,(u8*)switch_state[deodorization],16,1);
			Show_Str(350,120,80,16,"���ӳɹ�",16,1); 
			Show_Str(330,180,120,16,ipbuf,16,1); 
			Show_Str(380,240,80,16,"8008",16,1);
			Show_Str(350,300,130,16,"2018��12��9��",16,1);
		}
		
		//2.�ֶ�����ģʽ
		if(state_flag == 3){
				Show_Str(150,120,80,16,(u8*)switch_state[dry],16,1);
				Show_Str(150,180,80,16,(u8*)switch_state[keepwarm],16,1);
				Show_Str(150,240,80,16,(u8*)switch_state[deodorization],16,1);	
		}
		
		//�Զ����¿���
		if(keepwarm == 1){
			if(temperature <= temperature_threshold) Heat = 1;
			else Heat = 0;
		}
		
		//����GPIO���̵���,����������Ӧ�Ŀ���
		if(dry == 1) Heat = 1;
		if(deodorization == 1) {Anion1 = 1;Anion2 = 1; Light1 = 1; Light2 = 1;}
		
		//��������
		if(flag_send ==1){	
			//���������²���	
		  temperature=DS18B20_Get_Temp();	
		  DHT11_Read_Data(&temperature_dht11,&humidity);
		  airquality=ADC_ConvertedValue;
	    u3_printf("STM32OK\r\n");//���������������	
			sprintf((char*)p,"Temperature %d , Humidity %d ,Airquality %d ,\r\n",temperature/10,humidity,airquality);
			Show_Str(30,750,200,16,p,16,1);
			u3_printf("%s",p);
			LED0 = ~LED0;
			delay_ms(50);
			flag_send = 0;
		}

		//������յ�������
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
		
//*********************************************************����*************************************************************//	

	}
}


//*********************************************************�˻�������������*************************************************************//	

//��ʼ���ȴ�����
u8 atk_8266_wait_for_init(void) 
{
	u8 key=0;
	u8 netpro=1;
	POINT_COLOR=BLUE;
	Show_Str_Mid(0,450,"��A����",24,480);
	while(1)
	{
		key=KeyBoard_GetValue(); 
		if(key==3)break;        
		delay_ms(10);
		atk_8266_at_response(1);
	} 
	return netpro;
} 

//��ʼ����Ϻ�Ļ�ӭ����
void Show_Welcome(void)
{
	LCD_Clear(BLACK);
	POINT_COLOR=WHITE;
	Show_Str_Mid(0,380,"��ӭʹ��Ь��ͬѧ���ܼҾӹܼ�",24,480);
}

//*********************************************************�˻�������������*************************************************************//	


//**********************************************************��ʱ���жϷ���*************************************************************//	

//��ʱ��3�жϷ�����
void TIM3_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)==SET) //����ж�
	{
		LED1=!LED1;//DS1��ת
		count += 1;
		if(count == 100) {
			count = 0;
			LED1=!LED1;//DS1��ת
			if(flag_send==0)flag_send = 1;
		}
	}
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);  //����жϱ�־λ
}


//**********************************************************��ʱ���жϷ���*************************************************************//	

