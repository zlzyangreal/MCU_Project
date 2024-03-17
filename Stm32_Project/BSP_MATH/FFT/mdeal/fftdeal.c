#include "fftdeal.h"

#define M_PI 3.1415826 

uint32_t fft_size = FFT_SIZE;
uint32_t ifftFlag = 0;
uint32_t doBitReverse = 1;

float32_t FFT_Input[DEAL_SIZE];
float32_t FFT_Output[DEAL_SIZE/2];
extern uint16_t ADC_Buffer[];
float32_t window[DEAL_SIZE/2];
float32_t signal[DEAL_SIZE/2];
float32_t input_signal[DEAL_SIZE/2];
float32_t real[DEAL_SIZE/2];
float32_t imag[DEAL_SIZE/2];
float32_t ATAN[DEAL_SIZE/2];

void removeDC(void)
{
  float32_t mean = 0.0;
	int i;
	for(i=0;i<fft_size;i++)
	{
	  mean += (float)(ADC_Buffer[i]*3.3/4096);
	}
	mean /=fft_size;
	for(i=0;i<fft_size;i++)
	{
	  input_signal[i] = (float)(ADC_Buffer[i]*3.3/4096) - mean;
	}
}
//防泄露效果更好，但是主频削减更严重
void Blackman_window(void)
{
  int i;
	const float a0 = 0.42;
  const float a1 = 0.5;
  const float a2 = 0.08;
 
  float len_mult = 1/(float)(fft_size-1);
  for (i = 0; i < fft_size; i++)
 	{
    window[i] = a0 - a1 * cosf(i * 2 * PI * len_mult) + a2 * cosf(i * 4 * PI * len_mult);
	}
	for (i = 0; i < fft_size; i++) {
        signal[i] = window[i]*(float)(input_signal[i]);
	}
    
	
}
//计算要求太高
//void falt_top_window(void)
//{
//	 int i;
//   const float a0=0.21557895; 
//   const float a1=0.41663158; 
//   const float a2=0.277263158; 
//   const float a3=0.083578947; 
//   const float a4=0.006947368;    
// 
//   float len_mult = 1/(float)(fft_size-1);
//   for (i = 0; i < fft_size; i++) {
//        window[i] = a0 
//                    - a1 * cosf(i * 2 * M_PI * len_mult) 
//                    + a2 * cosf(i * 4 * M_PI * len_mult)
//                    - a3 * cosf(i * 6 * M_PI * len_mult)
//                    + a4 * cosf(i * 8 * M_PI * len_mult);
//	for (i = 0; i < fft_size; i++) {
//        signal[i] = window[i]*(float)(input_signal[i]);
//	}	
//			
//}
//}
//防泄露效果较差，但是主频削减较弱
void hanning_widow(void)
{
	int i;
  float len_mult = 1/(float)(fft_size-1);
	for (i = 0; i < fft_size; i++) 
	{
      window[i] = 0.5 * (1 - cosf(i * 2 * PI * len_mult));
  }
	for (i = 0; i < fft_size; i++) 
	{
      signal[i] = window[i]*(float)(input_signal[i]);
	}

}
void get_angle(void)
{
	uint16_t i;
  for(i=0;i<DEAL_SIZE;i++)
	{
		int t=0;
		if(t)
		{
		  imag[(i+1)/2] = FFT_Input[i];
			t = 0;
		}else
		{
		  real[i/2] = FFT_Input[i];
			t = 1;
		}
	}
	for(i=0;i<FFT_SIZE;i++)
	{
	  ATAN[i] = atan2(imag[i],real[i]);
	}
}
void FFT_DEAL(void)
{
  uint16_t i=0;
	removeDC();
//	Blackman_window();
	hanning_widow();
/* ------------------------------------------------------------------
* 
***FFT数据存入
***实部存入，虚部为0
*
* ------------------------------------------------------------------- */	
	for(i=0;i<FFT_SIZE;i++)
	{
	  FFT_Input[2*i] = (float)(signal[i]);
//		FFT_Input[2*i] = (float)(input_signal[i]);
//		FFT_Input[2*i] = (float)(ADC_Buffer[i]*3.3/4096);
		FFT_Input[2*i+1] = 0;
	}
	arm_cfft_f32(&arm_cfft_sR_f32_len1024,FFT_Input,ifftFlag,doBitReverse);
	arm_cmplx_mag_f32(FFT_Input, FFT_Output, fft_size);	
//  get_angle();
}


