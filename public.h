#ifndef _PUBLIC_H_
#define _PUBLIC_H_

#include "sys.h"
#include "delay.h"  
#include "usart.h"   
#include "led.h"
#include "lcd.h"
#include "key.h"  
#include "usmart.h"  
#include "sram.h"   
#include "malloc.h" 
#include "sdio_sdcard.h"
#include "ff.h"  
#include "exfuns.h"    
#include "fontupd.h"
#include "text.h"	
#include "usmart.h"	
#include "touch.h"		
#include "usart3.h"
#include "common.h" 
#include "dht11.h"
#include "ds18b20.h"
#include "bsp_adc.h"
#include "GUI.h"
#include "wifi_base.h"
#include "keyboard.h"
#include "w25qxx.h"
#include "relay.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

void Main_Init(void);

#endif

