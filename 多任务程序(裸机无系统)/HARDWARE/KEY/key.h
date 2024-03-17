#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK精英STM32开发板
//按键驱动代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2012/9/3
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define WK_UP PAin(0)	//PA0  WK_UP

#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//读取按键0
#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//读取按键1
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//读取按键3(WK_UP) 

 
#define KEY0_PRES 	1<<0	//KEY0按下
#define KEY1_PRES	  1<<1	//KEY1按下
#define WKUP_PRES   1<<2	//KEY_UP按下(即WK_UP/KEY_UP)
/*定义按键相关宏***************************************************************************/

/*定义键值********************************************************************************/
typedef enum {	KEY_IDLE=0,
				KEY0_S=1,KEY1_S=2,WKUP_S=3,KEY0_3=4,KEY1_3=5,WKUP_3=6,
			  } KeyType; 

//定义延时值
#define KEY_DELAY_SHORT  	8					//按键延时为多少中断单位，一个中断单位为10ms
#define KEY_DELAY3S      	300					//按键延时为多少中断单位，一个中断单位为10ms

/*****************************************************************************************
通用按键程序
******************************************************************************************/

typedef enum {FREE=0,DOWNEDGE=1,DOWN=2,UPEDGE=3} keystaus; 


//读取按键结构体
typedef volatile struct{
	unsigned char Read_KEY1;
	unsigned char Read_KEY0;
	unsigned char Read_WKUP;
	unsigned char Read_Key_Value;
}Read_Key_Value_Struct;




//按键寄存器结构体
typedef volatile struct{
	unsigned char Value_Cur;
	unsigned char Value_Last;
	unsigned char Flag;			
	keystaus Status;									//0:FREE,1:DOWNEDGE,2:DOWN,3:UPEDGE/
	KeyType Value;	
	unsigned short Delay;
	Read_Key_Value_Struct Read_Key_Value;									//0:FREE,1:DOWNEDGE,2:DOWN,3:UPEDGE/
}Key_Struct;

extern void KEY_Init(void);
extern unsigned char KeyRead(void);

extern void KeyScan(void);
extern void KeyDeal(void);

extern Key_Struct Key;

#endif

