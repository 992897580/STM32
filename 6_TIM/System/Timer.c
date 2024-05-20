#include "stm32f10x.h"                  // Device header

extern uint16_t nmb;
void Timer_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_Timebasesturct;
    NVIC_InitTypeDef NVIC_Initsturct;
    
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    
    TIM_InternalClockConfig(TIM2);
    
    
    TIM_Timebasesturct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_Timebasesturct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_Timebasesturct.TIM_Period = 10000-1;
    TIM_Timebasesturct.TIM_Prescaler = 7200-1;
    TIM_Timebasesturct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&TIM_Timebasesturct);
    
    TIM_ClearFlag(TIM2,TIM_FLAG_Update);
    
    
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    
    NVIC_Initsturct.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_Initsturct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Initsturct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_Initsturct.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_Initsturct);
    
    TIM_Cmd(TIM2,ENABLE);
    
    
    
    
}
void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update == SET))
    {
        nmb++;
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
}
