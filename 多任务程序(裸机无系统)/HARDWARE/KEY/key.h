#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define WK_UP PAin(0)	//PA0  WK_UP

#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//��ȡ����0
#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//��ȡ����1
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����3(WK_UP) 

 
#define KEY0_PRES 	1<<0	//KEY0����
#define KEY1_PRES	  1<<1	//KEY1����
#define WKUP_PRES   1<<2	//KEY_UP����(��WK_UP/KEY_UP)
/*���尴����غ�***************************************************************************/

/*�����ֵ********************************************************************************/
typedef enum {	KEY_IDLE=0,
				KEY0_S=1,KEY1_S=2,WKUP_S=3,KEY0_3=4,KEY1_3=5,WKUP_3=6,
			  } KeyType; 

//������ʱֵ
#define KEY_DELAY_SHORT  	8					//������ʱΪ�����жϵ�λ��һ���жϵ�λΪ10ms
#define KEY_DELAY3S      	300					//������ʱΪ�����жϵ�λ��һ���жϵ�λΪ10ms

/*****************************************************************************************
ͨ�ð�������
******************************************************************************************/

typedef enum {FREE=0,DOWNEDGE=1,DOWN=2,UPEDGE=3} keystaus; 


//��ȡ�����ṹ��
typedef volatile struct{
	unsigned char Read_KEY1;
	unsigned char Read_KEY0;
	unsigned char Read_WKUP;
	unsigned char Read_Key_Value;
}Read_Key_Value_Struct;




//�����Ĵ����ṹ��
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

