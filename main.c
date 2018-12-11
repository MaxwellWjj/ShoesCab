#include "public.h"

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

int main(void)
{        
	Main_Init();				//初始化
	ShoesCab_Working(); //鞋柜工作
}

//******************************************重要事项********************************************************//
/*

1.ESP8266配合KEIL这个垃圾编译器会造成极其玄学的问题，增加变量请慎重，改变时序请慎重
2.对照AD去改引脚,主要是传感器和开关引脚
3.千万别接紫外灯,意思一下就好
4.我的想法是MQ135放中间,剩下的4个传感器放四个角
5.继电器放中间,好连接一些（个人意见）
6.自己画的那个板子，供电流一定要足够大
7.DCDC只给32供电,32出来给传感器供电,其他的继电器、大电流的PTC加热片、都是开关电源供电

*/









