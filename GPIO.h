
#define LED_BLUE      (0u)
#define LED_RED     	(15u)
#define LED_GREEN     (16u)
#define BUTTON1       (12u)
#define BUTTON2     	(13u)


void init_led(void);
void init_button(void);
void turn_on_led(unsigned int color);
void turn_off_led(unsigned int color);
void led_program(void);
void GPIO_GetPinValue(volatile unsigned int *port, int pin, unsigned int* ptr);
void change_time(void);
void PORTC_IRQHandler(void);