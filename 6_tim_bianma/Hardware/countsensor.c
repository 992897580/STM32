#include "stm32f10x.h"                  // Device header


uint16_t countsensor_count = 0;
void countsensor_init(void)
{
    EXTI_InitTypeDef EXTI_INITS;
    GPIO_InitTypeDef GPIO_INIT;
    NVIC_InitTypeDef NVIC_INITS;
    
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    
    
    GPIO_INIT.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_INIT.GPIO_Pin = GPIO_Pin_14;
    GPIO_INIT.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_INIT);
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource14);
    
    
    
    EXTI_INITS.EXTI_Line = EXTI_Line14;
    EXTI_INITS.EXTI_LineCmd = ENABLE;
    EXTI_INITS.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_INITS.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_INITS);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    NVIC_INITS.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_INITS.NVIC_IRQChannelCmd = ENABLE;
    NVIC_INITS.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_INITS.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_INITS);
}
uint16_t countsensor_get(void)
{
    return countsensor_count;
}


void EXTI15_10_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line14) == SET)
    {
        countsensor_count++;
        EXTI_ClearITPendingBit(EXTI_Line14);
    }
    
    
    
}
