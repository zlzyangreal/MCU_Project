/* Copyright (c)  2018-2025 Wuhan Nameless Innovation Technology Co.,Ltd. All rights reserved.*/
/*----------------------------------------------------------------------------------------------------------------------/
*               ������ֻ��������ѧϰʹ�ã���Ȩ����Ȩ���������ƴ��Ŷӣ������ƴ��Ŷӽ��ɿس���Դ���ṩ�������ߣ�
*               ������ҪΪ�����ƴ��Ŷ��ṩ������δ��������ɣ����ý�Դ�����ṩ�����ˣ����ý�Դ����ŵ����Ϲ�����������أ� 
*               �������Դ�����Ĳ�����緢��������Ϊ�������ƴ��Ŷӽ���֮�Է��ɽ��������
-----------------------------------------------------------------------------------------------------------------------/
*               ������Ϣ���ܶ���ֹ��ǰ�����������˳���������
*               ��Դ���ף���ѧ����ϧ��ף������Ϯ�����׳ɹ�������
*               ѧϰ�����ߣ��������Ƽ���DJI��ZEROTECH��XAG��AEE��GDU��AUTEL��EWATT��HIGH GREAT�ȹ�˾��ҵ
*               ��ְ�����뷢�ͣ�15671678205@163.com���豸ע��ְ����λ����λ��������
*               �����ƴ���Դ�ɿ�QQȺ��540707961
*               CSDN���ͣ�http://blog.csdn.net/u011992534
*               �ſ�ID��NamelessCotrun����С��
*               Bվ��ѧ��Ƶ��https://space.bilibili.com/67803559/#/video
*               �ͻ�ʹ���ĵá��Ľ������������http://www.openedv.com/forum.php?mod=viewthread&tid=234214&extra=page=1
*               �Ա����̣�https://shop348646912.taobao.com/?spm=2013.1.1000126.2.5ce78a88ht1sO2
*               �ٶ�����:�����ƴ���Դ�ɿ�
*               ��˾����:www.nameless.tech
*               �޸�����:2019/4/12
*               �汾����Ӯ�ߡ���CarryPilot_V1.0
*               ��Ȩ���У�����ؾ���
*               Copyright(C) 2017-2025 �人�������¿Ƽ����޹�˾ 
*               All rights reserved
*               ��Ҫ��ʾ��
*               �����Ա�����ת�ֵķɿء��������ѡ�����ѧ�ܵĶ����Խ��ۺ�Ⱥѧϰ������
*               ����ֱ�����������������������ϣ��������´�����������Ȩ�����˲��ý�
*               ���ϴ��봫���Ϲ��������أ�������ı��ΪĿ���������ϴ��룬�����д˲�
*               ���ߣ���˾����ǰ��֪����1���ڼ�ʱ�����������ѧУ����λ����������
*               ������ַ��Ϣ�ᱻ�����ڹ�˾�������ٷ�΢�Ź���ƽ̨���ٷ��������͡�֪��
*               ר���Լ��Ա�������ҳ���Թ�ʾ���棬����������Ϊ�����Ϊ�����۵㣬Ӱ��
*               ��ѧ���ҹ���������������ܿ�ͺ������˻����������������ء�
*               �����Ϊ����˾����ش���ʧ�ߣ����Է���;���������л���ĺ�����лл������
----------------------------------------------------------------------------------------------------------------------*/
#ifndef __OLED_H
#define __OLED_H


//#define  OLED_WORK_MODE_I2C//OLEDʹ��I2Cģʽ������������SPIģʽʱ��ע�ͱ��м���


#define LCD_TFT_ENABLE 0

#define Bit_SET   1
#define Bit_RESET 0
#define SYSCTL_PERIPH_GPIO_OLED SYSCTL_PERIPH_GPIOA
#define GPIO_OLED   GPIO_PORTA_BASE 
#define LCD_DCout(data)		  GPIOPinWrite(GPIO_OLED, GPIO_PIN_2, data ? GPIO_PIN_2 : 0)//DC
#define LCD_RSTout(data)		GPIOPinWrite(GPIO_OLED, GPIO_PIN_3, data ? GPIO_PIN_3 : 0)//RST
#define LCD_SDAout(data)		GPIOPinWrite(GPIO_OLED, GPIO_PIN_4, data ? GPIO_PIN_4 : 0)//SDA
#define LCD_SCLout(data)		GPIOPinWrite(GPIO_OLED, GPIO_PIN_5, data ? GPIO_PIN_5 : 0)//SCL


#define READ_SDA   GPIOPinRead(GPIO_OLED,GPIO_PIN_4)	//SDA 
#define IIC_SDA_H  GPIOPinWrite(GPIO_OLED,GPIO_PIN_4,GPIO_PIN_4)//SDA 
#define IIC_SDA_L  GPIOPinWrite(GPIO_OLED,GPIO_PIN_4,0)//SDA
#define IIC_SCL_H  GPIOPinWrite(GPIO_OLED,GPIO_PIN_5,GPIO_PIN_5)//SCL
#define IIC_SCL_L  GPIOPinWrite(GPIO_OLED,GPIO_PIN_5,0)//SCL

void LCD_WrDat(unsigned char dat);
void LCD_WrCmd(unsigned char cmd);
void OLED_WrCmd(unsigned char IIC_Data);
void OLED_WrDat(unsigned char IIC_Data);
void LCD_Set_Pos(unsigned char x, unsigned char y);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void LCD_P6x8Char(unsigned char x,unsigned char  y,unsigned char ch);
void LCD_P6x8Str(unsigned char x,unsigned char  y,unsigned char ch[]);
void write_6_8_number(unsigned char x,unsigned char  y,float number);
void LCD_P8x16Char(unsigned char x,unsigned char  y,unsigned char ch);
void LCD_P8x16Str(unsigned char x,unsigned char  y,unsigned char ch[]);
void write_8_16_number(unsigned char x,unsigned char  y,float number);
void LCD_clear_L(unsigned char x,unsigned char y);
void OLED_Init(void);
void OLED_Init_Fast(void);
void Draw_Logo(void);
void Draw_Logo1(void);
void LCD_CLS(void);

void display_6_8_number(unsigned char x,unsigned char y, float number);
void display_6_8_string(unsigned char x,unsigned char  y,unsigned char ch[]);
	
#endif



