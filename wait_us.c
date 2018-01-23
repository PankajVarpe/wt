void wait_us(int t)
{
          LPC_TIM2->TCR = 1<<1; //reset timer counter
          LPC_TIM2->TCR = 1;    //enable timer counter
          while (LPC_TIM2->TC < t); 	
}

void  Init_Wait_us( ) {
      	LPC_SC->PCONP   |= 1<< 22;        //enable POWER to TIM2
	LPC_TIM2->CTCR  = 0;		  //timer mode
	LPC_SC->PCLKSEL1 &= !(3 << 12);   //Timer clock = system clk/4
	LPC_TIM2->PR   = clock_freq/4/1000000 -1;      //for 1us 
}	

int clock_freq = 100000000;  //used by peripherals to adjust frequency
#define FEED LPC_SC->PLL0FEED=0xAA; LPC_SC->PLL0FEED=0x55; 
void SystemInit() {
         LPC_SC->SCS = 1 <<5; 
         while (!(LPC_SC->SCS & (1<<6))); 
         LPC_SC->CLKSRCSEL = 1; 
 // code for the PLL0  
         LPC_SC->PLL0CFG = (1<<16)|24;  //N & M  
         FEED 
         LPC_SC->PLL0CON = 1;  //PLL0 enable 
         FEED 
         LPC_SC->CCLKCFG = 2;  //divide by 3 
         while (!(LPC_SC->PLL0STAT & (1<<26)));  //wait until locked 
         LPC_SC->PLL0CON |= 1<<1;  //PLL0 connect  
         FEED                                    //PLL0 operational 
}
