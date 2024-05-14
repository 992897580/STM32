#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

uint16_t ad0,ad1,ad2,ad3;
int main(void)
{
    
    OLED_Init();
    AD_Init();
    
    
    
    while(1)
    {
        ad0 = AD_getvalue(ADC_Channel_0);
        ad1 = AD_getvalue(ADC_Channel_1);
        ad2 = AD_getvalue(ADC_Channel_2);
        ad3 = AD_getvalue(ADC_Channel_3);
        
        
        
        OLED_ShowNum(1,5,ad0,4);
        OLED_ShowNum(2,5,ad1,4);
        OLED_ShowNum(3,5,ad2,4);
        OLED_ShowNum(4,5,ad3,4);
    }
    
}
