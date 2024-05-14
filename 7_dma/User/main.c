#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "MYdma.h"
uint8_t dataa[] = {0x01,0x02,0x03,0x04};
uint8_t datab[] = {0,0,0,0};

int main(void)
{
    
    OLED_Init();
    MYDMA_Init((uint32_t)dataa,(uint32_t)datab,4);
    OLED_ShowHexNum(1,1,dataa[0],2);
    OLED_ShowHexNum(1,4,dataa[1],2);
    OLED_ShowHexNum(1,7,dataa[2],2);
    OLED_ShowHexNum(1,10,dataa[3],2);
    OLED_ShowHexNum(2,1,datab[0],2);
    OLED_ShowHexNum(2,4,datab[1],2);
    OLED_ShowHexNum(2,7,datab[2],2);
    OLED_ShowHexNum(2,10,datab[3],2);
    

    

    while(1)
    {
        MYDMA_transfer();
        dataa[0]++;
        dataa[1]++;
        dataa[2]++;
        dataa[3]++;
        Delay_ms(100);
       OLED_ShowHexNum(3,1,dataa[0],2);
       OLED_ShowHexNum(3,4,dataa[1],2);
       OLED_ShowHexNum(3,7,dataa[2],2);
       OLED_ShowHexNum(3,10,dataa[3],2);
       OLED_ShowHexNum(4,1,datab[0],2);
       OLED_ShowHexNum(4,4,datab[1],2);
       OLED_ShowHexNum(4,7,datab[2],2);
       OLED_ShowHexNum(4,10,datab[3],2);
        Delay_ms(100);
    }
    
}
