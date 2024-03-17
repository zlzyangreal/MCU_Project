#include "stm32f4xx.h"
#include "usart.h"
#include "delay.h"
#include "bluetooth.h"
#include "adc.h"
#include "tim.h"
#include "mdeal.h"
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
int t=0;
int f=0;
int flag=0;
extern uint16_t FFT_OUTPUT_Buffer[];
extern float fft_outputbuf[];
extern uint16_t OUTPUT_Buffer[];

uint32_t ADC_ConvertedValue;

float32_t FIR_Buffer[NUM_SIZE]={0};
float32_t FIR_OUT_Buffer[NUM_SIZE]={0};


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


int main(void)
{
	delay_init(168);
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart1_init();
	uart2_init();  
	tim2_init();
  adc_init();
  
  while(1)
	{
//		 bluetooth_printf();
		 
//		 for(i=0;i<num_size;i++)
//		 {
//			  printf("add 1,0,%d\xff\xff\xff",(int)IIR_Buffer[f+1][i]/(16*2)+75);
//			  delay_ms(5);
//		 }
	}
}

void DMA2_Stream0_IRQHandler(void)  
{
	
    if(DMA_GetITStatus(DMA2_Stream0, DMA_IT_TCIF0))  //判断DMA传输完成中断  
    {
	    DMA_Cmd(DMA2_Stream0,DISABLE);
      while(DMA_GetCmdStatus(DMA2_Stream0) != DISABLE){}	
#if 0	
      NUM_DEAL();				
			for(i=0;i<num_size;i++)
		  {
			  printf("add 1,0,%d\xff\xff\xff",(int)(OUTPUT_Buffer[i]/(16*2)));
			  delay_ms(5);
		  }
#endif
#if 0				
			for(i=0;i<num_size;i++)
		  {
			  printf("add 1,0,%d\xff\xff\xff",(int)(ADC_Buffer[i]/(16*2)+75));
			  delay_ms(5);
		  }
#endif		
#if 0				
      FFT_DEAL();
			for(i=1;i<num_size/16-1;i++)
		  {
				if((fft_outputbuf[i])>100)
				{
				  printf("  Fre%d	Hz",i*200);
								  delay_ms(1000);
				}
//			printf("add 4,0,%d\xff\xff\xff",(int)(fft_outputbuf[i]/64));
			  delay_ms(5);
		  }
#endif
#if 0	
          fir_init();
          for(i=0;i<num_size;i++)
		      {
            FIR_Buffer[i] = (float)ADC_Buffer[i];
						FIR_OUT_Buffer[i] = fir_deal(FIR_Buffer[i]);
            printf("add 1,0,%d\xff\xff\xff",(int)FIR_OUT_Buffer[i]/16);
						delay_ms(5);
		      }
					
#endif	
			DMA_Cmd(DMA2_Stream0,ENABLE);
			ADC1->SR&=~(1<<5);//清零OVR溢出位
	    DMA_ClearITPendingBit(DMA2_Stream0, DMA_IT_TCIF0);
		  
		}

}


