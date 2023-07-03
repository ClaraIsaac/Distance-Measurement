/******************************************************************************
 *
 * Module: Ultrasonic
 *
 * File Name: ultrasonic.c
 *
 * Description: Source file for the Ultrasonic driver
 *
 * Author: Clara Isaac
 *
 *******************************************************************************/

#include "gpio.h"
#include "icu.h"
#include "ultrasonic.h"
#include <util/delay.h> /* to use delay function */

/*******************************************************************************
 *                       Variables Declarations                                *
 *******************************************************************************/

static uint16 g_timerValue = 0, g_edgeCount = 0, g_distance = 0;

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

/*
 * Description:
 * 1. Set the trigger pin as output pin.
 * 2. Write on the trigger pin Logic Low.
 * 3. Initialize ICU with the desired configuration.
 * 4. Set CallBack function of ICU.
 */
void Ultrasonic_init(void)
{
	/* Create configuration structure for ICU driver */
	Icu_ConfigType Icu_Config = {F_CPU_8,RISING};
	/* Setup Trigger pin as output pin */
	GPIO_setupPinDirection(TRIG_PORT, TRIG_PIN, PIN_OUTPUT);
	/* Write on the trigger pin Logic Low */
	GPIO_writePin(TRIG_PORT, TRIG_PIN, LOGIC_HIGH);
	/* Set ICU Callback function */
	Icu_setCallBack(Ultrasonic_edgeProcessing);
	Icu_init(&Icu_Config);
}

/*
 * Description:
 * Transmit a pulse of 10 us to the trigger pin.
 */
void Ultrasonic_Trigger(void)
{
	/* Generate the pulse */
	GPIO_writePin(TRIG_PORT, TRIG_PIN, LOGIC_HIGH);
	_delay_us(10);
	GPIO_writePin(TRIG_PORT, TRIG_PIN, LOGIC_LOW);
}

/*
 * Description:
 * 1. Start triggering.
 * 2. Get the distance.
 */
uint16 Ultrasonic_readDistance(void)
{
	/* start triggering */
	Ultrasonic_Trigger();
	/*
	 * Sound speed = 346 m/s.
	 * Distance = Speed * Time.
	 *          = (34600 * Time) / 2 cm (divided by two because it is the distance of leaving
	 *                                   and returning back)
	 *          = 0.0174 * Time.
	 */
	g_distance = (uint16)((g_timerValue)*0.0174);
	return g_distance; /* return the distance */
}

/*
 * Description:
 * Callback function of ICU.
 * Get the time taken by pulse at echo pin to leave and return back.
 */
void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount++;
	if (g_edgeCount == 1)
	{
		/* Clear Timer Counter register to start counting from the detected edge (rising edge) */
		Icu_clearTimerValue();
		/* Detect falling edge */
		Icu_setEdgeDetectionType(FALLING);
	}
	else if (g_edgeCount == 2)
	{
		/* Store the timer value */
		g_timerValue = Icu_getInputCaptureValue();
		/* Clear Timer Counter register to start counting from the detected edge (falling edge) */
		Icu_clearTimerValue();
		/* Detect rising edge */
		Icu_setEdgeDetectionType(RISING);
		/* Clear edgeCount to start counting from the detected edge (rising edge)*/
		g_edgeCount = 0;
	}
}
