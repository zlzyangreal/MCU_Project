#ifndef _MAIN_H_
#define _MAIN_H_
#include "stm32f10x.h"



typedef enum {FALSE = 0, TRUE = !FALSE} bool;

/********************************************************************************************************
//定义系统状态枚举类
********************************************************************************************************/

/*定义系统模式枚举类*/
typedef enum {MAIN_MODE1=0, MAIN_MODE2=1, MAIN_MODE3=2}
			  Sys_State_Enum;


typedef enum {MAINMODE1_SUBMODE1=0, MAINMODE1_SUBMODE2=1, MAINMODE1_SUBMODE3=2}
			  Sub_MAIN_MODE1_Enum;

typedef enum {MAINMODE2_SUBMODE1=0, MAINMODE2_SUBMODE2=1, MAINMODE2_SUBMODE3=2}
			  Sub_MAIN_MODE2_Enum;

typedef enum {MAINMODE3_SUBMODE1=0, MAINMODE3_SUBMODE2=1, MAINMODE3_SUBMODE3=2}
			  Sub_MAIN_MODE3_Enum;


/********************************************************************************************************
//定义系统模式结构体
********************************************************************************************************/
typedef struct {
    Sys_State_Enum      Main_Mode;     //
    Sub_MAIN_MODE1_Enum      Sub_MAIN_MODE1;     //
    Sub_MAIN_MODE2_Enum      Sub_MAIN_MODE2;     //
    Sub_MAIN_MODE3_Enum      Sub_MAIN_MODE3;     //
}Sys_Mode_Struct;


/********************************************************************************************************
//定义系统全局变量结构体
********************************************************************************************************/

typedef struct {
    Sys_Mode_Struct     Mode;                     //系统模式
    bool Flag_LCD_Update;	       //LCD刷新标志位
    
}Sys_Struct;



extern unsigned char Flag_Timer_True,Count_Timer; 
extern Sys_Struct Sys;


#endif
