#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Serial.h"
uint8_t rxdata;
int main(void)
{
    //char string[100];
   //uint8_t myarr[] = {0x42,0x43,0x44};
    OLED_Init();
    Serial_init();
   // serial_senddata(0x41);
    
//    
//   
//    //serial_sendarry(myarr,3);
//    //serial_sendstring("helloworld!");
//    serial_sendnumber(12345,5);
//    
////    printf("num = %d\r\n",666);
////    
//    sprintf(string,"num = %d\r\n",666);
////    serial_sendstring(string);
//    
//    
//    
//    serial_printf(string,"num = %d\r\n",666);
    while(1)
    {
      if(serial_getrxflag() == 1)
      {
          rxdata = serial_getrxdata();
          serial_senddata(rxdata);
          OLED_ShowHexNum(1,1,rxdata,2);
      }
    }
    
}
