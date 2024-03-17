#include "stm32f10x.h"
#include "key.h"
#include "sys.h" 
#include "delay.h"
#include "lcd.h"
#include "main.h"

Key_Struct Key;

void KEY_Init(void);
unsigned char KeyRead(void);

void KeyScan(void);
void KeyDeal(void);

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
								    
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//使能PORTA,PORTE时钟

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_3;//KEY0-KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //设置成上拉输入
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化GPIOE4,3

	//初始化 WK_UP-->GPIOA.0	  下拉输入
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0设置成输入，默认下拉	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化GPIOA.0
}

/******************************************************************************************
名称：KeyRead
功能：
使用方法：
KeyFlag

*******************************************************************************************/
 


unsigned char KeyRead(void)
{ //
   
    



	/*  配置GPIO的模式和IO口 */
    //int_i=GPIO_ReadInputData(GPIOG);
	
	//Key.Read_Key_Value.Read_Key_Value=int_i>>3;
 
Key.Read_Key_Value.Read_KEY0=KEY0;
if(Key.Read_Key_Value.Read_KEY0==0)
 {
	Key.Read_Key_Value.Read_KEY0=1;
 }
else if(Key.Read_Key_Value.Read_KEY0==1)
 {
	Key.Read_Key_Value.Read_KEY0=0;
 }
Key.Read_Key_Value.Read_KEY0=Key.Read_Key_Value.Read_KEY0<<0;

	
Key.Read_Key_Value.Read_KEY1=KEY1;
if(Key.Read_Key_Value.Read_KEY1==0)
 {
	Key.Read_Key_Value.Read_KEY1=1;
 }
else if(Key.Read_Key_Value.Read_KEY1==1)
 {
	Key.Read_Key_Value.Read_KEY1=0;
 }
Key.Read_Key_Value.Read_KEY1=Key.Read_Key_Value.Read_KEY1<<1;

 

Key.Read_Key_Value.Read_WKUP=WK_UP;
Key.Read_Key_Value.Read_WKUP=Key.Read_Key_Value.Read_WKUP<<2;


Key.Read_Key_Value.Read_Key_Value=Key.Read_Key_Value.Read_KEY1|Key.Read_Key_Value.Read_KEY0|Key.Read_Key_Value.Read_WKUP;  
return Key.Read_Key_Value.Read_Key_Value;		
}


/******************************************************************************************
名称：KeyScan
功能：按键扫描
使用方法：设置定时器溢出中断时间为10ms，在定时器中断中调用该函数；若有按键按下，该函数修改
KeyFlag

*******************************************************************************************/
/** 
 * 
 * 
 * 
 * 
 */
void KeyScan(void)
{ //
	//有按键事件未处理完，直接退出

	static unsigned char LongKeyFlag=0;
	
	if (Key.Flag == TRUE) return;
	
	Key.Value_Last = Key.Value_Cur;
	Key.Value_Cur = KeyRead();//读取按键值函数

	switch (Key.Status)
	{
		case FREE:
			if ((Key.Value_Cur != Key.Value_Last) && (Key.Value_Cur != 0))
			{//下降沿
				Key.Status = DOWN;
				Key.Delay = 0;

				LongKeyFlag=FALSE;					
			}			
			break;
		case DOWN:
			if ((Key.Value_Cur == Key.Value_Last) && (Key.Value_Cur != 0))
			{//有按键按下

 				Key.Delay++;								
				if(Key.Delay > KEY_DELAY3S && LongKeyFlag==FALSE)
				{
					//Call_Led(2,1000);
					LongKeyFlag=TRUE;
				}	
							
				if (Key.Delay > KEY_DELAY3S) 
				{//按键时间超过三秒
					switch(Key.Value_Last)
					{
						case KEY1_PRES:
						    //UP键长按
							Key.Value = KEY1_3;
							Key.Flag=TRUE;
							break;
						case KEY0_PRES:
							//DOWN键长按
							Key.Value = KEY0_3;
							Key.Flag=TRUE;
							break;
						case WKUP_PRES:
							//DOWN键长按
							Key.Value = WKUP_3;
							Key.Flag=TRUE;
							break;
						default:
							Key.Flag=FALSE;
							Key.Value=KEY_IDLE;
						    break;					
					}					
				}	
			}
			else if(Key.Value_Cur == 0)
				{//按键松开
					if((Key.Delay < KEY_DELAY3S) && (Key.Delay > KEY_DELAY_SHORT))
					{
				   		switch(Key.Value_Last)
						{
							case KEY1_PRES:
								//上键短按
								Key.Value = KEY1_S;
								Key.Flag=TRUE;
								break;
							case KEY0_PRES:
								//Set键短按
								Key.Value = KEY0_S;
								Key.Flag=TRUE;
								break;							
							case WKUP_PRES:
								//确认键短按
								Key.Value = WKUP_S;
								Key.Flag=TRUE;
								break;							
							default:
								Key.Flag=FALSE;
								Key.Value=KEY_IDLE;
						    		break;					
						}
					}
					Key.Status=FREE;
				}

			
			break;
			 		       
		default:
			break;
	}	
		
}
/******************************************************************************************
名称：KeyDeal
功能：按键处理
使用方法：在主程序Main中调用该函数；若有按键事件，执行相应处理过程，否则直接退出
设置flash和数据
*******************************************************************************************/

void KeyDeal(void)
{

  //KeyScan();
	if(Key.Flag == FALSE) return;
	
	switch(Sys.Mode.Main_Mode)
			{
			//主模式为MAIN_MODE1状态
		   case MAIN_MODE1:
		   	 {
				 switch(Sys.Mode.Sub_MAIN_MODE1)
					 {
					 case MAINMODE1_SUBMODE1:
						 //子模式为MAINMODE1_SUBMODE1状态
						 if(Key.Value == WKUP_S)
						 {
							 //按UP键,进入主界面2
							 Sys.Mode.Main_Mode=MAIN_MODE2;
							 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE1;
						 }
						 if(Key.Value == KEY0_S)
						 {
							 //按0键,进入主界面1的子界面3
							 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE3;
						 }
						 if(Key.Value == KEY1_S)
						 {
							 //按1键,进入主界面1的子界面2
							 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE2;
						 }
					 break;
					 case MAINMODE1_SUBMODE2:
							 //子模式为MAINMODE1_SUBMODE2状态
						 if(Key.Value == WKUP_S)
						 {
							 //按UP键,进入主界面2
							 Sys.Mode.Main_Mode=MAIN_MODE2;
							 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE1;
						 }
						 if(Key.Value == KEY0_S)
						 {
							 //按0键,进入主界面1的子界面1
							 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE1;
						 }
						 if(Key.Value == KEY1_S)
						 {
							 //按1键,进入主界面1的子界面3
							 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE3;
						 }
				 
					 break;
					 case MAINMODE1_SUBMODE3:
						 //子模式为MAINMODE1_SUBMODE3状态
						 if(Key.Value == WKUP_S)
						 {
							 //按UP键,进入主界面2
							 Sys.Mode.Main_Mode=MAIN_MODE2;
							 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE1;
						 }
						 if(Key.Value == KEY0_S)
						 {
							 //按0键,进入主界面1的子界面2
							 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE2;
						 }
						 if(Key.Value == KEY1_S)
						 {
							 //按1键,进入主界面1的子界面1
							 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE1;
						 }
					 break; 
					 default:
							 
						 /*******************************************************************************************/
					 break; 
					 
					 }
									  
		   	 }
			
			 break;
				//主模式为MAIN_MODE2状态
			 case MAIN_MODE2:
			   {
				  switch(Sys.Mode.Sub_MAIN_MODE2)
					 {
					 case MAINMODE2_SUBMODE1:
						 //子模式为MAINMODE2_SUBMODE1状态
						 if(Key.Value == WKUP_S)
						 {
							 //按UP键,进入主界面3
							 Sys.Mode.Main_Mode=MAIN_MODE3;
							 Sys.Mode.Sub_MAIN_MODE3=MAINMODE3_SUBMODE1;
						 }
						 if(Key.Value == KEY0_S)
						 {
							 //按0键,进入主界面2的子界面3
							 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE3;
						 }
						 if(Key.Value == KEY1_S)
						 {
							 //按1键,进入主界面2的子界面2
							 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE2;
						 }
					 break;
					 case MAINMODE2_SUBMODE2:
							 //子模式为MAINMODE1_SUBMODE2状态
						 if(Key.Value == WKUP_S)
						 {
							 //按UP键,进入主界面3
							 Sys.Mode.Main_Mode=MAIN_MODE3;
							 Sys.Mode.Sub_MAIN_MODE3=MAINMODE3_SUBMODE1;
						 }
						 if(Key.Value == KEY0_S)
						 {
							 //按0键,进入主界面2的子界面1
							 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE1;
						 }
						 if(Key.Value == KEY1_S)
						 {
							 //按1键,进入主界面2的子界面3
							 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE3;
						 }
					 break;
						 
					 case MAINMODE2_SUBMODE3:
						 //子模式为MAINMODE2_SUBMODE3状态
						 if(Key.Value == WKUP_S)
						 {
							 //按UP键,进入主界面3
							 Sys.Mode.Main_Mode=MAIN_MODE3;
							 Sys.Mode.Sub_MAIN_MODE3=MAINMODE3_SUBMODE1;
						 }
						 if(Key.Value == KEY0_S)
						 {
							 //按0键,进入主界面2的子界面2
							 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE2;
						 }
						 if(Key.Value == KEY1_S)
						 {
							 //按1键,进入主界面2的子界面1
							 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE1;
						 }
					 break; 
						 
					 default:
					 break; 
					 
					 }	
			   }
			   break;
				 
			   //主模式为MAIN_MODE3状态
			   case MAIN_MODE3:
				 {
					 switch(Sys.Mode.Sub_MAIN_MODE3)
					 	{
						 {
					 case MAINMODE3_SUBMODE1:
						 //子模式为MAINMODE3_SUBMODE1状态
						 if(Key.Value == WKUP_S)
						 {
							 //按UP键,进入主界面1
							 Sys.Mode.Main_Mode=MAIN_MODE1;
							 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE1;
						 }
						 if(Key.Value == KEY0_S)
						 {
							 //按0键,进入主界面3的子界面3
							 Sys.Mode.Sub_MAIN_MODE3=MAINMODE3_SUBMODE3;
						 }
						 if(Key.Value == KEY1_S)
						 {
							 //按1键,进入主界面3的子界面2
							 Sys.Mode.Sub_MAIN_MODE3=MAINMODE3_SUBMODE2;
						 }
					 break;
					 case MAINMODE3_SUBMODE2:
							 //子模式为MAINMODE3_SUBMODE2状态
						 if(Key.Value == WKUP_S)
						 {
							 //按UP键,进入主界面1
							 Sys.Mode.Main_Mode=MAIN_MODE1;
							 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE1;
						 }
						 if(Key.Value == KEY0_S)
						 {
							 //按0键,进入主界面3的子界面1
							 Sys.Mode.Sub_MAIN_MODE3=MAINMODE3_SUBMODE1;
						 }
						 if(Key.Value == KEY1_S)
						 {
							 //按1键,进入主界面3的子界面3
							 Sys.Mode.Sub_MAIN_MODE3=MAINMODE3_SUBMODE3;
						 }
				 
					 break;
					 case MAINMODE3_SUBMODE3:
						 //子模式为MAINMODE3_SUBMODE3状态
						 if(Key.Value == WKUP_S)
						 {
							 //按UP键,进入主界面1
							 Sys.Mode.Main_Mode=MAIN_MODE1;
							 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE1;
						 }
						 if(Key.Value == KEY0_S)
						 {
							 //按0键,进入主界面3的子界面2
							 Sys.Mode.Sub_MAIN_MODE3=MAINMODE3_SUBMODE2;
						 }
						 if(Key.Value == KEY1_S)
						 {
							 //按1键,进入主界面3的子界面1
							 Sys.Mode.Sub_MAIN_MODE3=MAINMODE3_SUBMODE1;
						 }
					 break; 
					 default:
							 
						 /*******************************************************************************************/
					 break; 
					 	}
										  
				 }
				
				 break;
			 }
			   
	
	
			 
	
			default:
				
			/*******************************************************************************************/
		break; 
			 
			}
	
	Key.Status=FREE;
	Key.Flag = FALSE;
    Key.Value=KEY_IDLE;
    //复位按键初始状态
	

}





