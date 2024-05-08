#include "stm32f10x.h"                  // Device header

void ENCODER2_init(void)
{
    TIM_TimeBaseInitTypeDef TIM_Timebasesturct;
    GPIO_InitTypeDef GPIO_Initsturct;
    TIM_ICInitTypeDef TIM_ICstruct;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    //GPIO配置
    GPIO_Initsturct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Initsturct.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_Initsturct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Initsturct);
    

    //时机单元
    TIM_Timebasesturct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_Timebasesturct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_Timebasesturct.TIM_Period = 65536-1;
    TIM_Timebasesturct.TIM_Prescaler = 1-1;
    TIM_Timebasesturct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3,&TIM_Timebasesturct);
    
    
    //滤波器和极性
    TIM_ICStructInit(&TIM_ICstruct);
    TIM_ICstruct.TIM_Channel = TIM_Channel_1;
    TIM_ICstruct.TIM_ICFilter = 0xF;
    TIM_ICstruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_PWMIConfig(TIM3,&TIM_ICstruct);
    
    TIM_ICstruct.TIM_Channel = TIM_Channel_2;
    TIM_ICstruct.TIM_ICFilter = 0xF;
    TIM_ICstruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_PWMIConfig(TIM3,&TIM_ICstruct);
    
    TIM_EncoderInterfaceConfig(TIM3,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
    
    TIM_Cmd(TIM3,ENABLE);
}
int16_t encoder2_get(void)
{
    
    
    int16_t temp;
    temp = TIM_GetCounter(TIM3);
    TIM_SetCounter(TIM3,0);
    return temp;
}


