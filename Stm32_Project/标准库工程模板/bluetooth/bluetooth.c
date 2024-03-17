#include "bluetooth.h"

unsigned char *valuepack_tx_buffer; 
unsigned short valuepack_tx_index; 
unsigned char valuepack_tx_bit_index; 
unsigned char valuepack_stage; 
//---------------------------------------------------------
//
//题目：
//作者;zlzyang
//蓝牙部分
//
//---------------------------------------------------------
 
//---------------打包蓝牙传输的数据包---------------------//
void startValuePack(unsigned char *buffer) 
{ 
 valuepack_tx_buffer = buffer; 
 valuepack_tx_index = 1; 
 valuepack_tx_bit_index = 0; 
 valuepack_tx_buffer[0] = PACK_HEAD; 
 valuepack_stage = 0; 
} 
//---------------各类数据包打包函数-----------------------//
//有问题
void putBool(unsigned char b) 
 { 
 if(valuepack_stage<=1) 
 { 
 if(b) 
 valuepack_tx_buffer[valuepack_tx_index] |= 0x01<<valuepack_tx_bit_index; 
 //或运算，将1左移valuepack_tx_bit_index位
 else 
 valuepack_tx_buffer[valuepack_tx_index] &= ~(0x01<<valuepack_tx_bit_index); 
 //（~ 表示按位取反）
   valuepack_tx_bit_index++; 
 if(valuepack_tx_bit_index>=8) 
 { 
 valuepack_tx_bit_index = 0; 
 valuepack_tx_index++; 
 } 
 valuepack_stage = 1; 
 } 
 } 
void putByte(char b) 
 { 
 if(valuepack_stage<=2) 
 { 
 if(valuepack_tx_bit_index!=0) 
 {  
 valuepack_tx_index++; 
 valuepack_tx_bit_index = 0; 
 } 
 valuepack_tx_buffer[valuepack_tx_index] = b; 
 valuepack_tx_index++; 
   valuepack_stage = 2; 
 } 
 } 
 void putShort(short s) 
 { 
 if(valuepack_stage<=3) 
 { 
 if(valuepack_tx_bit_index!=0) 
 {  
 valuepack_tx_index++; 
 valuepack_tx_bit_index = 0; 
 } 
 valuepack_tx_buffer[valuepack_tx_index] = s&0xff; 
 valuepack_tx_buffer[valuepack_tx_index+1] = s>>8; 
   valuepack_tx_index +=2; 
 valuepack_stage = 3; 
 } 
 } 
 void putInt(int i) 
 { 
 if(valuepack_stage<=4) 
 { 
 if(valuepack_tx_bit_index!=0) 
 {  
 valuepack_tx_index++; 
 valuepack_tx_bit_index = 0; 
 } 
   valuepack_tx_buffer[valuepack_tx_index] = i&0xff; 
 valuepack_tx_buffer[valuepack_tx_index+1] = (i>>8)&0xff; 
 valuepack_tx_buffer[valuepack_tx_index+2] = (i>>16)&0xff; 
 valuepack_tx_buffer[valuepack_tx_index+3] = (i>>24)&0xff; 
   valuepack_tx_index +=4; 
   valuepack_stage = 4; 
 } 
 } 
 int fi; 
 void putFloat(float f) 
 { 
 if(valuepack_stage<=5) 
 { 
 if(valuepack_tx_bit_index!=0) 
 {  
 valuepack_tx_index++; 
 valuepack_tx_bit_index = 0; 
 } 
   fi = *(int*)(&f); 
 valuepack_tx_buffer[valuepack_tx_index] = fi&0xff; 
 valuepack_tx_buffer[valuepack_tx_index+1] = (fi>>8)&0xff; 
 valuepack_tx_buffer[valuepack_tx_index+2] = (fi>>16)&0xff; 
 valuepack_tx_buffer[valuepack_tx_index+3] = (fi>>24)&0xff; 
 valuepack_tx_index +=4; 
 valuepack_stage = 5; 
 } 
 }
//---------------结束打包并且返回数据包长度-------------// 
unsigned int endValuePack() 
{ 
 unsigned char sum=0;
 int i=1;	
 for(i=1;i<valuepack_tx_index;i++) 
 { 
 sum+=valuepack_tx_buffer[i]; 
 } 
 valuepack_tx_buffer[valuepack_tx_index] = sum; 
 valuepack_tx_buffer[valuepack_tx_index+1] = PACK_TAIL; 
 return valuepack_tx_index+2; 
} 
//------------------------发送数据----------------------// 
void sendBuffer(unsigned char *p,unsigned int length) 
{ 
 int i;
 for(i=0;i<length;i++) 
 {  
 USART_SendData(USART2, *p++);  
 while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET)  
 {}  
 } 
} 

 


