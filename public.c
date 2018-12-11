#include "public.h"

void Main_Init(void)
{
	u8 fontok=0; 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);  //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	usart3_init(115200);  //��ʼ������3������Ϊ115200
	LED_Init();					//��ʼ��LED  
 	LCD_Init();					//LCD��ʼ��  
 	KEY_Init();					//������ʼ��  
	KeyBoard_Init();		//	������̳�ʼ��
	Relay_Init();				//�̵������Ƴ�ʼ��
	//W25QXX_Init();				//��ʼ��W25Q128
	tp_dev.init();				//��ʼ��������
	usmart_dev.init(168);		//��ʼ��USMART
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ�� 
	my_mem_init(SRAMCCM);		//��ʼ��CCM�ڴ�� 
	//exfuns_init();				//Ϊfatfs��ر��������ڴ�  
  //f_mount(fs[0],"0:",1); 		//����SD�� 
 	//f_mount(fs[1],"1:",1); 		//����FLASH.
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