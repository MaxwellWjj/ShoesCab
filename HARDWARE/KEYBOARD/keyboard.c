#include "keyboard.h"
#include "public.h"

void KeyBoard_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructuress;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);             
	GPIO_InitStructuress.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;  
	GPIO_InitStructuress.GPIO_Mode = GPIO_Mode_OUT;      
	GPIO_InitStructuress.GPIO_OType = GPIO_OType_PP;                                   
	GPIO_InitStructuress.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructuress.GPIO_PuPd =GPIO_PuPd_UP;                                      
	GPIO_Init(GPIOG, &GPIO_InitStructuress); //���������PG0-PG3Ϊ�����������
	GPIO_InitStructuress.GPIO_Pin =GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_8;   
	GPIO_InitStructuress.GPIO_Mode =GPIO_Mode_IN;
	GPIO_InitStructuress.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructuress.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOG, &GPIO_InitStructuress); //���������PG4-PG6/PG8Ϊ��������
}

int KeyBoard_GetValue(void)  //�õ�������̵�ֵ
{
	int KeyValue = 0;  
	u16 WriteVal = 0;  
 
	GPIO_Write(GPIOG,(GPIOG->ODR & 0xfff0 | 0xf));  //PG0-PG3�����
 
	if((GPIOG->IDR & 0x0170) == 0x0000)  //���PG4-PG7�Ƿ��иߵ�ƽ
	{
		return 20;
	}
	else  //����
	{
		delay_ms(5);  //��ʱ5���� ��������
		if((GPIOG->IDR & 0x0170) == 0x0000)  //ȷʵ�иߵ�ƽ,�����Ƕ�����ɵ�
		{
			return 20;  //����
		}
	}
 
	GPIO_Write(GPIOG, (GPIOG->ODR & 0xfff0 | 0x1 ));  //PG0�����,����Ĵ���ͬ��
	switch(GPIOG->IDR & 0x0170)  //��PG4-PG7�����ж�,����Ĵ���ͬ��
	{
		case 0x0010:KeyValue = 15;
		break;
 
		case 0x0020:KeyValue = 11;
		break;
 
		case 0x0040:KeyValue = 7;
		break;
 
		case 0x0100:KeyValue = 3;
		break;
	}
 
	GPIO_Write(GPIOG, (GPIOG->ODR & 0xfff0 | 0x2));  
	switch(GPIOG->IDR & 0x0170)  
	{
		case 0x0010:KeyValue = 14;
		break;
		
		case 0x0020:KeyValue = 10;
		break;
		
		case 0x0040:KeyValue = 6;
		break;
 
		case 0x0100:KeyValue = 2;
		break; 
	}
 
	GPIO_Write(GPIOG, (GPIOG->ODR & 0xfff0 | 0x4));  
	switch(GPIOG->IDR & 0x0170) 
	{
		case 0x0010:KeyValue = 13;
		break;
		
		case 0x0020:KeyValue = 9;
		break;
		
		case 0x0040:KeyValue = 5;
		break;
 
		case 0x0100:KeyValue = 1;
		break; 
	}
 
	GPIO_Write(GPIOG, (GPIOG->ODR & 0xfff0 | 0x8)); 
	switch(GPIOG->IDR & 0x0170)  
	{
		case 0x0010:KeyValue = 12;
		break;
		
		case 0x0020:KeyValue = 8;
		break;
		
		case 0x0040:KeyValue = 4;
		break;
 
		case 0x0100:KeyValue = 0;
		break; 
	}
 
	return KeyValue;
}
