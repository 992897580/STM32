#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
#include "encoder_2.h"
int16_t speed;
int main(void)
{

    OLED_Init();
    Timer_Init();
    ENCODER2_init();
    OLED_ShowString(1,1,"speed:");
    while(1)
    {
        OLED_ShowSignedNum(1,7,speed,5);
    }
    
}


void TIM2_IRQHandler(void)
{
    if(TIM_GetITStatus(TIM2,TIM_IT_Update) == SET)
    {
        speed = encoder2_get();
        TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
    }
}
