#ifndef __MDEAL_H
#define __MDEAL_H


#include "sys.h" 
#include "delay.h"
#include "adc.h"
#include "usart.h"
#include "arm_math.h"
#include "arm_const_structs.h"

void smooth5(uint16_t *x,int m);
void NUM_DEAL(void);
void FFT_DEAL(void);
float arm_iir_f32_bp(float input);

void fir_init(void);
float fir_deal(float input);

#endif 
