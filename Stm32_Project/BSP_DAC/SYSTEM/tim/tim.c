#include "tim.h" 
//---------------------------------------------------------
//
//��Ŀ��
//����;zlzyang
//ʱ�Ӳ���
//
//---------------------------------------------------------

void tim2_init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  TIM_OCInitTypeDef TIM_OCInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	GPIO_PinAFConfig(GPIOB,GPIO_PinSource3,GPIO_AF_TIM2);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

	TIM_TimeBaseStructure.TIM_Period = 4;//(С��65535)
	TIM_TimeBaseStructure.TIM_Prescaler = 79;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	
	TIM_OCInitStructure.TIM_Pulse = 1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High; 

	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_ARRPreloadConfig(TIM2, ENABLE); //����TIM3��ʱ����
	TIM_Cmd(TIM2, ENABLE);
	
//	TIM_CtrlPWMOutputs(TIM2, ENABLE);
}
void tim4_init(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	
	
  TIM_TimeBaseStructure.TIM_Period = 1;
	TIM_TimeBaseStructure.TIM_Prescaler = 0;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
//	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
		
  TIM_SelectOutputTrigger(TIM4, TIM_TRGOSource_Update);
//  TIM_ARRPreloadConfig(TIM4, ENABLE); 
	
}
void tim8_init(void)
{
GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1,ENABLE);  	//TIM1ʱ��ʹ��    
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); 	//ʹ��PORTAʱ��	
	
	GPIO_PinAFConfig(GPIOA,GPIO_PinSource8,GPIO_AF_TIM1); //GPIOA8����Ϊ��ʱ��1
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;           //GPIOA8
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;        //���ù���
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	//�ٶ�100MHz
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;      //���츴�����
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;        //����
	GPIO_Init(GPIOA,&GPIO_InitStructure);              //��ʼ��PA8
	  
	TIM_TimeBaseStructure.TIM_Prescaler=0;  //��ʱ����Ƶ
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_Period=1;   //�Զ���װ��ֵ
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; 
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;  //20201020
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);//��ʼ����ʱ��1
	
	//��ʼ��TIM1 Channel1 PWMģʽ	
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputState_Disable;//20201020	
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low; //�������:TIM����Ƚϼ��Ե�
	TIM_OCInitStructure.TIM_OCNPolarity= TIM_OCPolarity_High;//20201020
  TIM_OCInitStructure.TIM_OCIdleState= 0x00000000U  ;//20201020    
	TIM_OCInitStructure.TIM_OCNIdleState=0x00000000U;//20201020
 
	TIM_OCInitStructure.TIM_Pulse=300;
//	TIM_SetCompare1(TIM1,CCR1_Val);// channel 1   20201020	
	TIM_OC1Init(TIM1, &TIM_OCInitStructure);  //����Tָ���Ĳ�����ʼ������TIM1 4OC1
 
	TIM_OC1PreloadConfig(TIM1, TIM_OCPreload_Enable);  //ʹ��TIM1��CCR1�ϵ�Ԥװ�ؼĴ���
 
  TIM_ARRPreloadConfig(TIM1,ENABLE);//ARPEʹ�� 
	
	TIM_Cmd(TIM1, ENABLE);  //ʹ��TIM1
	
	TIM_CtrlPWMOutputs(TIM1, ENABLE);    //20201020
}

