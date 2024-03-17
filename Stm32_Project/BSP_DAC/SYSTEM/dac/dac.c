#include "dac.h"

#define sin_V (3.3/2)
const uint16_t Sine12bit[DAC_SIZE] = {
 2048 , 2460 , 2856 , 3218 , 3532 , 3786 , 3969 , 4072 ,
 4093 , 4031 , 3887 , 3668 , 3382 , 3042 , 2661 , 2255 ,
 1841 , 1435 , 1054 , 714 , 428 , 209 , 65 , 3 ,
24 , 127 , 310 , 564 , 878 , 1240 , 1636 , 2048

 };
const uint16_t bsp_sin128[DAC_SIZE] = {
	2047 ,  2147 ,	2248 ,	2347 ,	2446 ,	2544 ,	2641 ,	2737 ,
	2830 ,  2922 ,	3012 ,	3099 ,	3184 ,	3266 ,	3346 ,	3422 ,
	3494 ,  3564 ,	3629 ,	3691 ,	3749 ,	3803 ,	3852 ,	3897 ,
	3938 ,	3974 ,	4006 ,	4033 ,	4055 ,	4072 ,	4084 ,	4092 ,
	4094 ,	4092 ,	4084 ,	4072 ,	4055 ,	4033 ,	4006 ,	3974 ,
	3938 ,	3897 ,	3852 ,	3803 ,	3749 ,	3691 ,	3629 ,	3564 ,
	3494 ,	3422 ,	3346 ,	3266 ,	3184 ,	3099 ,	3012 ,	2922 ,
	2830 ,	2737 ,	2641 ,	2544 ,	2446 ,	2347 ,	2248 ,	2147 ,
	2047 ,	1947 ,	1846 ,	1747 ,	1648 ,	1550 ,	1453 ,	1357 ,
	1264 ,	1172 ,	1082 ,	995  ,	910  ,	828  ,	748  ,	672  ,
	600  ,	530  ,	465  ,	403  ,	345  ,	291  ,	242  ,	197  ,
	156  ,	120  ,	88   ,	61   ,	39   ,	22   ,	10   ,	2    ,
	0    ,	2    ,	10   ,	22   ,	39   ,	61   ,	88   ,	120  ,
	156  ,	197  ,	242  ,	291  ,	345  ,	403  ,  465  ,	530  ,
	600  ,	672  ,	748  ,	828  ,	910  ,	995  ,	1082 ,	1172 ,
	1264 ,	1357 ,	1453 ,	1550 ,	1648 ,	1747 ,	1846 ,	1947
};

uint32_t DAC_Buffer[DAC_SIZE] ;
//---------------------------------------------------------
//
//题目：
//作者;zlzyang
//DAC部分
//
//---------------------------------------------------------
void dac_init(void)
{
	DMA_InitTypeDef DMA_InitStructure;
  GPIO_InitTypeDef  GPIO_InitStructure;
	DAC_InitTypeDef DAC_InitType;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);//使能GPIOA时钟
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);//使能DAC时钟
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;//模拟输入
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
//	GPIO_InitStructure.GPIO_Speed =  GPIO_Speed_100MHz;
//	GPIO_InitStructure.GPIO_OType =  GPIO_OType_PP;
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
	
//	DAC_InitType.DAC_Trigger = DAC_Trigger_T4_TRGO;
	DAC_InitType.DAC_Trigger = DAC_Trigger_T8_TRGO;
	DAC_InitType.DAC_WaveGeneration = DAC_WaveGeneration_None;
	DAC_InitType.DAC_OutputBuffer = DAC_OutputBuffer_Disable;
	DAC_InitType.DAC_LFSRUnmask_TriangleAmplitude = DAC_LFSRUnmask_Bit0;
	
  DAC_Init(DAC_Channel_1, &DAC_InitType);
	

//	DAC_SetChannel1Data(DAC_Align_12b_R,0X0000);
//  DAC_SoftwareTriggerCmd(DAC_Channel_1,ENABLE);
	
	DAC_Mode_Init();
	
	
	DMA_DeInit(DMA1_Stream5);
	DMA_Cmd(DMA1_Stream5, DISABLE);
	DMA_InitStructure.DMA_Channel = DMA_Channel_7;
	DMA_InitStructure.DMA_PeripheralBaseAddr =  (u32)&(DAC->DHR12R1);
	DMA_InitStructure.DMA_Memory0BaseAddr = (uint32_t)&DAC_Buffer;
	DMA_InitStructure.DMA_DIR = DMA_DIR_MemoryToPeripheral;
	DMA_InitStructure.DMA_BufferSize =  (uint32_t)(DAC_SIZE);
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	
	DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
  DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_1QuarterFull;		
  DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
	DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;		
	DMA_Init(DMA1_Stream5, &DMA_InitStructure);
	
//	TIM_Cmd(TIM4, ENABLE);
	TIM_Cmd(TIM8, ENABLE);
	DAC_Cmd(DAC_Channel_1, ENABLE);
	DAC_DMACmd(DAC_Channel_1, ENABLE);
	DMA_Cmd(DMA1_Stream5, ENABLE);
	
}

void DAC_Mode_Init(void)
{
//野火官方sin	
//  uint32_t Idx = 0;
//	for (Idx = 0; Idx < 210; Idx++)
//	{
//	  DAC_Buffer[Idx] = (Sine12bit[Idx] << 16) + (Sine12bit[Idx]);
//	}
#if	1
//自制sin
  uint16_t i;
  uint16_t dac;
  TIM_Cmd(TIM4,ENABLE);
  for(i=0;i<128;i++)
  {
	  dac = (bsp_sin128[i]*4095)/(4095*sin_V);
		if(dac>4095)
		{
		  dac = 4095;
		}
		DAC_Buffer[i] = (dac<< 16)+dac;
	}	
#endif	

}
