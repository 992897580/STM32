#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LED.h"
#include "KEY.h"
#include "bee.h"
#include "lightsensor.h"

uint8_t keynmb;

int main(void)
{
    
//    LED_Init();
//    
//    KEY_Init();
    BEE_Init();
    lightsensor_init();
    while(1)
    {
//        keynmb = KEY_GETnum();
//        if(keynmb == 1)
//        {
//            LED1_turn();
//        }
//        if(keynmb == 2)
//        {
//            LED2_turn();
//        }
//        BEE_ON();
//        Delay_ms(500);
//        BEE_OFF();
//        Delay_ms(500);
//        BEE_TURN();
//        Delay_ms(500);
        
        if(lightsensor_get() == 1)
        {
            BEE_ON();
        }
        else
        {
            BEE_OFF();
        }
        
        
    }
    
}
