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
								    
//������ʼ������
void KEY_Init(void) //IO��ʼ��
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
 
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOE,ENABLE);//ʹ��PORTA,PORTEʱ��

	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4|GPIO_Pin_3;//KEY0-KEY1
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; //���ó���������
 	GPIO_Init(GPIOE, &GPIO_InitStructure);//��ʼ��GPIOE4,3

	//��ʼ�� WK_UP-->GPIOA.0	  ��������
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; //PA0���ó����룬Ĭ������	  
	GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��GPIOA.0
}

/******************************************************************************************
���ƣ�KeyRead
���ܣ�
ʹ�÷�����
KeyFlag

*******************************************************************************************/
 


unsigned char KeyRead(void)
{ //
   
    



	/*  ����GPIO��ģʽ��IO�� */
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
���ƣ�KeyScan
���ܣ�����ɨ��
ʹ�÷��������ö�ʱ������ж�ʱ��Ϊ10ms���ڶ�ʱ���ж��е��øú��������а������£��ú����޸�
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
	//�а����¼�δ�����ֱ꣬���˳�

	static unsigned char LongKeyFlag=0;
	
	if (Key.Flag == TRUE) return;
	
	Key.Value_Last = Key.Value_Cur;
	Key.Value_Cur = KeyRead();//��ȡ����ֵ����

	switch (Key.Status)
	{
		case FREE:
			if ((Key.Value_Cur != Key.Value_Last) && (Key.Value_Cur != 0))
			{//�½���
				Key.Status = DOWN;
				Key.Delay = 0;

				LongKeyFlag=FALSE;					
			}			
			break;
		case DOWN:
			if ((Key.Value_Cur == Key.Value_Last) && (Key.Value_Cur != 0))
			{//�а�������

 				Key.Delay++;								
				if(Key.Delay > KEY_DELAY3S && LongKeyFlag==FALSE)
				{
					//Call_Led(2,1000);
					LongKeyFlag=TRUE;
				}	
							
				if (Key.Delay > KEY_DELAY3S) 
				{//����ʱ�䳬������
					switch(Key.Value_Last)
					{
						case KEY1_PRES:
						    //UP������
							Key.Value = KEY1_3;
							Key.Flag=TRUE;
							break;
						case KEY0_PRES:
							//DOWN������
							Key.Value = KEY0_3;
							Key.Flag=TRUE;
							break;
						case WKUP_PRES:
							//DOWN������
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
				{//�����ɿ�
					if((Key.Delay < KEY_DELAY3S) && (Key.Delay > KEY_DELAY_SHORT))
					{
				   		switch(Key.Value_Last)
						{
							case KEY1_PRES:
								//�ϼ��̰�
								Key.Value = KEY1_S;
								Key.Flag=TRUE;
								break;
							case KEY0_PRES:
								//Set���̰�
								Key.Value = KEY0_S;
								Key.Flag=TRUE;
								break;							
							case WKUP_PRES:
								//ȷ�ϼ��̰�
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
���ƣ�KeyDeal
���ܣ���������
ʹ�÷�������������Main�е��øú��������а����¼���ִ����Ӧ������̣�����ֱ���˳�
����flash������
*******************************************************************************************/

void KeyDeal(void)
{

  //KeyScan();
	if(Key.Flag == FALSE) return;
	
	switch(Sys.Mode.Main_Mode)
			{
			//��ģʽΪMAIN_MODE1״̬
		   case MAIN_MODE1:
		   	 {
				 switch(Sys.Mode.Sub_MAIN_MODE1)
					 {
					 case MAINMODE1_SUBMODE1:
						 //��ģʽΪMAINMODE1_SUBMODE1״̬
						 if(Key.Value == WKUP_S)
						 {
							 //��UP��,����������2
							 Sys.Mode.Main_Mode=MAIN_MODE2;
							 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE1;
						 }
						 if(Key.Value == KEY0_S)
						 {
							 //��0��,����������1���ӽ���3
							 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE3;
						 }
						 if(Key.Value == KEY1_S)
						 {
							 //��1��,����������1���ӽ���2
							 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE2;
						 }
					 break;
					 case MAINMODE1_SUBMODE2:
							 //��ģʽΪMAINMODE1_SUBMODE2״̬
						 if(Key.Value == WKUP_S)
						 {
							 //��UP��,����������2
							 Sys.Mode.Main_Mode=MAIN_MODE2;
							 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE1;
						 }
						 if(Key.Value == KEY0_S)
						 {
							 //��0��,����������1���ӽ���1
							 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE1;
						 }
						 if(Key.Value == KEY1_S)
						 {
							 //��1��,����������1���ӽ���3
							 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE3;
						 }
				 
					 break;
					 case MAINMODE1_SUBMODE3:
						 //��ģʽΪMAINMODE1_SUBMODE3״̬
						 if(Key.Value == WKUP_S)
						 {
							 //��UP��,����������2
							 Sys.Mode.Main_Mode=MAIN_MODE2;
							 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE1;
						 }
						 if(Key.Value == KEY0_S)
						 {
							 //��0��,����������1���ӽ���2
							 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE2;
						 }
						 if(Key.Value == KEY1_S)
						 {
							 //��1��,����������1���ӽ���1
							 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE1;
						 }
					 break; 
					 default:
							 
						 /*******************************************************************************************/
					 break; 
					 
					 }
									  
		   	 }
			
			 break;
				//��ģʽΪMAIN_MODE2״̬
			 case MAIN_MODE2:
			   {
				  switch(Sys.Mode.Sub_MAIN_MODE2)
					 {
					 case MAINMODE2_SUBMODE1:
						 //��ģʽΪMAINMODE2_SUBMODE1״̬
						 if(Key.Value == WKUP_S)
						 {
							 //��UP��,����������3
							 Sys.Mode.Main_Mode=MAIN_MODE3;
							 Sys.Mode.Sub_MAIN_MODE3=MAINMODE3_SUBMODE1;
						 }
						 if(Key.Value == KEY0_S)
						 {
							 //��0��,����������2���ӽ���3
							 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE3;
						 }
						 if(Key.Value == KEY1_S)
						 {
							 //��1��,����������2���ӽ���2
							 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE2;
						 }
					 break;
					 case MAINMODE2_SUBMODE2:
							 //��ģʽΪMAINMODE1_SUBMODE2״̬
						 if(Key.Value == WKUP_S)
						 {
							 //��UP��,����������3
							 Sys.Mode.Main_Mode=MAIN_MODE3;
							 Sys.Mode.Sub_MAIN_MODE3=MAINMODE3_SUBMODE1;
						 }
						 if(Key.Value == KEY0_S)
						 {
							 //��0��,����������2���ӽ���1
							 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE1;
						 }
						 if(Key.Value == KEY1_S)
						 {
							 //��1��,����������2���ӽ���3
							 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE3;
						 }
					 break;
						 
					 case MAINMODE2_SUBMODE3:
						 //��ģʽΪMAINMODE2_SUBMODE3״̬
						 if(Key.Value == WKUP_S)
						 {
							 //��UP��,����������3
							 Sys.Mode.Main_Mode=MAIN_MODE3;
							 Sys.Mode.Sub_MAIN_MODE3=MAINMODE3_SUBMODE1;
						 }
						 if(Key.Value == KEY0_S)
						 {
							 //��0��,����������2���ӽ���2
							 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE2;
						 }
						 if(Key.Value == KEY1_S)
						 {
							 //��1��,����������2���ӽ���1
							 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE1;
						 }
					 break; 
						 
					 default:
					 break; 
					 
					 }	
			   }
			   break;
				 
			   //��ģʽΪMAIN_MODE3״̬
			   case MAIN_MODE3:
				 {
					 switch(Sys.Mode.Sub_MAIN_MODE3)
					 	{
						 {
					 case MAINMODE3_SUBMODE1:
						 //��ģʽΪMAINMODE3_SUBMODE1״̬
						 if(Key.Value == WKUP_S)
						 {
							 //��UP��,����������1
							 Sys.Mode.Main_Mode=MAIN_MODE1;
							 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE1;
						 }
						 if(Key.Value == KEY0_S)
						 {
							 //��0��,����������3���ӽ���3
							 Sys.Mode.Sub_MAIN_MODE3=MAINMODE3_SUBMODE3;
						 }
						 if(Key.Value == KEY1_S)
						 {
							 //��1��,����������3���ӽ���2
							 Sys.Mode.Sub_MAIN_MODE3=MAINMODE3_SUBMODE2;
						 }
					 break;
					 case MAINMODE3_SUBMODE2:
							 //��ģʽΪMAINMODE3_SUBMODE2״̬
						 if(Key.Value == WKUP_S)
						 {
							 //��UP��,����������1
							 Sys.Mode.Main_Mode=MAIN_MODE1;
							 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE1;
						 }
						 if(Key.Value == KEY0_S)
						 {
							 //��0��,����������3���ӽ���1
							 Sys.Mode.Sub_MAIN_MODE3=MAINMODE3_SUBMODE1;
						 }
						 if(Key.Value == KEY1_S)
						 {
							 //��1��,����������3���ӽ���3
							 Sys.Mode.Sub_MAIN_MODE3=MAINMODE3_SUBMODE3;
						 }
				 
					 break;
					 case MAINMODE3_SUBMODE3:
						 //��ģʽΪMAINMODE3_SUBMODE3״̬
						 if(Key.Value == WKUP_S)
						 {
							 //��UP��,����������1
							 Sys.Mode.Main_Mode=MAIN_MODE1;
							 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE1;
						 }
						 if(Key.Value == KEY0_S)
						 {
							 //��0��,����������3���ӽ���2
							 Sys.Mode.Sub_MAIN_MODE3=MAINMODE3_SUBMODE2;
						 }
						 if(Key.Value == KEY1_S)
						 {
							 //��1��,����������3���ӽ���1
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
    //��λ������ʼ״̬
	

}





