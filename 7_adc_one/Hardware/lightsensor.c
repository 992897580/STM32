#include "stm32f10x.h"                  // Device header
#include "lightsensor.h"
void lightsensor_init(void)
{
    GPIO_InitTypeDef GPIO_Initstructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
   
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Initstructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOB,&GPIO_Initstructure); 
}
uint8_t lightsensor_get(void)
{
    return GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_13);
}


