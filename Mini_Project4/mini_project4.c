/******************************************************************************
 *
 * File Name: mini_project4.c
 *
 * Description: Read distance form Ultrasonic and display it on LCD
 *
 * Author: Clara Isaac
 *
 * Date: 14/10/2022
 *
 *******************************************************************************/

#include "gpio.h"
#include "std_types.h"
#include "common_macros.h"
#include "ultrasonic.h"
#include "lcd.h"
#include <avr/io.h> /* To use SREG register */

int main(void)
{
	/* Variable to store the distance */
	uint16 a_distance = 0;
	/* Enabling Global Interrupt Register */
	SREG |= (1<<7);
	/* LCD initialization */
	LCD_init();
	/* Ultrasonic initialization */
	Ultrasonic_init();

	LCD_displayString("Distance=     cm");
	while(1)
	{
		/* Get the distance */
		a_distance = Ultrasonic_readDistance();
		/* Display it on LCD */
		LCD_moveCursor(0, 10);
		LCD_intgerToString(a_distance);
		LCD_displayCharacter(' ');
	}
}
