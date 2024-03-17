#ifndef __BLUETOOTH_H
#define __BLUETOOTH_H

#include <sys.h>

void initValuePack(int baudrate); 
void startValuePack(unsigned char *buffer); 
void putBool(unsigned char b); 
void putByte(char b); 
void putShort(short s); 
void putInt(int i); 
void putFloat(float f); 
unsigned int endValuePack(void); 
void sendBuffer(unsigned char *buffer,unsigned int length); 
#define PACK_HEAD 0xa5  
#define PACK_TAIL 0x5a 

#endif
