#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
#include "key.h"

uint8_t keynmb;

int main(void)
{
    OLED_Init();
    KEY_Init();
    Serial_init();
    OLED_ShowString(1,1,"tx:");
    OLED_ShowString(3,1,"rx:");
    
    txbuff[0] = 0x01;
    txbuff[1] = 0x02;
    txbuff[2] = 0x03;
    txbuff[3] = 0x04;
    
    serial_sendbuff();
    while(1)
    {
        keynmb = KEY_GETnum();
        if(keynmb == 1)
        {
            //·¢ËÍ
                txbuff[0] ++;
                txbuff[1] ++;
                txbuff[2] ++;
                txbuff[3] ++;
             serial_sendbuff();
            
            OLED_ShowHexNum(2,1,txbuff[0],2);
            OLED_ShowHexNum(2,4,txbuff[1],2);
            OLED_ShowHexNum(2,7,txbuff[2],2);
            OLED_ShowHexNum(2,10,txbuff[3],2);
        }
        
        
        if(serial_getrxflag() == 1)
        {
            OLED_ShowHexNum(4,1,rxbuff[0],2);
            OLED_ShowHexNum(4,4,rxbuff[1],2);
            OLED_ShowHexNum(4,7,rxbuff[2],2);
            OLED_ShowHexNum(4,10,rxbuff[3],2);
        }
    }
}
