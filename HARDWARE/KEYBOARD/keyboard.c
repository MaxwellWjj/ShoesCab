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
	GPIO_Init(GPIOG, &GPIO_InitStructuress); //定义输出的PG0-PG3为上拉推挽输出
	GPIO_InitStructuress.GPIO_Pin =GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_8;   
	GPIO_InitStructuress.GPIO_Mode =GPIO_Mode_IN;
	GPIO_InitStructuress.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructuress.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_Init(GPIOG, &GPIO_InitStructuress); //定义输入的PG4-PG6/PG8为下拉输入
}

int KeyBoard_GetValue(void)  //得到矩阵键盘的值
{
	int KeyValue = 0;  
	u16 WriteVal = 0;  
 
	GPIO_Write(GPIOG,(GPIOG->ODR & 0xfff0 | 0xf));  //PG0-PG3输出高
 
	if((GPIOG->IDR & 0x0170) == 0x0000)  //检测PG4-PG7是否有高电平
	{
		return 20;
	}
	else  //消抖
	{
		delay_ms(5);  //延时5毫秒 用来消抖
		if((GPIOG->IDR & 0x0170) == 0x0000)  //确实有高电平,但是是抖动造成的
		{
			return 20;  //返回
		}
	}
 
	GPIO_Write(GPIOG, (GPIOG->ODR & 0xfff0 | 0x1 ));  //PG0输出高,下面的代码同理
	switch(GPIOG->IDR & 0x0170)  //对PG4-PG7进行判断,下面的代码同理
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
