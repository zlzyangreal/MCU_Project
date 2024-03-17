#include "adc.h"
#include "delay.h"
#include "usart.h"

uint16_t num_size = NUM_SIZE;
uint16_t ADC_Buffer[NUM_SIZE]= {0};
unsigned char buff1[27];
//---------------------------------------------------------
//
//��Ŀ��
//����;zlzyang
//ADC����
//
//---------------------------------------------------------
void adc_init(void)
{
	DMA_InitTypeDef DMA_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	ADC_CommonInitTypeDef ADC_CommonInitStructure;
  GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1 , ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init( GPIOB, &GPIO_InitStructure);
	
//	DMA_DeInit(DMA2_Stream0);
	DMA_Cmd(DMA2_Stream0, DISABLE);
	DMA_DeInit(DMA2_Stream0);
	DMA_InitStructure.DMA_Channel = DMA_Channel_0;
  DMA_InitStructure.DMA_PeripheralBaseAddr=(uint32_t)&ADC1->DR;		
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)ADC_Buffer;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
  DMA_InitStructure.DMA_BufferSize = (uint32_t)(NUM_SIZE);//		
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize=DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;//		
	DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
  
  DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;		
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;		
	DMA_Init(DMA2_Stream0, &DMA_InitStructure);


  DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TC); //����жϱ�־   
  DMA_ITConfig(DMA2_Stream0, DMA_IT_TC, ENABLE); //��������ж�  

	ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
	ADC_CommonInitStructure.ADC_DMAAccessMode=ADC_DMAAccessMode_Disabled;
	ADC_CommonInitStructure.ADC_TwoSamplingDelay=ADC_TwoSamplingDelay_20Cycles;
	ADC_CommonInit(&ADC_CommonInitStructure);
	
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//
	ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_Rising;//
  ADC_InitStructure.ADC_ExternalTrigConv=ADC_ExternalTrigConv_T2_CC2;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfConversion = 1;
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_3Cycles);//���ڴ�С���Խ���Ƶ�ʲɼ���Χ
  ADC_Cmd(ADC1, ENABLE);

  
//	ADC_SoftwareStartConv(ADC1);//	
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitStructure.NVIC_IRQChannel = DMA2_Stream0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	

	
//	DMA_ITConfig(DMA2_Stream0,DMA_IT_TC|DMA_IT_TE,ENABLE);
//	DMA_ClearFlag(DMA2_Stream0,DMA_FLAG_TCIF0);	
	ADC_DMARequestAfterLastTransferCmd(ADC1,ENABLE);
	ADC_DMACmd(ADC1,ENABLE);

	DMA_Cmd(DMA2_Stream0, ENABLE);

  while (DMA_GetCmdStatus(DMA2_Stream0) != ENABLE) {
  }
	
}



