#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Timer.h"
uint16_t nmb = 0;
int main(void)
{
    
    OLED_Init();    
    OLED_ShowString(1,1,"nmb:");
    
    Timer_Init();
    
    
    
    while(1)
    {
        OLED_ShowNum(1,5,nmb,5);
       
    }
    
}
