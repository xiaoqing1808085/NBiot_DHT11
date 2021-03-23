#include "message.h"


int32_t string_number(char *str)
{
	int32_t num = 0;

	while(str[num] != '}'){
		num++;
	}
	
	return (num+1);
}




char *string_to_hex(char* str)
{
	int32_t i = 0,end,a = 0;
	
	end = string_number(str);
	
	for(i = 0; i < end; i++){
		switch(str[i]){
			case '{':
				message[a++] = '7';
				message[a++] = 'b';
				break;
			case '}':
				message[a++] = '7';
				message[a++] = 'd';
				break;
			case ':':
				message[a++] = '3';
				message[a++] = 'a';
				break;
			case '"':
				message[a++] = '2';
				message[a++] = '2';
				break;
			case ',':
				message[a++] = '2';
				message[a++] = 'c';
				break;
			case '	':
				message[a++] = '0';
				message[a++] = '9';
				break;
			case '\n':
				message[a++] = '0';
				message[a++] = 'a';
				break;
			case 't':
				message[a++] = '7';
				message[a++] = '4';
				break;
			case 'h':
				message[a++] = '6';
				message[a++] = '8';
				break;
			case '0':
				message[a++] = '3';
				message[a++] = '0';
				break;
			case '1':
				message[a++] = '3';
				message[a++] = '1';
				break;
			case '2':
				message[a++] = '3';
				message[a++] = '2';
				break;
			case '3':
				message[a++] = '3';
				message[a++] = '3';
				break;
			case '4':
				message[a++] = '3';
				message[a++] = '4';
				break;
			case '5':
				message[a++] = '3';
				message[a++] = '5';
				break;
			case '6':
				message[a++] = '3';
				message[a++] = '6';
				break;
			case '7':
				message[a++] = '3';
				message[a++] = '7';
				break;
			case '8':
				message[a++] = '3';
				message[a++] = '8';
				break;
			case '9':
				message[a++] = '3';
				message[a++] = '9';
				break;				
			default:message[a++] = '?';
				break;
		}
	}
	
	return message;
}
