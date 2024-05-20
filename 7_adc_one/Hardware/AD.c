#include "stm32f10x.h"                  // Device header

void AD_Init(void)
{   
    ADC_InitTypeDef ADC_initstruct;
    
    
    //ʱ��ʹ��
    GPIO_InitTypeDef GPIO_Initstructure;
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
    
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    


    //����gpio
    GPIO_Initstructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Initstructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init(GPIOA,&GPIO_Initstructure);  
    //ѡ�������
    ADC_RegularChannelConfig(ADC1,ADC_Channel_0,1,ADC_SampleTime_55Cycles5);
    
    //��ʼ��adc
    ADC_initstruct.ADC_ContinuousConvMode = ENABLE;//��λ��ǵ���ת��
    ADC_initstruct.ADC_DataAlign = ADC_DataAlign_Right;//���䷽ʽ
    ADC_initstruct.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//�ⲿ����Դѡ��
    ADC_initstruct.ADC_Mode = ADC_Mode_Independent;//adcģʽ
    ADC_initstruct.ADC_NbrOfChannel = 1;//ͨ����Ŀ
    ADC_initstruct.ADC_ScanConvMode = DISABLE;//ɨ��ģʽ���ǵ���ģʽ
    ADC_Init(ADC1,&ADC_initstruct);
    
    //����adc��Դ
    ADC_Cmd(ADC1,ENABLE);
    
    //У׼
    ADC_ResetCalibration(ADC1);
    while(ADC_GetResetCalibrationStatus(ADC1) == SET);//���ظ�λУ׼��״̬
    
    ADC_StartCalibration(ADC1);//��ʼУ׼
    while(ADC_GetCalibrationStatus(ADC1) == SET);//�ȴ�У׼
    ADC_SoftwareStartConvCmd(ADC1,ENABLE);
}
uint16_t AD_getvalue(void)
{
    //adc��ʼ
    return ADC_GetConversionValue(ADC1);
}



