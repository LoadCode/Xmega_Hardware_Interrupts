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

void InterruptConfig(PORT_t *PORT)
{
	//this function configures a basic interrupt 
	//interrupt is present in PC2
	PORT->PIN2CTRL |= PORT_ISC_FALLING_gc; //Activate interrupt on falling
	PORT->INTCTRL   = PORT_INT0LVL_MED_gc; //Config the priority of interrupt
	PORT->INT0MASK = PIN2_bm;			   //Interrupt0 input on pin 2
	PMIC.CTRL |= PMIC_MEDLVLEN_bm;		   //Set the level of priority on the
	//Programable Multilevel Interrupt Controller
	sei();
}

int main(void)
{
	//code tested on Xmega32A4U
	PORTA.DIR = 0xFF; //port A as output for indication in a led on pin 1
	InterruptConfig(&PORTC); //Cofig interrupt in pin 2 of portc on falling edge
	
    while(1)
    { 
    }
}

ISR(PORTC_INT0_vect) //ISR for the interrupt0 in PORTE
{
	PORTA.OUTTGL = 0x01;
}
