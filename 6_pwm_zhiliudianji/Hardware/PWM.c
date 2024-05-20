#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_Timebasesturct;
    GPIO_InitTypeDef GPIO_Initsturct;
    TIM_OCInitTypeDef TIM_initsturct;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

//    GPIO_PinRemapConfig(GPIO_PartialRemap1_TIM2,ENABLE);
//    GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
//    
    
    GPIO_Initsturct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Initsturct.GPIO_Pin = GPIO_Pin_2;
    GPIO_Initsturct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Initsturct);
    
    
    
    TIM_InternalClockConfig(TIM2);

    TIM_Timebasesturct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_Timebasesturct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_Timebasesturct.TIM_Period = 100-1;
    TIM_Timebasesturct.TIM_Prescaler = 720-1;
    TIM_Timebasesturct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&TIM_Timebasesturct);
    
   
    
    
    TIM_OCStructInit(&TIM_initsturct);
    TIM_initsturct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_initsturct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_initsturct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_initsturct.TIM_Pulse = 0;  
    TIM_OC3Init(TIM2,&TIM_initsturct);
    
    
    TIM_Cmd(TIM2,ENABLE);
}
void PWM_setcompare3(uint16_t compare)
{
    TIM_SetCompare3(TIM2,compare);
}

