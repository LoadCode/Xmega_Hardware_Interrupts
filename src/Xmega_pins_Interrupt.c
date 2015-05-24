/*
 * Interrupciones_Xmega.c
 *
 * Created: 01/04/2015 09:37:34 a.m.
 *  Author: Julio
 *  web:    blogdelingeniero1.wordpress.com
 */ 

#define F_CPU 2000000UL
#include <avr/io.h>
#include <avr/interrupt.h>

void InterruptConfig(PORT_t *PORT, uint8_t pin, uint8_t pin_bm ,uint8_t mode_gc, uint8_t InterruptNumber)
{
	//this function configures a interrupt (InterruptNumber->0 1) in the 'pin' of the port with direction PORT
	// with the mode 'mode_gc' example: PORT_ISC_FALLING_gc
	*(&(PORT->PIN0CTRL)+pin) |= mode_gc; //Activate interrupt on falling
	PORT->INTCTRL   = PORT_INT0LVL_MED_gc; //Config the priority of interrupt
	*(&(PORT->INT0MASK)+InterruptNumber) = pin_bm; //Interrupt0 or Interrupt1 input on pin 'pin'
	PMIC.CTRL |= PMIC_MEDLVLEN_bm;		   //Set the level of priority on the
	//Programable Multilevel Interrupt Controller
	sei();
}

int main(void)
{
	//code tested on Xmega32A4U
	PORTA.DIR = 0xFF; //port A as output for indication in a led on pin 1
	//Configures interrupt 0 input in pin 2 of the port B in falling edge
	InterruptConfig(&PORTB,pin,PIN2_bm,PORT_ISC_FALLING_gc,0);
    while(1);
}

ISR(PORTC_INT0_vect) //ISR for the interrupt0 in PORTC
{
	PORTA.OUTTGL = 0x0F;
	PORTC.INTFLAGS = PORT_INT0IF_bm; //clears the interrupt 0 flag for debounce case
}
