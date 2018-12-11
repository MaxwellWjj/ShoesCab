#ifndef __DS18B20_H
#define __DS18B20_H 
#include "sys.h"   
#include "public.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK STM32F407������
//DS18B20��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//��������:2014/5/7
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2014-2024
//All rights reserved										  
//////////////////////////////////////////////////////////////////////////////////

//IO��������
#define DS18B20_IO_IN()  {GPIOA->MODER&=~(3<<(4*2));GPIOA->MODER|=0<<4*2;}	//PG9����ģʽ
#define DS18B20_IO_OUT() {GPIOA->MODER&=~(3<<(4*2));GPIOA->MODER|=1<<4*2;} 	//PG9���ģʽ
 
////IO��������											   
#define	DS18B20_DQ_OUT PAout(4) //���ݶ˿�	PG9
#define	DS18B20_DQ_IN  PAin(4)  //���ݶ˿�	PG9 
   	
u8 DS18B20_Init(void);			//��ʼ��DS18B20
int DS18B20_Get_Temp(void);	//��ȡ�¶�
void DS18B20_Start(void);		//��ʼ�¶�ת��
void DS18B20_Write_Byte(u8 dat);//д��һ���ֽ�
u8 DS18B20_Read_Byte(void);		//����һ���ֽ�
u8 DS18B20_Read_Bit(void);		//����һ��λ
u8 DS18B20_Check(void);			//����Ƿ����DS18B20
void DS18B20_Rst(void);			//��λDS18B20    
#endif















