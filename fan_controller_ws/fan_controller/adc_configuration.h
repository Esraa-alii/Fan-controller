/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc_configuration.h
 *
 * Description: header file for the ATmega32 ADC driver
 *
 * Author: Esraa Ali
 *
 *******************************************************************************/
#ifndef ADC_CONFIGURATION_H_
#define ADC_CONFIGURATION_H_
#include "std_types.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
#define ADC_MAXIMUM_VALUE    1023
#define ADC_REF_VOLT_VALUE   2.56 /*volt of the battery connected to the AREF Pin*/

/*******************************************************************************
 *                              Types Declaration                              *
 *******************************************************************************/
typedef enum{
	AREF,AVCC,Reversed,Internal
}ADC_vref;

typedef enum{
	Left,Right
}ADC_Adjust_Result;

typedef enum{
	Disabled,Enabled
}ADC_auto_trigger_enable;

typedef enum{
	FCPU_2=1,FCPU_4,FCPU_8,FCPU_16,FCPU_32,FCPU_64,FCPU_128
}ADC_freq;

typedef enum{
	Free_running,Analog_comparator,External_interrupt0,Timer0_compare,Timer0_overflow,Timer1_compareB,Timer1_overflow,Timer1_captureEvent
}ADC_auto_trigger_source;

typedef struct{
	ADC_vref Vref;
	ADC_Adjust_Result Adjust_Result;
	ADC_auto_trigger_enable AutoTrigger_Enable;
	ADC_freq Clock;
	ADC_auto_trigger_source AutoTrigger_Source;
}ADC_Config_Type;

#endif
