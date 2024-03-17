//
//      TMDX ALPHA RELEASE
//      Intended for product evaluation purposes
//
//###########################################################################
//
// FILE:	DSP28_Gpio.c
//
// TITLE:	DSP28 General Purpose I/O Initialization & Support Functions.
//
//###########################################################################
//
//  Ver | dd mmm yyyy | Who  | Description of changes
// =====|=============|======|===============================================
//  0.55| 06 May 2002 | L.H. | EzDSP Alpha Release
//  0.56| 20 May 2002 | L.H. | No change
//  0.57| 27 May 2002 | L.H. | No change
//###########################################################################

#include "DSP28_Device.h"

//---------------------------------------------------------------------------
// InitGpio: 
//---------------------------------------------------------------------------
// This function initializes the Gpio to a known state.
//
void InitGpio(void)
{

// Set GPIO A port pins,AL(Bits 7:0)(input)-AH(Bits 15:8) (output) 8bits
// Input Qualifier =0, none
     EALLOW;
     GpioMuxRegs.GPAMUX.all=0x0000;     
     GpioMuxRegs.GPADIR.all=0x0000;    	// upper byte as output/low byte as input
//   GpioMuxRegs.GPAQUAL.all=0x0000;	// Input qualifier disabled
     
     GpioMuxRegs.GPBMUX.all=0x0000;     
     GpioMuxRegs.GPBDIR.all=0x0000;  
     GpioMuxRegs.GPDMUX.all=0x0000;     
     GpioMuxRegs.GPDDIR.all=0x0000;  
     GpioMuxRegs.GPEMUX.all=0x0000;     
     GpioMuxRegs.GPEDIR.all=0x0000;  
     GpioMuxRegs.GPFMUX.all=0x0000;     
     GpioMuxRegs.GPFDIR.all=0x0000;  
     GpioMuxRegs.GPGMUX.all=0x0000;     
     GpioMuxRegs.GPGDIR.all=0x0000;  




// Set GPIO B port pins, configured as EVB signals
// Input Qualifier =0, none
// Set bits to 1 to configure peripherals signals on the pins
 //    GpioMuxRegs.GPBMUX.all=0xFFFF;   
 //   GpioMuxRegs.GPBQUAL.all=0x0000;	// Input qualifier disabled
     EDIS;

}	
	
//===========================================================================
// No more.
//===========================================================================
