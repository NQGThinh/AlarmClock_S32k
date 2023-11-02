#include "reg.h"
#include "LPUART.h"
#include "LPSI.h"
#include "Softimer.h"
#include "GPIO.h"




int main(void)
{
	init_led();
	init_button();
	Clock_init(FIRC);
	LPUART_init();
	
	LPSPI_init();
	init_Systick(5000);
	init_softimer();
  	Softtimer_Start(1,10000,CONTINUOS,&count_up);
	Softtimer_Start(2,1000,CONTINUOS,&led_program);
	setup_7led();
	while(1)
	{
		if((receive_state == NOTEMPTY) && (check_CompleteReceive()))
		{
			save();
			if(check_error())
			{
				send_error();
				return 0;
			}
		}
		if(mode == SET || mode==ALARM)
		{ 
			{
				send_to_7led();
			}
		}
		if(mode != NONE)
		{
			Softtimer_MainFunction(1); 				// clock count up
		}
		if(is_time_to_alarm())
		{
			Stop_SoftimerMainFuction(1); 			// clock stop count up
			Softtimer_MainFunction(2);
		}
	}
}





