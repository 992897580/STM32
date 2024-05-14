#include "stm32f10x.h"                  // Device header
uint16_t mydma_size;
void MYDMA_Init(uint32_t addra,uint32_t addrb,uint16_t size)
{
    DMA_InitTypeDef DMA_initsturct;
    mydma_size = size;
    
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
    //�洢������������ã���ʼ��ַ����Ƿ�����
    DMA_initsturct.DMA_PeripheralBaseAddr = addra;//��ַ
    DMA_initsturct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;//���
    DMA_initsturct.DMA_PeripheralInc = DMA_PeripheralInc_Enable;
    DMA_initsturct.DMA_MemoryBaseAddr = addrb;
    DMA_initsturct.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    DMA_initsturct.DMA_MemoryInc = DMA_MemoryInc_Enable;
    //
    DMA_initsturct.DMA_DIR = DMA_DIR_PeripheralSRC;//���䷽��
    DMA_initsturct.DMA_BufferSize = size;//����������Ĵ���ֵ
    DMA_initsturct.DMA_Mode = DMA_Mode_Normal;//�Ƿ��Զ���װ
    DMA_initsturct.DMA_M2M = DMA_M2M_Enable;//dma�Ƿ��Ǵ洢�����洢��(�Ƿ��������
    DMA_initsturct.DMA_Priority = DMA_Priority_Medium;//ͨ�������ȼ�
    DMA_Init(DMA1_Channel1,&DMA_initsturct);
    
    
    DMA_Cmd(DMA1_Channel1,DISABLE);

}
void MYDMA_transfer(void)
{
    //�ٴδ��䣬��Ҫ��dmaʧ��
    DMA_Cmd(DMA1_Channel1,DISABLE);
    DMA_SetCurrDataCounter(DMA1_Channel1,mydma_size);
    DMA_Cmd(DMA1_Channel1,ENABLE);
    
    //ת�����֮һ
    while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
    DMA_ClearFlag(DMA1_FLAG_TC1);
}
