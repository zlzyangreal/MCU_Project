#include "stdio.h"
#include <stdint.h>
#include <stdbool.h>
#include "hw_memmap.h"
#include "hw_types.h"
#include "hw_gpio.h"
#include "debug.h"
#include "fpu.h"
#include "gpio.h"
#include "pin_map.h"
#include "rom.h"
#include "sysctl.h"
#include "uart.h"
#include "uartstdio.h"
#include "SystickTime.h"



#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif


/*
*********************************************************************************************************
*	�� �� ��: PrintfLogo
*	����˵��: ��ӡ�������ƺ����̷�������, ���ϴ����ߺ󣬴�PC���Ĵ����ն�������Թ۲���
*	��    ��: ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void PrintfLogo(void)
{
	printf("*************************************************************\n\r");
	printf("* ��������   : %s\r\n", "���ڵδ�ʱ���ľ�׼��ʱ");	/* ��ӡ�������� */
	printf("* ���̰汾   : %s\r\n", "V1.0");		  /* ��ӡ���̰汾 */
	printf("* ��������   : %s\r\n", "20221125");	/* ��ӡ�������� */
	printf("* ��׼��汾 : TM4C123GH6PZT7\r\n");
	printf("* \r\n");	/* ��ӡһ�пո� */
	printf("* QQ    : 3138372165 \r\n");
	printf("* Email : 3138372165@qq.com \r\n");
	printf("* Copyright www.nameless.tech ��������\r\n");
	printf("*************************************************************\n\r");
}



void ConfigureUART(void)
{
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);// Enable the GPIO Peripheral used by the UART.
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);// Enable UART0
	ROM_GPIOPinConfigure(GPIO_PA0_U0RX);// Configure GPIO Pins for UART mode.
	ROM_GPIOPinConfigure(GPIO_PA1_U0TX);
	ROM_GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
	// Use the internal 16MHz oscillator as the UART clock source.
	// Initialize the UART for console I/O.
	UARTStdioConfig(0, 115200, 16000000);
	UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
}

int fputc(int ch, FILE *f){UARTCharPut(UART0_BASE,ch);	return (ch);}
int fgetc(FILE *f) {int ch=UARTCharGet(UART0_BASE);	return (ch);}
int main(void)
{  
	ROM_FPUEnable();//ʹ�ܸ��㵥Ԫ
	ROM_FPULazyStackingEnable();//�����ӳٶ�ջ,�����ж���Ӧ�ӳ�  
	ROM_SysCtlClockSet(SYSCTL_SYSDIV_2_5 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ |SYSCTL_OSC_MAIN);//����ϵͳʱ��
	ROM_SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_5);//��ɫ
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_6);//��ɫ
	ROM_GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_4);//��ɫ
	initTime();//��ʼ���δ�ʱ��
	ConfigureUART();//��ʼ������0
	PrintfLogo();//���ڴ�ӡ�汾��Ϣ
	while(1)
	{
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_5, 0);//�õ�λ����
		delay_ms(100);    
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_5, GPIO_PIN_5);//�ø�λϨ��
		delay_ms(100);

		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_6, 0);//�õ�λ����
		delay_ms(100);   
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_6, GPIO_PIN_6);//�ø�λϨ��
		delay_ms(100);

		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, 0);//�õ�λ����
		delay_ms(100);  
		GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_4, GPIO_PIN_4);//�ø�λϨ��
		delay_ms(100);
	}
}
