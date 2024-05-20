#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "motor.h"
#include "KEY.h"
uint8_t key_nmb;
int8_t speed;
int main(void)
{

    OLED_Init();
    motor_init();
    KEY_Init();
    OLED_ShowString(1,1,"speed:");
    while(1)
    {
          key_nmb = KEY_GETnum();
          if(key_nmb == 1)
          {
              speed += 20;
              if(speed > 100)
              {
                  speed = -100;
              }
          }
          motor_setspeed(speed);
          OLED_ShowSignedNum(1,7,speed,3);
    }
    
}
