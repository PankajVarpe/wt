#include "LPC17xx.h" 
#define PAT 0xB4
int clock_freq = 4000000;  //used by peripherals to adjust frequency

void SystemInit() {
   //routine should change/ set up clock as required
	 //variable clock_freq should be moified
}
void wait_ms(int t)
{
	   LPC_TIM3->TCR = 1<<1; //reset timer counter
     LPC_TIM3->TCR = 1;    //enable timer counter
     while (LPC_TIM3->TC < t); 	
}
void Init_Wait( ) {
	  	LPC_SC->PCONP   |= 1<< 23;   //enable POWER to TIM3
	    LPC_TIM3->CTCR  = 0;				//timer mode
	    LPC_SC->PCLKSEL1 = 2<< 14;   //Timer clock = half system clk
	    LPC_TIM3->PR   = clock_freq/2/1000 -1;      //for 1ms 
}	
int main ( ) {
    Init_Wait();
    LPC_GPIO1->FIODIR2 = PAT;
    while(1)
	{
		 LPC_GPIO1->FIOSET2 = PAT;  //LEDs ON
     wait_ms(100); 
		 LPC_GPIO1->FIOCLR2 = PAT;  //LEDs OFF
     wait_ms(100);  
	}
}
