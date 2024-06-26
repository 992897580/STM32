#include "stm32f10x.h"                  // Device header
void IC_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_Timebasesturct;
    GPIO_InitTypeDef GPIO_Initsturct;
    TIM_ICInitTypeDef TIM_ICstruct;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);

    
    GPIO_Initsturct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Initsturct.GPIO_Pin = GPIO_Pin_6;
    GPIO_Initsturct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Initsturct);
    
    
    
    TIM_InternalClockConfig(TIM3);

    TIM_Timebasesturct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_Timebasesturct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_Timebasesturct.TIM_Period = 65536-1;
    TIM_Timebasesturct.TIM_Prescaler = 72-1;
    TIM_Timebasesturct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM3,&TIM_Timebasesturct);
    
    TIM_ICstruct.TIM_Channel = TIM_Channel_1;
    TIM_ICstruct.TIM_ICFilter = 0xF;
    TIM_ICstruct.TIM_ICPolarity = TIM_ICPolarity_Rising;
    TIM_ICstruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
    TIM_ICstruct.TIM_ICSelection = TIM_ICSelection_DirectTI;
//    TIM_ICInit(TIM3,&TIM_ICstruct);
//    TIM_ICstruct.TIM_Channel = TIM_Channel_2;
//    TIM_ICstruct.TIM_ICFilter = 0xF;
//    TIM_ICstruct.TIM_ICPolarity = TIM_ICPolarity_Falling;
//    TIM_ICstruct.TIM_ICPrescaler = TIM_ICPSC_DIV1;
//    TIM_ICstruct.TIM_ICSelection = TIM_ICSelection_IndirectTI;
//    TIM_ICInit(TIM3,&TIM_ICstruct);
    TIM_PWMIConfig(TIM3,&TIM_ICstruct);
    
    
    TIM_SelectInputTrigger(TIM3,TIM_TS_TI1FP1);
    
    TIM_SelectSlaveMode(TIM3,TIM_SlaveMode_Reset);
    
    TIM_Cmd(TIM3,ENABLE);
}

uint32_t IC_getfreq(void)
{
    return 1000000 / (TIM_GetCapture1(TIM3)+1);
}
uint32_t IC_getduty(void)
{
    return (TIM_GetCapture2(TIM3)+1) * 100 / (TIM_GetCapture1(TIM3)+1);
}

