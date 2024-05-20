#include "stm32f10x.h"                  // Device header

void BEE_Init(void)
{
    
    GPIO_InitTypeDef GPIO_Initstructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Initstructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOB,&GPIO_Initstructure);  
    GPIO_ResetBits(GPIOB,GPIO_Pin_12);
    

}
void BEE_ON(void)
{
    GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}
void BEE_OFF(void)
{
    GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

void BEE_TURN(void)
{
    if(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12) == 0)
    {
        GPIO_SetBits(GPIOB,GPIO_Pin_12);
        
    }
    else
    {
        GPIO_ResetBits(GPIOB,GPIO_Pin_12);
    }
}


