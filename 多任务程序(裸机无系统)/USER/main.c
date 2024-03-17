#include "sys.h" 	
#include "delay.h"	
#include "led.h"
#include "includes.h"

 

/************************************************
 ALIENTEK精英STM32开发板实验45
 UCOSII实验1-任务调度 实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
************************************************/

Sys_Struct Sys;

/////////////////////////UCOSII任务设置///////////////////////////////////
//START 任务
//设置任务优先级
#define START_TASK_PRIO      			10 //开始任务的优先级设置为最低
//设置任务堆栈大小
#define START_STK_SIZE  				64
//任务堆栈	
OS_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *pdata);	
 			   
//LED0任务
//设置任务优先级
#define LED0_TASK_PRIO       			7 
//设置任务堆栈大小
#define LED0_STK_SIZE  		    		64
//任务堆栈	
OS_STK LED0_TASK_STK[LED0_STK_SIZE];
//任务函数
void led0_task(void *pdata);


//LED1任务
//设置任务优先级
#define LED1_TASK_PRIO       			6 
//设置任务堆栈大小
#define LED1_STK_SIZE  					64
//任务堆栈
OS_STK LED1_TASK_STK[LED1_STK_SIZE];
//任务函数
void led1_task(void *pdata);


//KeyDeal任务
//设置任务优先级
#define KEYDEAL_TASK_PRIO       			4
//设置任务堆栈大小
#define KEYDEAL_STK_SIZE  					512
//任务堆栈
OS_STK KEYDEAL_TASK_STK[KEYDEAL_STK_SIZE];
//任务函数
void keydeal_task(void *pdata);


//Disp_Proc任务
//设置任务优先级
#define DISP_TASK_PRIO       			5
//设置任务堆栈大小
#define DISP_STK_SIZE  					512
//任务堆栈
OS_STK DISP_TASK_STK[DISP_STK_SIZE];
//任务函数
void disp_task(void *pdata);

 int main(void)
 {	//一系列初始化和实验一一样
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	delay_init();	    //延时函数初始化	  
	LED_Init();		  	//初始化与LED连接的硬件接口
	LCD_Init();
	KEY_Init();
	 
	//模式初始设置
 Sys.Mode.Main_Mode=MAIN_MODE1;
 Sys.Mode.Sub_MAIN_MODE1=MAINMODE1_SUBMODE1;
 Sys.Mode.Sub_MAIN_MODE2=MAINMODE2_SUBMODE1;
 Sys.Mode.Sub_MAIN_MODE3=MAINMODE3_SUBMODE1;
	 
	//这个OS是操作系统(只不过是个简单的) 
	OSInit();//系统初始化
	//创建起始任务为start_task,开始任务的优先级设置为最低START_TASK_PRIO，中间两项是指向可选数据区的指针和指向START任务堆栈START_TASK_STK   
 	OSTaskCreate(start_task,(void *)0,(OS_STK *)&START_TASK_STK[START_STK_SIZE-1],START_TASK_PRIO );
	OSStart();//相当于是开启多进程	  	 
}
	  
//开始任务
void start_task(void *pdata)
{
    OS_CPU_SR cpu_sr=0;
	pdata = pdata; 
  	OS_ENTER_CRITICAL();			//进入临界区(无法被中断打断)
	//创建LED0任务，优先级为7级(较低)    
 	OSTaskCreate(led0_task,(void *)0,(OS_STK*)&LED0_TASK_STK[LED0_STK_SIZE-1],LED0_TASK_PRIO);
	//创建LED1任务，优先级为6级(高于LED0)						   
 	OSTaskCreate(led1_task,(void *)0,(OS_STK*)&LED1_TASK_STK[LED1_STK_SIZE-1],LED1_TASK_PRIO);
	//创建LED2任务，优先级为4
	OSTaskCreate(keydeal_task,(void *)0,(OS_STK*)&KEYDEAL_TASK_STK[KEYDEAL_STK_SIZE-1],KEYDEAL_TASK_PRIO);
	//创建DISP任务，优先级为5
	OSTaskCreate(disp_task,(void *)0,(OS_STK*)&DISP_TASK_STK[DISP_STK_SIZE-1],DISP_TASK_PRIO);	
	OSTaskSuspend(START_TASK_PRIO);	//挂起起始任务.(目的是处理相同优先级任务)
	OS_EXIT_CRITICAL();				//退出临界区(可以被中断打断)
}

//LED0任务
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

//LED1任务
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

//KEYDEAL任务
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

//DISP任务
void disp_task(void *pdata)
{	  
	while(1)
	{		  
		Disp_Proc();//显示模块
		OSTimeDly(10);//10ms刷新一次
	};
}





