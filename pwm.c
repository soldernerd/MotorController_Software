
#include <xc.h>
#include <stdint.h>

#include "config.h"
#include "pwm.h"


void pwm_init(void)
{ 
    PPSUnLock()
    PWM_PPS = 0b01100; //CCP1 module  
    PPSLock()

    //Configure PWM output using CCP1 / timer2
    PR2 = 0xFF; // 10 bits resolution
    T2CONbits.T2CKPS = PWM_PRESCALER_4; //Prescaler. PWM frequency = Fosc / (1024*Prescaler)
    //T2CONbits.T2OUTPS = 0b0000; //postscaler=1
    CCPTMRSbits.C1TSEL = 0b00; //use timer 2
    CCP1CONbits.CCP1FMT = 1; //Left aligned
    CCP1CONbits.CCP1MODE = 0b1111; //PWM mode
    CCPR1H = 0x10; //Most significant bits
    CCPR1L = 0x00; //Least significant bits
    CCP1CONbits.CCP1EN = 1; //Module enabled
    T2CONbits.TMR2ON = 1; //Start timer 2
}


void pwm_set_dutycycle(uint16_t dutycycle)
{
    dutycycle = dutycycle & 0b1111111111;
    CCPR1H = dutycycle>>2; //Most significant bits
    CCPR1L = (dutycycle&0b11)<<6; //Least significant bits
}

