/* 
 * File:   adc.h
 * Author: luke
 *
 * Created on 29. Oktober 2019, 20:03
 */

#ifndef ADC_H
#define	ADC_H

#define ADC_INTERRUPT_FLAG PIR1bits.ADIF

typedef enum
{
    ADC_NOT_READY = 0,
	ADC_IS_READY = 1
} AdcStatus_t;

//Function prototypes
void adc_init(void);
AdcStatus_t adc_ready(void);
void adc_read(void);
uint16_t adc_getValue();


#endif	/* ADC_H */

