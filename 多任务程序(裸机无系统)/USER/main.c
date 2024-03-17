#include "sys.h" 	
#include "delay.h"	
#include "led.h"
#include "includes.h"

 

/************************************************
 ALIENTEK��ӢSTM32������ʵ��45
 UCOSIIʵ��1-������� ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/

Sys_Struct Sys;

/////////////////////////UCOSII��������///////////////////////////////////
//START ����
//�����������ȼ�
#define START_TASK_PRIO      			10 //��ʼ��������ȼ�����Ϊ���
//���������ջ��С
#define START_STK_SIZE  				64
//�����ջ	
OS_STK START_TASK_STK[START_STK_SIZE];
//������
void start_task(void *pdata);	
 			   
//LED0����
//�����������ȼ�
#define LED0_TASK_PRIO       			7 
//���������ջ��С
#define LED0_STK_SIZE  		    		64
//�����ջ	
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
//������
void led0_task(void *pdata);


//LED1����
//�����������ȼ�
#define LED1_TASK_PRIO       			6 
//���������ջ��С
#define LED1_STK_SIZE  					64
//�����ջ
OS_STK LED1_TASK_STK[LED1_STK_SIZE];
//������
void led1_task(void *pdata);


//KeyDeal����
//�����������ȼ�
#define KEYDEAL_TASK_PRIO       			4
//���������ջ��С
#define KEYDEAL_STK_SIZE  					512
//�����ջ
OS_STK KEYDEAL_TASK_STK[KEYDEAL_STK_SIZE];
//������
void keydeal_task(void *pdata);


//Disp_Proc����
//�����������ȼ�
#define DISP_TASK_PRIO       			5
//���������ջ��С
#define DISP_STK_SIZE  					512
//�����ջ
OS_STK DISP_TASK_STK[DISP_STK_SIZE];
//������
void disp_task(void *pdata);

 int main(void)
 {	//һϵ�г�ʼ����ʵ��һһ��
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	delay_init();	    //��ʱ������ʼ��	  
	LED_Init();		  	//��ʼ����LED���ӵ�Ӳ���ӿ�
	LCD_Init();
	KEY_Init();
	 
	//ģʽ��ʼ����
 Sys.Mode.Main_Mode=MAIN_MODE1;
 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE1;
 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE1;
 Sys.Mode.Sub_MAIN_MODE3=MAINMODE3_SUBMODE1;
	 
	//���OS�ǲ���ϵͳ(ֻ�����Ǹ��򵥵�) 
	OSInit();//ϵͳ��ʼ��
	//������ʼ����Ϊstart_task,��ʼ��������ȼ�����Ϊ���START_TASK_PRIO���м�������ָ���ѡ��������ָ���ָ��START�����ջSTART_TASK_STK   
 	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );
	OSStart();//�൱���ǿ��������	  	 
}
	  
//��ʼ����
void start_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
	pdata = pdata; 
  	OS_ENTER_CRITICAL();			//�����ٽ���(�޷����жϴ��)
	//����LED0�������ȼ�Ϊ7��(�ϵ�)    
 	OSTaskCreate(led0_task,(void *)0,(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],LED0_TASK_PRIO);
	//����LED1�������ȼ�Ϊ6��(����LED0)						   
 	OSTaskCreate(led1_task,(void *)0,(OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1],LED1_TASK_PRIO);
	//����LED2�������ȼ�Ϊ4
	OSTaskCreate(keydeal_task,(void *)0,(OS_STK*)&KEYDEAL_TASK_STK[KEYDEAL_STK_SIZE-1],KEYDEAL_TASK_PRIO);
	//����DISP�������ȼ�Ϊ5
	OSTaskCreate(disp_task,(void *)0,(OS_STK*)&DISP_TASK_STK[DISP_STK_SIZE-1],DISP_TASK_PRIO);	
	OSTaskSuspend(START_TASK_PRIO);	//������ʼ����.(Ŀ���Ǵ�����ͬ���ȼ�����)
	OS_EXIT_CRITICAL();				//�˳��ٽ���(���Ա��жϴ��)
}

//LED0����
void led0_task(void *pdata)
{	 	
	while(1)
	{
		LED0=1;
		OSTimeDly(300);
		LED0=0;
		OSTimeDly(300);
	};
}

//LED1����
void led1_task(void *pdata)
{	  
	while(1)
	{
		LED1=0;
		OSTimeDly(300);
		LED1=1;
		OSTimeDly(300);
	};
}

//KEYDEAL����
void keydeal_task(void *pdata)
{	  
	while(1)
	{
		KeyScan();
		
		if(Key.Flag==TRUE)  
		{
			KeyDeal();
		}
		
		OSTimeDly(1);
		
	};
}

//DISP����
void disp_task(void *pdata)
{	  
	while(1)
	{		  
		Disp_Proc();//��ʾģ��
		OSTimeDly(10);//10msˢ��һ��
	};
}





