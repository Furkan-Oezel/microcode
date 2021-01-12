#include "TI/TM4C123.h"
#include "init.h"
#include "nicknames.h"

void SysTick_Handler(void)
{
	toggle(RED);
	toggle(BLUE);
}

void IRQ30_Handler(void)
{
	if(GPIOF->MIS & (1 << LEFT_SW))
	{
		GPIOF->ICR |= (1 << LEFT_SW);
		turn_off(RED);
	}

	if(GPIOF->MIS & (1 << RIGHT_SW))
	{
		GPIOF->ICR |= (1 << RIGHT_SW);
		turn_off(BLUE);
	}
}

int main()
{
	init_gpiof();
	init_systick(1);	//10x the desired time
	init_interrupt(LEFT_SW, LEVEL_SENSITIVE);
	init_interrupt(RIGHT_SW, LEVEL_SENSITIVE);

	while (1)
	{

	}
}
