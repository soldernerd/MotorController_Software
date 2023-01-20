/* 
 * File:   pwm.h
 * Author: Luke
 *
 * Created on 12. März 2017, 21:08
 */

#ifndef PWM_H
#define	PWM_H

typedef enum
{
    PWM_PRESCALER_1 = 0b00,
    PWM_PRESCALER_4 = 0b01,
    PWM_PRESCALER_16 = 0b10,
    PWM_PRESCALER_64 = 0b11
} PwmPrescaler_t;

void pwm_init(void);
void pwm_set_dutycycle(uint16_t dutycycle);


#endif	/* PWM_H */

