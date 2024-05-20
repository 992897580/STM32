#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "AD.h"

uint16_t advalue;
float voltage;
int main(void)
{
    
    OLED_Init();
    AD_Init();
    
    
    
    while(1)
    {
        advalue = AD_getvalue();
        voltage = (float)advalue / 4095*3.3;
        OLED_ShowNum(1,1,advalue,5);
        OLED_ShowNum(2,1,voltage,5);
        OLED_ShowNum(3,1,(uint16_t)(voltage*100)%100,2);
    }
    
}
