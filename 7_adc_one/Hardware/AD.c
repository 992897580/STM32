#include "stm32f10x.h"                  // Device header

void AD_Init(void)
{   
    ADC_InitTypeDef ADC_initstruct;
    
    
    //时钟使能
    GPIO_InitTypeDef GPIO_Initstructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    


    //配置gpio
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Initstructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOA,&GPIO_Initstructure);  
    //选择规则组
    ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
    
    //初始化adc
    ADC_initstruct.ADC_ContinuousConvMode = ENABLE;//多次还是单次转换
    ADC_initstruct.ADC_DataAlign = ADC_DataAlign_Right;//对其方式
    ADC_initstruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//外部触发源选择
    ADC_initstruct.ADC_Mode = ADC_Mode_Independent;//adc模式
    ADC_initstruct.ADC_NbrOfChannel = 1;//通道数目
    ADC_initstruct.ADC_ScanConvMode = DISABLE;//扫描模式还是单次模式
    ADC_Init(ADC1,&ADC_initstruct);
    
    //开启adc电源
    ADC_Cmd(ADC1,ENABLE);
    
    //校准
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1) == SET);//返回复位校准的状态
    
    ADC_StartCalibration(ADC1);//开始校准
    while(ADC_GetCalibrationStatus(ADC1) == SET);//等待校准
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}
uint16_t AD_getvalue(void)
{
    //adc开始
    return ADC_GetConversionValue(ADC1);
}



