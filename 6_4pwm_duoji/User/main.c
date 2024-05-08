#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "KEY.h"
#include "servo.h"

uint8_t keynum;
float angle;
int main(void)
{

    OLED_Init();
    Servo_Init();
    KEY_Init();
    OLED_ShowString(1,1,"angle:");
    
    while(1)
    {
        keynum = KEY_GETnum();
        if(keynum == 1)   
        {
            angle += 30;
            if(angle >180)
            {
                angle = 0;
            }
        }
        Servo_setangle(angle);
        OLED_ShowNum(1,7,angle,3);
    }
    
}
