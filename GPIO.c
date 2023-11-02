#include "GPIO.h"
#include "reg.h"
#include "LSPI.h"

volatile unsigned int led_state = LED_GREEN;
unsigned int button1 = 0;
unsigned int button2 = 0;
extern unsigned short ss;
extern unsigned short mm;
extern unsigned short hh;
extern void send_to_7led(void);

void init_led(void)
{
	/* Enable clock port */
	PCC->PCCn[PCC_PORTD_INDEX] |= (1<<30);

	/* Set pin as GPIO function */
	PORTD->PCR[LED_BLUE] |= (1<<8);
	PORTD->PCR[LED_RED] |= (1<<8);
	PORTD->PCR[LED_GREEN] |= (1<<8);

	/* Set pin as GPIO output */
	GPIOD->PDDR = 0xffffffff;
	GPIOD->PDOR |= (1<<LED_BLUE) | (1<<LED_RED) | (1<<LED_GREEN);
}

void init_button(void)
{
	/*--------------------*/
	/* BUTTON */
	/*--------------------*/

	/* Set clock for port C */
	PCC->PCCn[PCC_PORTC_INDEX] |= (1<<30);
	
	/* Set pins as GPIO function */
	PORTC->PCR[BUTTON1] |= (1<<8);
	PORTC->PCR[BUTTON2] |= (1<<8);
	
	/* Disable pullup pulldown */
	PORTC->PCR[BUTTON1] &= ~(1<<1);
	PORTC->PCR[BUTTON2] &= ~(1<<1);
	
	/* Set pin as input pin */
	GPIOC->PDDR &= ~(1<<BUTTON1);
	GPIOC->PDDR &= ~(1<<BUTTON2);
	
	/* Set interupt type */
	PORTC->PCR[BUTTON1] |= (10<<16); /* falling edge */
	PORTC->PCR[BUTTON2] |= (10<<16);
	
	/* Enable NVIC for Port C */
	NVIC->ISER[1] |= (1u<<29u);
}

void turn_on_led(unsigned int color)
{
	GPIOD->PDOR &= ~(1<<color);
}

void turn_off_led(unsigned int color)
{
	GPIOD->PDOR |= (1<<color);
}

void GPIO_GetPinValue(volatile unsigned int *port, int pin, unsigned int* ptr)
{
	*port = *port >> pin;
	*ptr = *port & 1;
}

void led_program(void)
{
	if(led_state == LED_GREEN)
	{
		led_state = LED_RED;
		turn_on_led(LED_GREEN);
		turn_off_led(LED_RED);
		turn_off_led(LED_BLUE);
	}
	else if(led_state == LED_RED)
	{
		led_state = LED_BLUE;
		turn_on_led(LED_RED);
		turn_off_led(LED_BLUE);
		turn_off_led(LED_GREEN);
	}
	else if(led_state == LED_BLUE)
	{
		led_state = LED_GREEN;
		turn_on_led(LED_BLUE);
		turn_off_led(LED_RED);
		turn_off_led(LED_GREEN);
	}
}

//void change_time(void)
//{
//	GPIO_GetPinValue(&GPIOC->PDIR,BUTTON1,&button1);
//	GPIO_GetPinValue(&GPIOC->PDIR,BUTTON2,&button2);
//	if(button1 == 1)
//	{
//		hh--;
//		button1 = 0;
//	}
//	if(button2 == 1)
//	{
//		mm--;
//		button2 = 0;
//	}
//}

void PORTC_IRQHandler(void)
{
	if( PORTC->PCR[BUTTON1] & (1u<<24u) ){   /* Check interrupt flag of BUTTON1 */
		hh--;
		PORTC->PCR[BUTTON1] |= (1u<<24u);
	}
	if( PORTC->PCR[BUTTON2] & (1u<<24u) ){   /* Check interrupt flag of BUTTON1 */
		mm--;
		PORTC->PCR[BUTTON2] |= (1u<<24u);
	}
}