#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "stdarg.h"

char buff[50];
uint8_t serial_rxdata;
uint8_t serial_rxflag;



void Serial_init(void)
{   
    GPIO_InitTypeDef GPIO_INITstruct;
    USART_InitTypeDef USART_INITstruct;
    NVIC_InitTypeDef NVIC_initstruct;
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    GPIO_INITstruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_INITstruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_INITstruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_INITstruct);
    
    GPIO_INITstruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_INITstruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_INITstruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_INITstruct);
    
    USART_INITstruct.USART_BaudRate = 9600;
    USART_INITstruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_INITstruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    USART_INITstruct.USART_Parity = USART_Parity_No;
    USART_INITstruct.USART_StopBits = USART_StopBits_1;
    USART_INITstruct.USART_WordLength = USART_WordLength_8b;
    USART_Init(USART1,&USART_INITstruct);
    
    //÷–∂œΩ” ’
    USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    NVIC_initstruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_initstruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_initstruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_initstruct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_initstruct);
    
    
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


void USART1_IRQHandler(void)
{
    static uint8_t rxstate = 0;
    static uint8_t nub=0;
    if(USART_GetFlagStatus(USART1,USART_IT_RXNE) == SET)
    {   
        uint8_t rxdata = USART_ReceiveData(USART1);
        
        if(rxstate == 0)
        {
            if(rxdata == '@' && serial_rxflag == 0)
            {
                rxstate = 1;
                nub = 0;
            }
            
        }else if(rxstate == 1)
        {
            if(rxdata == '\r'){
                 rxstate = 2;
            }else{
             buff[nub] = rxdata;
             nub++;
            }
            
        }else if(rxstate == 2)
        {
            if(rxdata == '\n')
            {
                rxstate = 0;
                buff[nub] = '\0';
                serial_rxflag = 1;
            }
        }
        USART_ClearITPendingBit(USART1,USART_IT_RXNE);
    }
}


