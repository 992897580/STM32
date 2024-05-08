#include "stm32f10x.h"                  // Device header

int16_t encoder_cont = 0;

void encoder_init(void)
{
    EXTI_InitTypeDef EXTI_INITS;
    GPIO_InitTypeDef GPIO_INIT;
    NVIC_InitTypeDef NVIC_INITS;
    
    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
    
    
    GPIO_INIT.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_INIT.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_INIT.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&GPIO_INIT);
    
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
    
    
    EXTI_INITS.EXTI_Line = EXTI_Line0 | EXTI_Line1;
    EXTI_INITS.EXTI_LineCmd = ENABLE;
    EXTI_INITS.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_INITS.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_INITS);
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    NVIC_INITS.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_INITS.NVIC_IRQChannelCmd = ENABLE;
    NVIC_INITS.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_INITS.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_INITS);
    
    NVIC_INITS.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_INITS.NVIC_IRQChannelCmd = ENABLE;
    NVIC_INITS.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_INITS.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_INITS);
    
}

int16_t encoder_get(void)
{
    int16_t temp;
    temp = encoder_cont;
    encoder_cont = 0;
    return temp;
}

void EXTI0_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line0) == SET)
    {
        if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1) == 0)
        {
            encoder_cont--;
        }
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
}
void EXTI1_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line1) == SET)
    {
        if(GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) == 0)
        {
            encoder_cont++;
        }
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}

