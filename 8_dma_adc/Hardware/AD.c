#include "stm32f10x.h"                  // Device header
uint16_t AD_val[4];
void AD_Init(void)
{   
    ADC_InitTypeDef ADC_initstruct;
    DMA_InitTypeDef DMA_initsturct;
    
    //ʱ��ʹ��
    GPIO_InitTypeDef GPIO_Initstructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    


    //����gpio
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Initstructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3;
    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOA,&GPIO_Initstructure);  

    //�ĸ�ͨ��
    ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_55Cycles5);
    //��ʼ��adc
    ADC_initstruct.ADC_ContinuousConvMode = ENABLE;//��λ��ǵ���ת��
    ADC_initstruct.ADC_DataAlign = ADC_DataAlign_Right;//���䷽ʽ
    ADC_initstruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�ⲿ����Դѡ��
    ADC_initstruct.ADC_Mode = ADC_Mode_Independent;//adcģʽ
    ADC_initstruct.ADC_NbrOfChannel = 4;//ͨ����Ŀ
    ADC_initstruct.ADC_ScanConvMode = ENABLE;//ɨ��ģʽ���ǵ���ģʽ
    ADC_Init(ADC1,&ADC_initstruct);
    
    
    
    //����dma
    
    
    
    
    //�洢������������ã���ʼ��ַ����Ƿ�����
    DMA_initsturct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;//��ַ
    DMA_initsturct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//���
    DMA_initsturct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_initsturct.DMA_MemoryBaseAddr = (uint32_t)AD_val;
    DMA_initsturct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_initsturct.DMA_MemoryInc = DMA_MemoryInc_Enable;
    //
    DMA_initsturct.DMA_DIR = DMA_DIR_PeripheralSRC;//���䷽��
    DMA_initsturct.DMA_BufferSize = 4;//����������Ĵ���ֵ
    DMA_initsturct.DMA_Mode = DMA_Mode_Circular;//�Ƿ��Զ���װ
    DMA_initsturct.DMA_M2M = DMA_M2M_Disable;//dma�Ƿ��Ǵ洢�����洢��(�Ƿ��������
    DMA_initsturct.DMA_Priority = DMA_Priority_Medium;//ͨ�������ȼ�
    DMA_Init(DMA1_Channel1,&DMA_initsturct);
    DMA_Cmd(DMA1_Channel1,ENABLE);
    
    //����adc��dma�����
    ADC_DMACmd(ADC1,ENABLE);
    //����adc��Դ
    ADC_Cmd(ADC1,ENABLE);
    
    //У׼
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1) == SET);//���ظ�λУ׼��״̬
    
    ADC_StartCalibration(ADC1);//��ʼУ׼
    while(ADC_GetCalibrationStatus(ADC1) == SET);//�ȴ�У׼
    
    
     ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}
//void AD_getvalue(void)
//{
//        //�ٴδ��䣬��Ҫ��dmaʧ��
//    DMA_Cmd(DMA1_Channel1,DISABLE);
//    DMA_SetCurrDataCounter(DMA1_Channel1,4);
//    DMA_Cmd(DMA1_Channel1,ENABLE);

//    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
//    
//        //ת�����֮һ
//    while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
//    DMA_ClearFlag(DMA1_FLAG_TC1);
//}



