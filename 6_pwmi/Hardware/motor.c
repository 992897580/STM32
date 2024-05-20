#include "stm32f10x.h"                  // Device header
#include "PWM.h"
void motor_init(void)
{
    
    GPIO_InitTypeDef GPIO_Initstructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Initstructure.GPIO_Pin = GPIO_Pin_4 | GPIO_Pin_5;
    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOA,&GPIO_Initstructure);  
    GPIO_ResetBits(GPIOA,GPIO_Pin_4 | GPIO_Pin_5);
    PWM_Init();
    
}
void motor_setspeed(int8_t speed)   
{
    if(speed >= 0)
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_4);
        GPIO_ResetBits(GPIOA,GPIO_Pin_5);
        PWM_setcompare1(speed);
    }
    else
    {
        GPIO_SetBits(GPIOA,GPIO_Pin_5);
        GPIO_ResetBits(GPIOA,GPIO_Pin_4);
        PWM_setcompare1(-speed);
    }
}
