#include "dht.h"

void dht_mode(int sta)
{
	if(sta){
		GPIO_InitStruct.Pin = GPIO_PIN_14;
		GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
		HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);
	} else {
		GPIO_InitStruct.Pin = GPIO_PIN_14;
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
		HAL_GPIO_Init(LED_GPIO_Port, &GPIO_InitStruct);
	}
}


//��λDHT11
void DHT11_Rst(void)
{
    dht_mode(0); 	//SET OUTPUT
    DHT11_DQ_OUT=0; 	//����DQ
    HAL_Delay(20);    	//��������18ms,(DHT22 500us)
    DHT11_DQ_OUT=1; 	//DQ=1
    delay_us(30);    	//��������20~40us
}

//�ȴ�DHT11�Ļ�Ӧ
//����1:δ��⵽DHT11�Ĵ���
//����0:����
u8 DHT11_Check(void)
{
    u8 retry=0;
    dht_mode(1);//SET INPUT
    while (DHT11_DQ_IN&&retry<100)//DHT11������40~80us
    {
        retry++;
        delay_us(1);
    };
    if(retry>=100)return 1;
    else retry=0;
    while (!DHT11_DQ_IN&&retry<100)//DHT11���ͺ���ٴ�����40~80us
    {
        retry++;
        delay_us(1);
    };
    if(retry>=100)return 1;
    return 0;
}

//��DHT11��ȡһ��λ
//����ֵ��1/0
u8 DHT11_Read_Bit(void)
{
    u8 retry=0;
    while(DHT11_DQ_IN&&retry<100)//�ȴ���Ϊ�͵�ƽ
    {
        retry++;
        delay_us(1);
    }
    retry=0;
    while(!DHT11_DQ_IN&&retry<100)//�ȴ���ߵ�ƽ
    {
        retry++;
        delay_us(1);
    }
    delay_us(40);//�ȴ�40us
    if(DHT11_DQ_IN)return 1;
    else return 0;
}

//��DHT11��ȡһ���ֽ�
//����ֵ������������
u8 DHT11_Read_Byte(void)
{
    u8 i,dat;
    dat=0;
    for (i=0; i<8; i++)
    {
        dat<<=1;
        dat|=DHT11_Read_Bit();
    }
    return dat;
}

//��DHT11��ȡһ������
//temp:�¶�ֵ(��Χ:0~50��)
//humi:ʪ��ֵ(��Χ:20%~90%)
//����ֵ��0,����;1,��ȡʧ��
u8 DHT11_Read_Data(u8 *temp,u8 *humi)
{
    u8 buf[5];
    u8 i;
    DHT11_Rst();
    if(DHT11_Check()==0)
    {
        for(i=0; i<5; i++) //��ȡ40λ����
        {
            buf[i]=DHT11_Read_Byte();
        }
        if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
        {
            *humi=buf[0];
            *temp=buf[2];
        }
    } else return 1;
    return 0;
}

u8 DHT11_Read_Data_Float(float *temp,float *humi)
{
    u8 buf[5];
    u8 i;
    DHT11_Rst();
    if(DHT11_Check()==0)
    {
        for(i=0; i<5; i++) //��ȡ40λ����
        {
            buf[i]=DHT11_Read_Byte();
        }
        if((buf[0]+buf[1]+buf[2]+buf[3])==buf[4])
        {
			*humi=((buf[0] << 8) + buf[1]) / 10.0;
			*temp=((buf[2] << 8) + buf[3]) / 10.0;
        }
    } else return 1;
    return 0;
}

//��ʼ��DHT11��IO�� DQ ͬʱ���DHT11�Ĵ���
//����1:������
//����0:����
u8 DHT11_Init(void)
{
    u8 ret = 1;
    DHT11_Rst();  //��λDHT11
    ret = DHT11_Check();
    printf("dht11 init %s. \r\n", ret == 0 ? "ok" : "failed");
    return ret;
}

