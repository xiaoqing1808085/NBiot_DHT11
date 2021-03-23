#ifndef __DHT_H__
#define __DHT_H__

#include "main.h"
#include "sys.h"
#include "usart.h"
#include "stdio.h"
#include "delay.h"
#include "gpio.h"




typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

//IO��������
//#define DHT11_IO_IN()  {IODHT22_GPIO_Port->CRH &= 0xFFFFF0FF;	IODHT22_GPIO_Port->CRH |= 8 << 8;}	// PC10 IN  MODE
//#define DHT11_IO_OUT() {IODHT22_GPIO_Port->CRH &= 0xFFFFF0FF;	IODHT22_GPIO_Port->CRH |= 3 << 8;}	// PC10 OUT MODE


//IO��������
#define	DHT11_DQ_OUT PCout(14) //���ݶ˿�	PC14
#define	DHT11_DQ_IN  PCin(14)  //���ݶ˿�	PC14

u8 DHT11_Init(void);//��ʼ��DHT11
u8 DHT11_Read_Data(u8 *temp, u8 *humi); //��ȡ��ʪ��
u8 DHT11_Read_Byte(void);//����һ���ֽ�
u8 DHT11_Read_Bit(void);//����һ��λ
u8 DHT11_Check(void);//����Ƿ����DHT11
void DHT11_Rst(void);//��λDHT11
u8 DHT11_Read_Data_Float(float *temp,float *humi);







#endif
