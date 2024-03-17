#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "bluetooth.h"
#include "adc.h"
#include "tim.h"
#include "mdeal.h"
#include "fftdeal.h"
#include "arm_math.h"
#include "arm_const_structs.h"
//---------------------------------------------------------
//
//题目：
//作者;zlzyang
//主函数部分
//
//---------------------------------------------------------
unsigned char buff[27];
unsigned char bluetooth_buff[4096];
extern uint16_t ADC_Buffer[];
extern uint16_t num_size;
int i;
uint32_t DMA_FLAG=0;
extern uint16_t OUTPUT_Buffer[];
extern float32_t FFT_Output[DEAL_SIZE/2];
uint32_t ADC_ConvertedValue;
void bluetooth_printf(void)
{
	delay_ms(500);
	startValuePack(bluetooth_buff);
//---------------各类数据包打包-------------------------//
 putBool(0); 
// putBool(1); 
// putBool(0); 
// putBool(0);
// putByte(16);	
// putShort(3123); 
// putInt(3124);
//  putFloat(4096); 
 sendBuffer(bluetooth_buff,endValuePack());
}

void show(void)
{
  #if 0	
      NUM_DEAL();				
			for(i=0;i<num_size;i++)
		  {
			  printf("add 1,0,%d\xff\xff\xff",(int)(OUTPUT_Buffer[i]/(16*2)+75));
			  delay_ms(10);
		  }
#endif
#if 1					
			for(i=0;i<num_size;i++)
		  {
			  printf("add 1,0,%d\xff\xff\xff",(int)(ADC_Buffer[i]/(16*2)+75));
			  delay_ms(10);
		  }
#endif
#if 0			
      FFT_DEAL();	
			for(i=0;i<num_size/2;i++)
		  {
				printf("FFT: %f, %d\n",FFT_Output[i],i);
//				printf("v: %d, %d\n",ADC_Buffer[i],i);
//			  printf("add 1,0,%d\xff\xff\xff",(int)(FFT_Output[i]/(16*2)+75));
		  }
#endif	
			DMA_Cmd(DMA2_Stream0,ENABLE);
			ADC1->SR&=~(1<<5);//清零OVR溢出位
}
int main(void)
{
	delay_init(168);
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart1_init();
	uart2_init();  
	tim2_init();
  adc_init();

  while(1){
//		 bluetooth_printf();
		if(DMA_FLAG)
		{
		  show();
			DMA_FLAG=0;
		}
	}
}

void DMA2_Stream0_IRQHandler(void)  
{
	
    if(DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0))  //判断DMA传输完成中断  
    {
	    DMA_Cmd(DMA2_Stream0,DISABLE);
      while(DMA_GetCmdStatus(DMA2_Stream0) != DISABLE){}	

				DMA_FLAG=1;
	    DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);
		  
		}

}


