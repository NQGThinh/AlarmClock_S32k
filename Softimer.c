#include "reg.h"
#include "Softimer.h"

void init_Systick(unsigned int value)
{
	SYST->SYST_CSR = 0;
	SYST->SYST_CVR = 0;
	SYST->SYST_RVR = value;
	SYST->SYST_CSR |= 0xff;
}

static volatile unsigned int TimeCountMs = 0;
void SysTick_Handler(void)
{
    TimeCountMs++;
}

/*-------------------*/
/* Software timer */
/*-------------------*/

typedef struct
{
	unsigned flag;
	unsigned int TimeoutValue;
	unsigned int CurrentTime;
	unsigned int Mode;
	callback event;
}Softtimer;

static Softtimer Timer[ID_MAX]; 

void init_softimer(void)
{
	for(int i=0; i<ID_MAX; i++)
	{
		Timer[i].flag = 0;
		Timer[i].TimeoutValue = 0;
		Timer[i].CurrentTime = 0;
		Timer[i].Mode = 0;
	}
}

void Softtimer_Start(unsigned int ID,
											unsigned int TimeoutValue,
												unsigned int Mode,
													callback event)
{
	Timer[ID].flag = 1;
	Timer[ID].TimeoutValue = TimeoutValue;
	Timer[ID].CurrentTime = TimeCountMs;
	Timer[ID].Mode = Mode;
	Timer[ID].event = event;
}

void Softtimer_Stop(unsigned ID)
{
	Timer[ID].TimeoutValue = 0;
}

void Softtimer_MainFunction(unsigned ID)
{
	if (Timer[ID].flag==1 && TimeCountMs >= Timer[ID].CurrentTime + Timer[ID].TimeoutValue)
	{
		Timer[ID].event();
		if(Timer[ID].Mode == ONSHOT)
		{
			Timer[ID].TimeoutValue = 0;
			Timer[ID].flag = 0;
		}
		else if(Timer[ID].Mode == CONTINUOS)
		{
			Timer[ID].CurrentTime = TimeCountMs;
		}
	}
}

void Stop_SoftimerMainFuction(unsigned ID)
{
	Timer[ID].flag = 0;
}