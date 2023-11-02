

void LPSPI_init(void);
void LPSPI1_send_char(unsigned short data);
void LPSPI1_send_string(char*  data_string );
void setup_7led(void);
int check_error();
void send_error(void);
void send_to_7led(void);
void save(void);
void count_up(void);
int is_time_to_alarm(void);

extern unsigned char mode;

#define NONE 0
#define ALARM 'a'
#define SET 's'

