#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
    TIM_TimeBaseInitTypeDef TIM_Timebasesturct;
    GPIO_InitTypeDef GPIO_Initsturct;
    TIM_OCInitTypeDef TIM_initsturct;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
  
    
    GPIO_Initsturct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_Initsturct.GPIO_Pin = GPIO_Pin_1;
    GPIO_Initsturct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_Initsturct);
    
    
    
    TIM_InternalClockConfig(TIM2);

    TIM_Timebasesturct.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_Timebasesturct.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_Timebasesturct.TIM_Period = 20000-1; //ARR
    TIM_Timebasesturct.TIM_Prescaler = 72-1; //PSC
    TIM_Timebasesturct.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2,&TIM_Timebasesturct);
    
   
    
    
    TIM_OCStructInit(&TIM_initsturct);
    TIM_initsturct.TIM_OCMode = TIM_OCMode_PWM1;
    TIM_initsturct.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_initsturct.TIM_OutputState = TIM_OutputState_Enable;
    TIM_initsturct.TIM_Pulse = 0;  //CRR
    TIM_OC2Init(TIM2,&TIM_initsturct);
    
    
    TIM_Cmd(TIM2,ENABLE);
}
void PWM_setcompare2(uint16_t compare)
{
    TIM_SetCompare2(TIM2,compare);
}

