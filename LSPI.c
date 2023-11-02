#include "LPSI.h"
#include "reg.h"
#include "LPUART.h"

unsigned char mode=NONE;


unsigned short ss = 0;
unsigned short mm = 0;
unsigned short hh = 0;
unsigned char number1=0;
unsigned char number2=0;
unsigned char number3=0;
unsigned char number4=0;
unsigned char number5=0;
unsigned char number6=0;
unsigned char number7=0;
unsigned char number8=0;

unsigned short sss = 0;
unsigned short mmm = 0;
unsigned short hhh = 0;
unsigned char number11=0;
unsigned char number22=0;
unsigned char number33=0;
unsigned char number44=0;
unsigned char number55=0;
unsigned char number66=0;
unsigned char number77=0;
unsigned char number88=0;
extern ring_buffer* _rx_buffer;

void LPSPI_init(void)
{
	/* Pin number        | Function
	* ----------------- |------------------
	* PTB14             | LPSPI1_SCK
	* PTB15             | LPSPI1_SIN
	* PTB16			        | LPSPI1_SOUT
	* PTB17			        | LPSPI1_PCS3 */
	
	/* 1. Setting SCK/PCS/SOUT/SIN pin */
	PCC->PCCn[PCC_PORTB_INDEX] |= (1u<<30u);  /* Enable clock for PORTB */
	PORTB->PCR[14] |= (3u<<8u); 							/* Port B14: MUX = ALT3, LPSPI1_SCK */
	PORTB->PCR[15] |= (3u<<8u); 							/* Port B15: MUX = ALT3, LPSPI1_SIN */
	PORTB->PCR[16] |= (3u<<8u); 							/* Port B16: MUX = ALT3, LPSPI1_SOUT */
	PORTB->PCR[17] |= (3u<<8u); 							/* Port B17: MUX = ALT3, LPSPI1_PCS3 */

	/* 2. Select source LPUART  */
	PCC->PCCn[PCC_LPSPI1_INDEX] |= (3<<24u);   /* Select source: FIRCDIV2_CLK = 48MHz */
	PCC->PCCn[PCC_LPSPI1_INDEX] |= (1<<30u);   /* Enable clock for LPURAT */
		
	/* 3. Setting baud rate */
	LPSPI1->CCR |= (4u);      /* SCK Divider: 6-2 = 4 */
	LPSPI1->CCR |= (4u<<24u);
	LPSPI1->CCR |= (4u<<16u);
	
	/* 3.4.5.6 */	
	LPSPI1->TCR = ( (3u<<27u)   					/*3. Set Prescaler Value */  /*4. CPOL =0, CPHA = 0 */ 
								| (15u)        					/*5. Set frame size is 8 bits (FRAMESZ + 1) */
								| (3u<<24u) ); 					/*6. Transfer using PCS3  */
	
	/* 7. Setting Transmit/Receive FIFO */
	LPSPI1->FCR  |= (3u);        				/* Transmit FIFO */
	LPSPI1->CFGR1 |= (1u<<3u);  				/* No Stall if Tx FIFO empty or Rx FIFO full*/
	
	/* 8. Configures LPSPI mode */ 
	LPSPI1->CFGR1 |= (1u) ;       				/* Master mode */
	LPSPI1->CR |= (1u<<3u);      				/* Debug mode */

	/* 9. Enable LPSPI module */
	LPSPI1->CR |= (1u);
}

void LPSPI1_send_char(unsigned short data)
{
	while((LPSPI1->SR & (1u)) == 0 ){}
                                   /* Wait for Tx FIFO available 	*/
  LPSPI1->TDR = data;              /* Transmit data 				*/

}

void LPSPI1_send_string(char*  data_string )  
{  /* Function to Transmit whole string */
	while(*data_string != '\0')  {           /* Send chars one at a time */
		LPSPI1_send_char(*data_string);
		data_string++;
	}
}

void setup_7led(void)
{
	/* intensity*/
	LPSPI1_send_char(0x0A01);
	
	/* scan limit*/
	LPSPI1_send_char(0x0B07);

	/* Normal Operation */
	LPSPI1_send_char(0x0C01);

	 /* Display Test */
	//LPSPI1_send_char(0x0F01);
 
		/* Decode mode */
	LPSPI1_send_char(0x09FF);
	for(int i=0x0100; i<=0x0800; i+=0x0100)
	{
		if(i==0x0300) 
		{
			LPSPI1_send_char(0x030a);
		}
		else if (i==0x0600)
		{
			LPSPI1_send_char(0x060a);
		}
		else
		{
			LPSPI1_send_char(i);
		}
	}
}

void save(void)
{
	dequeue(_rx_buffer,&mode);
	if(mode == SET)
	{
		dequeue(_rx_buffer,&number1);
		dequeue(_rx_buffer,&number2);
		dequeue(_rx_buffer,&number3);
		dequeue(_rx_buffer,&number4);
		dequeue(_rx_buffer,&number5);
		dequeue(_rx_buffer,&number6);
		dequeue(_rx_buffer,&number7);
		dequeue(_rx_buffer,&number8);
		
		hh = (number1-48)*10 + (number2-48);
		mm = (number4-48)*10 + (number5-48);
		ss = (number7-48)*10 + (number8-48);
	}
	else if(mode == ALARM)
	{
		dequeue(_rx_buffer,&number11);
		dequeue(_rx_buffer,&number22);
		dequeue(_rx_buffer,&number33);
		dequeue(_rx_buffer,&number44);
		dequeue(_rx_buffer,&number55);
		dequeue(_rx_buffer,&number66);
		dequeue(_rx_buffer,&number77);
		dequeue(_rx_buffer,&number88);
		
		hhh = (number11-48)*10 + (number22-48);
		mmm = (number44-48)*10 + (number55-48);
		sss = (number77-48)*10 + (number88-48);
	}
	
}

int check_error()
{
	if(hh>=24 || mm>=60 || ss>=60 || hhh>=24 || mmm>=60 || sss>=60)
	{
		return 1;
	}
	else return 0;
}

void send_error(void)
{
	for(int i=0x010a; i<=0x0900; i+=0x0100)
	{
		LPSPI1_send_char(i);
	}
}

int is_time_to_alarm(void)
{
	if((hhh!= 0) && (mmm!=0) && (sss!=0) && (mode==ALARM))
	{
		if((hh>=hhh) && (mm>=mmm) && (ss>=sss))
		{
			return 1;
		}
	}
	return 0;
	
}

void count_up(void)
{
	ss++;
	if(ss>=60)
	{
		ss=0;
		mm++;
		if(mm>=60)
		{
			mm=0;
			hh++;
			if(hh>=24) 
			{
				hh=0;
			}
		}
	}
}

void send_to_7led(void)
{
	/* second */
	LPSPI1_send_char(0x0100+(ss%10));
	LPSPI1_send_char(0x0200+(ss/10));
	/* minute */
	LPSPI1_send_char(0x0400+(mm%10));
	LPSPI1_send_char(0x0500+(mm/10));
	/* hour */
	LPSPI1_send_char(0x0700+(hh%10));
	LPSPI1_send_char(0x0800+(hh/10));
}