#include "mdeal.h"

uint16_t DEAL_Buffer[NUM_SIZE]={0};
uint16_t OUTPUT_Buffer[NUM_SIZE]={0};
extern uint16_t ADC_Buffer[];

//5点平滑处理，7点精度更高
void smooth5(uint16_t *x,int m)
{
	uint16_t  a[NUM_SIZE]={0};
	int get_i,deal_i,deal_j,deal_k,end_i;
	for(get_i=0;get_i<NUM_SIZE;get_i++)
	{
	  a[get_i] = x[get_i];
	}
	for(deal_i=0;deal_i<m;deal_i++)
	{
	  uint16_t  b[NUM_SIZE]={0};
// 计算第一个元素的平滑值
    b[0] = (69 * a[0] + 4 * (a[1] + a[3]) - 6 * a[2] - a[4]) / 70;
// 计算第二个元素的平滑值
    b[1] = (2 * (a[0] + a[4]) + 27 * a[1] + 12 * a[2] - 8 * a[3]) / 35;
// 对中间的元素进行平滑计算
//    for (deal_j = 2; deal_j < NUM_SIZE - 2; deal_j++)
//		{
//        b[deal_j] = (-3 * (a[deal_j-2] + a[deal_j+2]) + 12 * (a[deal_j-1] + a[deal_j+1]) + 17 * a[deal_j]) / 35;
//    }
//考虑0	,但出现断崖	
		 for (deal_j = 2; deal_j < NUM_SIZE - 2; deal_j++) {
            if (a[deal_j-2] != 0 && a[deal_j-1] != 0 && a[deal_j] != 0 && a[deal_j+1] != 0 && a[deal_j+2] != 0) {
                b[deal_j] = (-3 * (a[deal_j-2] + a[deal_j+2]) + 12 * (a[deal_j-1] + a[deal_j+1]) + 17 * a[deal_j]) / 35;
            } else {
                b[deal_j] = a[deal_j];
            }
        }

// 计算倒数第二个元素的平滑值
    b[NUM_SIZE - 2] = (2 * (a[NUM_SIZE-1] + a[NUM_SIZE-5]) + 27 * a[NUM_SIZE-2] + 12 * a[NUM_SIZE-3] - 8 * a[NUM_SIZE-4]) / 35;
// 计算最后一个元素的平滑值
    b[NUM_SIZE - 1] = (69 * a[NUM_SIZE-1] + 4 * (a[NUM_SIZE-2] + a[NUM_SIZE-4]) - 6 * a[NUM_SIZE-3] - a[NUM_SIZE-5]) / 70;
// 将计算得到的平滑值赋值给变量a
    for (deal_k = 0; deal_k < NUM_SIZE; deal_k++) 
		{
        a[deal_k] = b[deal_k];
    }
	}
	for(end_i=0;end_i<NUM_SIZE;end_i++)
	{
	  DEAL_Buffer[end_i] = a[end_i];
	}
}
//二次函数拟合,采用7点拟合
void qua_smooth(uint16_t *x,int m)
{
  int i,end_i;
	uint16_t  z[NUM_SIZE]={0};
	if(m<7)
	{
	  for(i=0;i<=m-1;i++)
		{
		  OUTPUT_Buffer[i]=x[i];
		}
	}else
	{
	  z[0] = ( 32.0 * x[0] + 15.0 * x[1] + 3.0 * x[2] - 4.0 * x[3] - 6.0 * x[4] - 3.0 * x[5] + 5.0 * x[6] ) / 42.0;
    z[1] = ( 5.0 * x[0] + 4.0 * x[1] + 3.0 * x[2] + 2.0 * x[3] + x[4] - x[6] ) / 14.0;
    z[2] = ( 1.0 * x[0] + 3.0 * x [1] + 4.0 * x[2] + 4.0 * x[3] + 3.0 * x[4] + 1.0 * x[5] - 2.0 * x[6] ) / 14.0;
    for ( i = 3; i <= NUM_SIZE - 4; i++ )
        {
            z[i] = ( -2.0 * (x[i - 3] + x[i + 3]) + 3.0 * (x[i - 2] + x[i + 2]) +  6.0 * (x[i - 1] + x[i + 1]) + 7.0 * x[i] ) / 21.0;
        }
    z[NUM_SIZE - 3] = ( 1.0 * x[NUM_SIZE - 1] + 3.0 * x [NUM_SIZE - 2] + 4.0 * x[NUM_SIZE - 3] + 4.0 * x[NUM_SIZE - 4] + 3.0 * x[NUM_SIZE - 5] + 1.0 * x[NUM_SIZE - 6] - 2.0 * x[NUM_SIZE - 7] ) / 14.0;
    z[NUM_SIZE - 2] = ( 5.0 * x[NUM_SIZE - 1] + 4.0 * x[NUM_SIZE - 2] + 3.0 * x[NUM_SIZE - 3] + 2.0 * x[NUM_SIZE - 4] + x[NUM_SIZE - 5] - x[NUM_SIZE - 7] ) / 14.0;
    z[NUM_SIZE - 1] = ( 32.0 * x[NUM_SIZE - 1] + 15.0 * x[NUM_SIZE - 2] + 3.0 * x[NUM_SIZE - 3] - 4.0 * x[NUM_SIZE - 4] - 6.0 * x[NUM_SIZE - 5] - 3.0 * x[NUM_SIZE - 6] + 5.0 * x[NUM_SIZE - 7] ) / 42.0;
    }
		for(end_i=0;end_i<NUM_SIZE;end_i++)
	{
	  OUTPUT_Buffer[end_i] = z[end_i];
	}
}
void NUM_DEAL(void)
{
   smooth5(ADC_Buffer,50);
	 qua_smooth(DEAL_Buffer,50);
}

