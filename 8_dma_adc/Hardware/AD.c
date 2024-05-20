#include "stm32f10x.h"                  // Device header
uint16_t AD_val[4];
void AD_Init(void)
{   
    ADC_InitTypeDef ADC_initstruct;
    DMA_InitTypeDef DMA_initsturct;
    
    //时钟使能
    GPIO_InitTypeDef GPIO_Initstructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1,ENABLE);
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    


    //配置gpio
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Initstructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2| GPIO_Pin_3;
    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOA,&GPIO_Initstructure);  

    //四个通道
    ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_1,2,ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_2,3,ADC_SampleTime_55Cycles5);
    ADC_RegularChannelConfig(ADC1,ADC_Channel_3,4,ADC_SampleTime_55Cycles5);
    //初始化adc
    ADC_initstruct.ADC_ContinuousConvMode = ENABLE;//多次还是单次转换
    ADC_initstruct.ADC_DataAlign = ADC_DataAlign_Right;//对其方式
    ADC_initstruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//外部触发源选择
    ADC_initstruct.ADC_Mode = ADC_Mode_Independent;//adc模式
    ADC_initstruct.ADC_NbrOfChannel = 4;//通道数目
    ADC_initstruct.ADC_ScanConvMode = ENABLE;//扫描模式还是单次模式
    ADC_Init(ADC1,&ADC_initstruct);
    
    
    
    //开启dma
    
    
    
    
    //存储器和外设的设置，起始地址宽度是否自增
    DMA_initsturct.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;//地址
    DMA_initsturct.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;//宽度
    DMA_initsturct.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_initsturct.DMA_MemoryBaseAddr = (uint32_t)AD_val;
    DMA_initsturct.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_initsturct.DMA_MemoryInc = DMA_MemoryInc_Enable;
    //
    DMA_initsturct.DMA_DIR = DMA_DIR_PeripheralSRC;//传输方向
    DMA_initsturct.DMA_BufferSize = 4;//传输计数器寄存器值
    DMA_initsturct.DMA_Mode = DMA_Mode_Circular;//是否自动重装
    DMA_initsturct.DMA_M2M = DMA_M2M_Disable;//dma是否是存储器到存储器(是否软件触发
    DMA_initsturct.DMA_Priority = DMA_Priority_Medium;//通道的优先级
    DMA_Init(DMA1_Channel1,&DMA_initsturct);
    DMA_Cmd(DMA1_Channel1,ENABLE);
    
    //开启adc到dma的输出
    ADC_DMACmd(ADC1,ENABLE);
    //开启adc电源
    ADC_Cmd(ADC1,ENABLE);
    
    //校准
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1) == SET);//返回复位校准的状态
    
    ADC_StartCalibration(ADC1);//开始校准
    while(ADC_GetCalibrationStatus(ADC1) == SET);//等待校准
    
    
     ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}
//void AD_getvalue(void)
//{
//        //再次传输，需要给dma失能
//    DMA_Cmd(DMA1_Channel1,DISABLE);
//    DMA_SetCurrDataCounter(DMA1_Channel1,4);
//    DMA_Cmd(DMA1_Channel1,ENABLE);

//    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
//    
//        //转运完成之一
//    while(DMA_GetFlagStatus(DMA1_FLAG_TC1) == RESET);
//    DMA_ClearFlag(DMA1_FLAG_TC1);
//}



