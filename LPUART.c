#include "reg.h"
#include "LPUART.h"


ring_buffer rx_buffer = {{0}, -1, -1};
ring_buffer tx_buffer = {{0}, -1, -1};

ring_buffer* _rx_buffer = &rx_buffer;
ring_buffer* _tx_buffer = &tx_buffer;
 
unsigned char transmit_state = IDLE;
unsigned char receive_state = EMPTY;
unsigned int length = 0;

void LPUART_init(void)
{
	/* Enable NVIC LPUART1 */
	NVIC->ISER[1] |= (1<<1);
	
	/* Setting Tx/Rx pin */
	PCC->PCCn[PCC_PORTC_INDEX] |= (1<<30); 		/* Enable clock port C */
	PORTC->PCR[6] |= (2<<8);	/* Pin Mux Control: ALT2, RX */
	PORTC->PCR[7] |= (2<<8);	/* Pin Mux Control: ALT2, TX */

	/* Select source UART */
	PCC->PCCn[PCC_LPUART1_INDEX] &= ~(1<<30);
	PCC->PCCn[PCC_LPUART1_INDEX] |= (3<<24);
	PCC->PCCn[PCC_LPUART1_INDEX] |= (1<<30);

	/* Setting baurate */
	LPUART1->BAUD |= 312;		/* SBR */

	/* Setting frame */
	LPUART1->BAUD &= ~(1<<13); 	/* 1 stop bit */
	LPUART1->CTRL &= ~(1<<4); 	/* 8 bit data */
	LPUART1->CTRL &= ~(1<<1);		/* No parity bit */
	
	/* Enable receiver/transmit interupt */
	LPUART1->CTRL |= (1<<21);
	//LPUART1->CTRL |= (1<<23);
	
	/* Enable transmit/receive */
	LPUART1->CTRL |= (1<<18); 	/* Enable receiver */
	LPUART1->CTRL |= (1<<19); 	/* Enable transmiter */
}

//void UART_init(void)
//{
//	transmit_state = IDLE;
//}

void Clock_init(clock_type clock)
{
	if(clock == FIRC)
	{
		while((SCG->FIRCCSR&(1<<23)) > 1){}
		SCG->FIRCCSR =0x01000001;
		SCG->FIRCDIV |= (1<<8);
	}
	else if (clock == SIRC)
	{
		while((SCG->SIRCCSR&(1<<23)) > 1){}
		SCG->SIRCCSR =0x01000001;
		SCG->SIRCDIV |= (1<<8);
	}
}

void LPUART1_RxTx_IRQHandler(void)
{
	Uart_RxMainFunction();
}  

int check_CompleteReceive(void)
{
	if((LPUART1->STAT>>20) & 1) 
	{
		LPUART1->STAT = 0x100000;
		return 1;
	}
	else return 0;
}
/*------------------------------------------------*/
/* ------------ RING BUFFER FUNCTION ------------ */
/*------------------------------------------------*/


void ring_buffer_init(void)
{
	_rx_buffer = &rx_buffer;
	_tx_buffer = &tx_buffer;
}

int is_empty(ring_buffer* buffer)
{
	if((buffer->head == -1) && (buffer->tail == -1)) return 1;
	else return 0;
}

int is_full(ring_buffer* buffer)
{
	if(((buffer->head + 1) % BUFFER_SIZE) == buffer->tail) return 1;
	else return 0;
}

void enqueue(ring_buffer* buffer, char x)
{
	if(is_full(buffer)) return;
	else if(is_empty(buffer))
	{
		buffer->head = 0;
		buffer->tail = 0;
	}
	else 
	{
		buffer->head = (buffer->head + 1) % BUFFER_SIZE;
	}
	buffer->buffer[buffer->head] = x;
}

void dequeue(ring_buffer* buffer, unsigned char* x)
{
//	if(is_empty(buffer)) return;
//	else if((buffer->head == buffer->tail))
//	{
//		*x =  buffer->buffer[buffer->tail];
//		buffer->head = -1;
//		buffer->tail = -1;
//	}
//	else 
	{
		*x =  buffer->buffer[buffer->tail];
		buffer->tail = (buffer->tail +1) % BUFFER_SIZE;
	}
}

/*--------------------------------------*/
/* Save string to software buffer */
/*--------------------------------------*/

void Transmit(char string[])
{
	if( transmit_state == IDLE )
	{
		int i=0;
		while(string[i] != '\0')
		{
			enqueue(_tx_buffer, string[i]);
			i++;
		}
		transmit_state = BUSY;
	}
}

/*--------------------------------------*/
/* Send string to hardware buffer */
/*--------------------------------------*/

void Uart_TxMainFunction(void)
{
	if(transmit_state == BUSY)
	{
		while (((LPUART1->STAT>>23) & 1) == 0)
		{
		}
		if(is_empty(_tx_buffer)) return;
		else if(_tx_buffer->head >= _tx_buffer->tail)
		{
			LPUART1->DATA = _tx_buffer->buffer[_tx_buffer->tail];
			_tx_buffer->tail = (_tx_buffer->tail + 1) % BUFFER_SIZE;
		}
		else if(_tx_buffer->head < _tx_buffer->tail) transmit_state = IDLE;
	}
}


/*--------------------------------------*/
/* Receive data */
/*--------------------------------------*/

void Uart_RxMainFunction(void)
{
	if(is_empty(_rx_buffer))
	{
		_rx_buffer->head = 0;
		_rx_buffer->tail = 0;
	}
	else 
	{
		_rx_buffer->head = (_rx_buffer->head + 1) % BUFFER_SIZE;
	}
	_rx_buffer->buffer[_rx_buffer->head] = LPUART1->DATA;
	if(_rx_buffer->tail <= _rx_buffer->head)
	{
		receive_state = NOTEMPTY;
	}
	else
	{
		receive_state = EMPTY;
	}
}



