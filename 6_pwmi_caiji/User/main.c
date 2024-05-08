#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "PWM.h"
#include "IC.h"
int main(void)
{

    OLED_Init();
    PWM_Init();
    IC_Init();
    OLED_ShowString(1,1,"freq:00000hz");
    PWM_setpsc(720-1);
    PWM_setcompare1(50);
    while(1)
    {
         OLED_ShowNum(1,6,IC_getfreq(),5);
    }
    
}
