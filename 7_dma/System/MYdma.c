#include "stm32f10x.h"                  // Device header
uint16_t mydma_size;
void MYDMA_Init(uint32_t addra,uint32_t addrb,uint16_t size)
{
    DMA_InitTypeDef DMA_initsturct;
    mydma_size = size;
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
    //存储器和外设的设置，起始地址宽度是否自增
    DMA_initsturct.DMA_PeripheralBaseAddr = addra;//地址
    DMA_initsturct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//宽度
    DMA_initsturct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
    DMA_initsturct.DMA_MemoryBaseAddr = addrb;
    DMA_initsturct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_initsturct.DMA_MemoryInc = DMA_MemoryInc_Enable;
    //
    DMA_initsturct.DMA_DIR = DMA_DIR_PeripheralSRC;//传输方向
    DMA_initsturct.DMA_BufferSize = size;//传输计数器寄存器值
    DMA_initsturct.DMA_Mode = DMA_Mode_Normal;//是否自动重装
    DMA_initsturct.DMA_M2M = DMA_M2M_Enable;//dma是否是存储器到存储器(是否软件触发
    DMA_initsturct.DMA_Priority = DMA_Priority_Medium;//通道的优先级
    DMA_Init(DMA1_Channel1,&DMA_initsturct);
    
    
    DMA_Cmd(DMA1_Channel1,DISABLE);

}
void MYDMA_transfer(void)
{
    //再次传输，需要给dma失能
    DMA_Cmd(DMA1_Channel1,DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel1,mydma_size);
    DMA_Cmd(DMA1_Channel1,ENABLE);
    
    //转运完成之一
    while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
    DMA_ClearFlag(DMA1_FLAG_TC1);
}
