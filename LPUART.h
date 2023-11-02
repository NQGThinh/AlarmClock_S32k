
typedef enum
{
	SIRC,
	FIRC,
	SOSC,
}clock_type;

void LPUART_init(void);
void Clock_init(clock_type clock);
void send_char(char data);
void receive_char(void);
void LPUART1_RxTx_IRQHandler(void);
int check_CompleteReceive(void);
void init_led(void);
void turn_on_led(unsigned int color);
void send_string(char digit[]);

/*----------------------------*/
/*-------Ring buffer-------*/
/*----------------------------*/


#define BUFFER_SIZE 64

typedef struct
{
	unsigned char buffer[BUFFER_SIZE];
	int head;
	int tail;
}ring_buffer;

void ring_buffer_init(void);
int is_empty(ring_buffer* buffer);
int is_full(ring_buffer* buffer);
void enqueue(ring_buffer* buffer, char x);
void dequeue(ring_buffer* buffer, unsigned char* x);
void UART_init(void);
void Uart_Transmit(char string[]);
void Uart_TxMainFunction(void);
void Uart_RxMainFunction(void);

extern unsigned char transmit_state;
extern unsigned char receive_state;



#define BUSY 1
#define IDLE 2
#define EMPTY 3
#define NOTEMPTY 4
