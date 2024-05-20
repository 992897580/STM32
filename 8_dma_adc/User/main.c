#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"


int main(void)
{
    
    OLED_Init();
    AD_Init();
    
    
    
    while(1)
    {

        
//        AD_getvalue();
        
        OLED_ShowNum(1,5,AD_val[0],4);
        OLED_ShowNum(2,5,AD_val[1],4);
        OLED_ShowNum(3,5,AD_val[2],4);
        OLED_ShowNum(4,5,AD_val[3],4);
        
        Delay_ms(100);
    }
    
}
