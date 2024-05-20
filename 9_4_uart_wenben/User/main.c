#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include <string.h>
#include "Serial.h"
#include "LED.h"

//extern char buff[];
//extern uint8_t serial_rxflag;
int main(void)
{
    OLED_Init();
    Serial_init();
    LED_Init();
    OLED_ShowString(1,1,"tx:");
    OLED_ShowString(3,1,"rx:");

    while(1)
    {
       if(serial_rxflag == 1)
       {
           OLED_ShowString(4,1,"                ");
           OLED_ShowString(4,1,buff);
           
           if(strcmp(buff,"LED_ON") == 0)
           {
               LED1_ON();
               serial_sendstring("led_on_ok\r\n");
               OLED_ShowString(2,1,"                ");
               OLED_ShowString(2,1,"LED_on_ok");
           }else if(strcmp(buff,"LED_OFF") == 0)
           {
               LED1_OFF();
               serial_sendstring("led_off_ok\r\n");
               OLED_ShowString(2,1,"                ");
               OLED_ShowString(2,1,"LED_off_ok");
           }else{
                
               serial_sendstring("error_cmd\r\n");
               OLED_ShowString(2,1,"                ");
               OLED_ShowString(2,1,"error_cmd");
           }
           serial_rxflag = 0;
       }
    }
}
