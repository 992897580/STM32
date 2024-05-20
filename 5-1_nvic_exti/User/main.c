#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "encoder.h"
int16_t nmb;

int main(void)
{
    
    OLED_Init();
    encoder_init();
    
    
    

    while(1)
    {
        nmb += encoder_get();
        OLED_ShowSignedNum(1,5,nmb,5);
    
    }
    
}
