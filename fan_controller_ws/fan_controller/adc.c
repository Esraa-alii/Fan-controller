/******************************************************************************
 *
 * Module: ADC
 *
 * File Name: adc.c
 *
 * Description: Source file for the ATmega32 ADC driver
 *
 * Author: Esraa Ali
 *
 *******************************************************************************/

#include "avr/io.h" /* To use the ADC Registers */
#include "adc.h"   /* The header file of the ADC driver*/
#include "common_macros.h" /* To use the macros like SET_BIT */



/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
/*
 * Description : Setup ADC Module
 * Arguments : pointer to the struct which contain needed member to init the adc
 * Return type : none
 */
void ADC_init(const ADC_Config_Type* Config_Ptr)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = Required Ref Voltage depends on Member in ADC_ConfigType structure
	 * ADLAR   = 8-bits of ADC output stored in ADC Lower Register and another 2-bits stored in ADC Higher Register
	 * MUX4:0  = initialized as channel 0
	 */
	ADMUX = (ADMUX & 0x3F) | ((Config_Ptr->Vref)<<6);

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADATE   = 0 Disable Auto Trigger
	 * ADPS2:0 = 011 to choose ADC_Clock = F_CPU/8 = 1Mhz/8 = 125Khz -> ADC must operate in range 50-200Khz
	 */
	ADCSRA = (1 << ADEN);
	ADCSRA = (ADCSRA & 0xF8) | (Config_Ptr->Clock);

}

/*
 * Description : Function responsible for read analog data from a certain ADC channel
                 and convert it to digital using the ADC driver using polling technique.
 * Arguments : channel number to be read .
 * Return type : none .
 */
uint16 ADC_readChannel(uint8 channel_num)
{
	channel_num &= 0x07; /* Input channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* Clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* Choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,ADSC); /* Start conversion write '1' to ADSC */
	while(BIT_IS_CLEAR(ADCSRA,ADIF)); /* Wait for conversion to complete, ADIF becomes '1' */
	SET_BIT(ADCSRA,ADIF); /* Clear ADIF by write '1' to it :) */
	return ADC; /* Read the digital value from the data register */
}

