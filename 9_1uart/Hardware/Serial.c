#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "stdarg.h"
void Serial_init(void)
{   
    GPIO_InitTypeDef GPIO_INITstruct;
    USART_InitTypeDef USART_INITstruct;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    GPIO_INITstruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_INITstruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_INITstruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_INITstruct);
    
    USART_INITstruct.USART_BaudRate = 9600;
    USART_INITstruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_INITstruct.USART_Mode = USART_Mode_Tx;
    USART_INITstruct.USART_Parity = USART_Parity_No;
    USART_INITstruct.USART_StopBits = USART_StopBits_1;
    USART_INITstruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1,&USART_INITstruct);
    
    
    USART_Cmd(USART1,ENABLE);
    
    
}    
void serial_senddata(uint16_t data)
{
    USART_SendData(USART1,data);
    while(USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET); 
}
void serial_sendarry(uint8_t *dataarry,uint16_t len)
{
    uint16_t i;
    for(i = 0;i<len;i++)
    {
        serial_senddata(dataarry[i]);
    }
}
void serial_sendstring(char *string)
{
    uint8_t i;
    for(i=0;string[i] != '\0';i++)
    {
        serial_senddata(string[i]);
    }
}
uint32_t serial_pow(uint32_t x,uint32_t y)
{
    uint32_t result = 1;
    while(y--)
    {
        result *= x;
    }
    return result;
}
void serial_sendnumber(uint32_t number,uint8_t len)
{
    uint8_t i;
    for(i = 0;i<len;i++)
    {
      serial_senddata(number/serial_pow(10,len-i-1)%10 + 0x30);
    }
}
int fputc(int ch,FILE *f)
{
    serial_senddata(ch);
    return ch;
}
void serial_printf(char *format,...)
{
    char string[100];
    va_list arg;
    va_start(arg,format);
    vsprintf(string,format,arg);
    va_end(arg);
    serial_sendstring(string);
}



