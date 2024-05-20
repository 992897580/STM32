#include "stm32f10x.h"                  // Device header
#include "Delay.h"
void KEY_Init(void)
{
    GPIO_InitTypeDef GPIO_Initstructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
   
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Initstructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11;
    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOB,&GPIO_Initstructure);    
}

uint8_t KEY_GETnum(void)
{
    uint8_t KEYnum = 0;
    //¶ÁÈ¡¶Ë¿Ú
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)
    {
        Delay_ms(20);
        while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)
        Delay_ms(20);
        KEYnum = 1;
    }
    if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0)
    {
        Delay_ms(20);
        while(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_11) == 0)
        Delay_ms(20);
        KEYnum = 2;
    }
    return KEYnum;
}
