/*
* PWMCustom.c
*
* Created: 2015-10-10 16:06:06
*  Author: Stefan & Prince
*/
#include <asf.h>
#include "PWMCustom.h"
#include "global_variables.h"

void PWMSetup()
{
	pmc_enable_periph_clk(ID_PWM);
	pwm_channel_disable(PWM, PWM_CHANNEL_6);
	pwm_clock_t pwm_clock ={
		.ul_clka = 1000*999,
		.ul_clkb = 0,
		.ul_mck = sysclk_get_cpu_hz()
	};
	pwm_init(PWM, &pwm_clock);

	pwm_channel.alignment = PWM_ALIGN_LEFT;
	pwm_channel.polarity = PWM_LOW;
	pwm_channel.ul_prescaler = PWM_CMR_CPRE_CLKA;
	pwm_channel.ul_duty = 0;
	pwm_channel.ul_period = 999;
	pwm_channel.channel = PWM_CHANNEL_6;
	pwm_channel_init(PWM, &pwm_channel);
	pwm_channel_enable(PWM, PWM_CHANNEL_6);
}

void PWMDutyCycle(int value){
	pwm_channel_update_duty(PWM, &pwm_channel, value);
}

void shieldInit()
{
	ioport_set_pin_dir(PIO_PC21_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIO_PC21_IDX, LOW);
	ioport_set_pin_dir(PIO_PD8_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIO_PD8_IDX, HIGH);
}
