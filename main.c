/* Main file for DC Motor Controller
 * 
 * File:   main.c
 * Author: Lukas Faessler
 * Visit www.soldernerd.com for schematics, photos and more
 *
 * Created on 2023-01-12
 */

#include <xc.h>
#include <stdint.h>
#include <math.h>

#include "config.h"
#include "adc.h"
#include "pwm.h"

//Global variables
uint8_t portA = 0x00;
uint8_t portC = 0x00;
int8_t encoder1_count;
uint8_t encoder1_button;
int8_t encoder2_count;
uint8_t encoder2_button;

//Function prototypes
void turn_on(void);
void turn_off(void);

/*
void interrupt _isr(void)
{
        if(PIR1bits.TMR1IF)
        {
            timer1_isr();
            return;
        }

    //encoder_isr();
}
*/

void interrupt _isr(void)
{
    if(ADC_INTERRUPT_FLAG)
    {
        //Read ADC and start a new conversion
        adc_read();
        //Clear interrupt flag
        ADC_INTERRUPT_FLAG = 0;
        
        //Set duty cycle if a new averaged value is available
        if(adc_ready())
        {
            pwm_set_dutycycle(adc_getValue());
        }       
    }
}


void init(void)
{
    //Configure pin 11 for LED output and turn it on
    LED_TRIS = 0;
    LED_PIN = 1;
    
    //Configure pin 6 for ENABLE output and turn it off
    ENABLE_TRIS = 0;
    ENABLE_PIN = 0;
    
    //Configure pin 6 for PWM output and turn it off
    PWM_TRIS = 0;
    PWM_PIN = 0;
    
    //Configure pin 9 for MOTOR_ON as digital input
    MOTOR_ON_TRIS = 1;
    MOTOR_ON_ANSEL = 0;
    
    //Initialize ADC
    adc_init();

    //Initialize PWM
    pwm_init(); 
}


void main(void) 
{
    uint8_t cntr;
    init(); 
    
    ENABLE_PIN = 1;
    
    while(1)
    {
        for(cntr=0;cntr<200;cntr++)
        {
            
        }
        PWM_PIN = 1;
        
        for(cntr=0;cntr<80;cntr++)
        {
            
        }
        PWM_PIN = 0;
        
        
        if(MOTOR_ON_PIN)
        {
            LED_PIN = 0;
            ENABLE_PIN = 0;
        }   
        else
        {
            LED_PIN = 1;
            ENABLE_PIN = 1;
        }
        
    }
    

}
