
typedef void(*callback)(void);

void Systick(unsigned int ms);
void init_Systick(unsigned int value);
void init_softimer(void);
void Softtimer_Start(unsigned int ID,
											unsigned int TimeoutValue,
												unsigned int Mode,
													callback event);
void Softtimer_Stop(unsigned ID);
void Softtimer_MainFunction(unsigned ID);
void Stop_SoftimerMainFuction(unsigned ID);
												
#define ID_MAX 4
#define ONSHOT 1
#define CONTINUOS 2