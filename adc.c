#include <xc.h>
#include <stdint.h>

#include "config.h"
#include "adc.h"


#define AVERAGE_COUNT 16
#define AVERAGE_SHIFT 4
#define AVERAGE_ADD 7

AdcStatus_t adc_status;
uint16_t adc_value;
uint16_t adc_sum;
uint8_t conversion_count;


void adc_init(void)
{
    //Initialize variables
    adc_status = ADC_NOT_READY;
    adc_value = 0;
    adc_sum = 0; 
    conversion_count = 0;
    
    //Configure ADC module
    ADCON0bits.CHS = 0b010010; // channel ANC2 (RC2) = pin 8, page 242
    ADCON1bits.ADFM = 1; // right justified
    ADCON1bits.ADCS = 0b110; //Fosc/64
    ADCON1bits.ADNREF = 0; // Negative reference = GND
    ADCON1bits.ADPREF = 0b00; // Positive Reference = VDD
    ADCON0bits.ADON = 1; // Enable module
    __delay_us(50); //Wait for cannel selection to become effective
    
    //Enable interrupts
    PIR1bits.ADIF = 0; //Clear interrupt flag
    INTCONbits.PEIE = 1; //Enable peripheral interrupts
    PIE1bits.ADIE = 1; //Enable ADC interrupts
    INTCONbits.GIE = 1; //Enable general interrupts
    
    //Start a first conversion
    ADCON0bits.ADGO = 1; 
}

void adc_read(void)
{
    uint16_t adc_val;
    
    if(!ADCON0bits.ADGO)
    {
        //Read result of ADC conversion
        adc_val = ADRESH;
        adc_val <<= 8;
        adc_val |= ADRESL;
        
        //Add new value to sum and increment count
        adc_sum += adc_val;
        conversion_count++;

        if(conversion_count==AVERAGE_COUNT)
        {
            //Calculate average
            adc_sum += AVERAGE_ADD;
            adc_value = adc_sum >> AVERAGE_SHIFT;
            
            //Reset adc_sum
            adc_sum = 0;
            
            //Reset count
            conversion_count = 0;

            //Signal that new result is ready
            adc_status = ADC_IS_READY;
        }

        //In any case, start a new conversion
        ADCON0bits.ADGO = 1;
    }
}

AdcStatus_t adc_ready(void)
{
    return adc_status;
}

uint16_t adc_getValue()
{
    //Reset status
    adc_status = ADC_NOT_READY;
    //Return averaged value
    return adc_value;
}


