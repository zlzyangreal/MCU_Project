/*
* author:  Zlzyang
* date:    2023-12-11
*/
#include "DSP28_Device.h"

#define  CPLDport2000 (volatile unsigned int *) 0x2000

//define for keyscan
#define  LED1 (volatile unsigned int *) 0x3000 
#define  LED2 (volatile unsigned int *) 0x3001 
#define  LED3 (volatile unsigned int *) 0x3002 
#define  LED4 (volatile unsigned int *) 0x3003 
#define  LED5 (volatile unsigned int *) 0x3004 
#define  LED6 (volatile unsigned int *) 0x3005 
#define  LED7 (volatile unsigned int *) 0x3006
#define  LED8 (volatile unsigned int *) 0x3007 

Uint32 delay_count = 0;

void delay(void) {
	delay_count = CpuTimer0.InterruptCount;
	while( CpuTimer0.InterruptCount - delay_count <= 0) {
		delay_count =  CpuTimer0.InterruptCount;
	}
	CpuTimer0.InterruptCount = 0;
}


void basic_keys_show(void){
				*LED8 = 0x7F;
				*LED7 = 0x14;
				delay();
				*LED8 = 0xfe;
				*LED7 = 0x77;
				delay();
				*LED8 = 0xff;
				*LED7 = 0x77;
				delay();
				*LED8 = 0x3c;
				*LED7 = 0x77;
				delay();
				*LED8 = 0xef;
				*LED7 = 0x77;
				delay();
				*LED8 = 0xee;
				*LED7 = 0x77;
				delay();
				*LED8 = 0xdc;
				*LED7 = 0x77;
				delay();
				*LED8 = 0xbe;
				*LED7 = 0x77;
				delay();
				*LED8 = 0xbb;
				*LED7 = 0x77;
				delay();
				*LED8 = 0x1c;
				*LED7 = 0x77;
				delay();
}

void yellow_keys_show(void){
				*LED8 = 0xbe;
				*LED7 = 0x77;
				delay();
				*LED8 = 0xbb;
				*LED7 = 0x77;
				delay();
				*LED8 = 0x1c;
				*LED7 = 0x77;
				delay();
}

void main(void) {  
   int temp = 0;
   InitSysCtrl();								// system initialization
   DINT;         								// disable interrupts	
   InitPieCtrl();								// disable the PIE and clear all PIE registers
   IER = 0x0000;						
   IFR = 0x0000;						
   InitPieVectTable();							// initialize the PIE vector table with pointers to the shell Interrupt
   //InitPeripherals();							// initialize peripherals
   InitCpuTimers();
   PieCtrl.PIEIER1.bit.INTx7 = 1;				// enable PIE Group 1 INT7
   IER |= M_INT1;								// enable CPU INT1
   EINT;										// enable interrupts
   ERTM;										// enable debug interrupts
   ConfigCpuTimer(&CpuTimer0, 150, 1000000);	// initialize timer0
   StartCpuTimer0();							// start timer0
    EALLOW;

   GpioMuxRegs.GPFMUX.bit.MCLKXA_GPIOF8=0;
   GpioMuxRegs.GPFMUX.bit.MCLKRA_GPIOF9=0;
   GpioMuxRegs.GPFMUX.bit.MFSXA_GPIOF10=0;
   GpioMuxRegs.GPFMUX.bit.MFSRA_GPIOF11=0;
   GpioMuxRegs.GPFMUX.bit.MDXA_GPIOF12=0;
   
 
   GpioMuxRegs.GPFDIR.bit.GPIOF8=1;
   GpioMuxRegs.GPFDIR.bit.GPIOF9=1;
   GpioMuxRegs.GPFDIR.bit.GPIOF10=1;
   GpioMuxRegs.GPFDIR.bit.GPIOF11=1;
   GpioMuxRegs.GPFDIR.bit.GPIOF12=1;
  
   GpioMuxRegs.GPBDIR.bit.GPIOB9=1;
   GpioMuxRegs.GPBDIR.bit.GPIOB10=1; 
	EDIS;

   	*CPLDport2000=0x0;
	//The following is 8 digital tube zero
   	*LED1=0x0;			
   	*LED2=0x0;
   	*LED3=0x0;
   	*LED4=0x0;
   	*LED5=0x0;
   	*LED6=0x0;
   	*LED7=0x0;
   	*LED8=0x0;
   
   
   while(1) {
   		*CPLDport2000=0x03;              
		// CPLD of gating motherboard points to traffic light circuit 
   		GpioDataRegs.GPBDAT.bit.GPIOB9=0;
   		GpioDataRegs.GPBDAT.bit.GPIOB10=0;  
        
    	GpioDataRegs.GPFDAT.bit.GPIOF8=0;   
    	GpioDataRegs.GPFDAT.bit.GPIOF9=0;    
   		GpioDataRegs.GPFDAT.bit.GPIOF10=0;
    	GpioDataRegs.GPFDAT.bit.GPIOF11=0;
    	GpioDataRegs.GPFDAT.bit.GPIOF12=0;
        // delay(8000000);
        // temp=ScanKey(); 
		switch (temp) {
		case 0: 
				GpioDataRegs.GPFDAT.bit.GPIOF8=0;   
    			GpioDataRegs.GPFDAT.bit.GPIOF9=1;    
   				GpioDataRegs.GPFDAT.bit.GPIOF10=0;
    			GpioDataRegs.GPFDAT.bit.GPIOF11=1;
    			GpioDataRegs.GPFDAT.bit.GPIOF12=0;
				basic_keys_show();
				temp++;
			break;
		case 1:
				GpioDataRegs.GPFDAT.bit.GPIOF8=0;   
				GpioDataRegs.GPFDAT.bit.GPIOF9=1;    
   				GpioDataRegs.GPFDAT.bit.GPIOF10=0;
				GpioDataRegs.GPFDAT.bit.GPIOF11=1;
				GpioDataRegs.GPFDAT.bit.GPIOF12=1;
				yellow_keys_show();
				temp++;
			break;
		case 2:
				GpioDataRegs.GPFDAT.bit.GPIOF8=1;
				GpioDataRegs.GPFDAT.bit.GPIOF9=0;    
   				GpioDataRegs.GPFDAT.bit.GPIOF10=1;
				GpioDataRegs.GPFDAT.bit.GPIOF11=0;
				GpioDataRegs.GPFDAT.bit.GPIOF12=0;
				basic_keys_show();
				temp++;
			break;
		case 3:
				GpioDataRegs.GPFDAT.bit.GPIOF8=1;
				GpioDataRegs.GPFDAT.bit.GPIOF9=0;    
   				GpioDataRegs.GPFDAT.bit.GPIOF10=1;
				GpioDataRegs.GPFDAT.bit.GPIOF11=0;
				GpioDataRegs.GPFDAT.bit.GPIOF12=1;
				yellow_keys_show();
				temp = 0;
			break;
		default:
			break;
		}
                
    }
}




