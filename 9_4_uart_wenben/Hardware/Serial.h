#ifndef __SERIAL_H_
#define __SERIAL_H_

#include "stdio.h"

extern uint8_t txbuff[];
extern uint8_t rxbuff[];


void Serial_init(void);
void serial_senddata(uint16_t data);
void serial_sendarry(uint8_t *dataarry,uint16_t len);
void serial_sendstring(char *string);
void serial_sendnumber(uint32_t number,uint8_t len);
uint32_t serial_pow(uint32_t x,uint32_t y);
void serial_printf(char *format,...);
void serial_sendbuff(void);
uint8_t serial_getrxflag(void);


#endif
