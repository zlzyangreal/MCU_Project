#ifndef __FFTDEAL_H
#define __FFTDEAL_H


#include "sys.h" 
#include "delay.h"
#include "adc.h"
#include "arm_math.h"
#include "arm_const_structs.h"

/* ------------------------------------------------------------------
* 
***FFT全局变量
*
* ------------------------------------------------------------------- */
#define FFT_SIZE NUM_SIZE
#define DEAL_SIZE (FFT_SIZE*2)

void FFT_DEAL(void);

#endif 
