/******************************************************************************
 *
 * Module: Ultrasonic
 *
 * File Name: ultrasonic.h
 *
 * Description: Header file for the Ultrasonic driver
 *
 * Author: Clara Isaac
 *
 *******************************************************************************/

#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

#include "std_types.h"

/* Ultrasonic HW Port and Pin ID */
#define 	TRIG_PORT 	PORTB_ID
#define 	TRIG_PIN 	PIN5_ID

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/


/*
 * Description:
 * 1. Set the trigger pin as output pin.
 * 2. Write on the trigger pin Logic Low.
 * 3. Initialize ICU with the desired configuration.
 * 4. Set CallBack function of ICU.
 */
void Ultrasonic_init(void);

/*
 * Description:
 * Transmit a pulse of 10 us to the trigger pin.
 */
void Ultrasonic_Trigger(void);

/*
 * Description:
 * 1. Start triggering.
 * 2. Get the distance.
 */
uint16 Ultrasonic_readDistance(void);

/*
 * Description:
 * Callback function of ICU.
 * Get the time taken by pulse at echo pin to leave and return back.
 */
void Ultrasonic_edgeProcessing(void);

#endif /* ULTRASONIC_H_ */
