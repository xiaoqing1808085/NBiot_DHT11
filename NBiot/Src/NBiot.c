#include "NBiot.h"


static void station_led()
{
		//失败LED闪烁3次，间隔2S
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		HAL_Delay(2000);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		HAL_Delay(2000);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		HAL_Delay(2000);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
		HAL_Delay(2000);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
		HAL_Delay(2000);
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_SET);
}


/*
	返回值：
		0：IP获取成功
		1：超时
*/


static int is_ip()
{
	int i = 0;
	int wait = 0;
	char ch;
	while(i != 7) {
		ch = getchar();
		if(ch == '\n') {
			i++;
		}
	}
	
	while((getchar() != '\n') && (wait != 20)){
		HAL_Delay(1000);
		wait++;
	}
	if(wait == 20) {
		return 1;
	} 
	
	return 0;
}



/*返回值
		0：OK
		1：ERROR
*/
int is_ok()
{
	while(getchar() != '\0'){
		if(getchar() == '\r'){
			if(getchar() == '\n') {
				if(getchar() == 'O')
				{
					return 0;
				} else if(getchar() == 'E') {
					return 1;
				}
				
			}
		}
	
	}
	
	return 2;
}

/*
	返回值：
		0：成功
		1：失败
*/

int nbiot_init()
{
	int i = 0;
	for(i = 0; i < 20; i++) {
		HAL_Delay(1000);
	}
		printf("ATE0\r\n");
		HAL_Delay(1000);
		printf("AT+EMQNEW=\"49.233.91.252\",\"1883\",12000,100\r\n");
		HAL_Delay(2500);
		
			printf("AT+EMQCON=0,3,\"myclientid\",1000,1,0\r\n");
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
			return 0;
}


#if 0
int nbiot_init()
{
	int i = 0;
	i = is_ip();
	if(i == 0) {
		HAL_Delay(2000);
		printf("ATE0\r\n");
		HAL_Delay(500);
		printf("ATE0\r\n");
		HAL_Delay(500);
		printf("AT+EMQNEW=\"49.233.91.252\",\"1883\",12000,100\r\n");
		if(is_ok() == 0) {
			printf("AT+EMQSUB=0,\"mytopic\",1\r\n");
			HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, GPIO_PIN_RESET);
			return 0;
		}else {
			station_led();
		}
		
		
	} else {
			station_led();
	}
	
	
	return 1;
}
#endif
