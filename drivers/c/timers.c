#include "timers.h"

volatile bool ALERT_10MS = false;

//*****************************************************************************
// Verifies that the base address is a valid GPIO base address
//*****************************************************************************
static bool verify_base_addr(uint32_t base_addr)
{
   switch( base_addr )
   {
     case TIMER0_BASE:
     case TIMER1_BASE:
     case TIMER2_BASE:
     case TIMER3_BASE:
     case TIMER4_BASE:
     case TIMER5_BASE:
     {
       return true;
     }
     default:
     {
       return false;
     }
   }
}

//*****************************************************************************
// Returns the RCGC and PR masks for a given TIMER base address
//*****************************************************************************
static bool get_clock_masks(uint32_t base_addr, uint32_t *timer_rcgc_mask, uint32_t *timer_pr_mask)
{
  // Set the timer_rcgc_mask and timer_pr_mask using the appropriate
  // #defines in ../include/sysctrl.h
  switch(base_addr)
  {
    case TIMER0_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R0;
      *timer_pr_mask = SYSCTL_PRTIMER_R0;
      break;
    }
    case TIMER1_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R1;
      *timer_pr_mask = SYSCTL_PRTIMER_R1;
      break;
    }
    case TIMER2_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R2;
      *timer_pr_mask = SYSCTL_PRTIMER_R2;
      break;
    }
    case TIMER3_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R3;
      *timer_pr_mask = SYSCTL_PRTIMER_R3;
      break;
    }
    case TIMER4_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R4;
      *timer_pr_mask = SYSCTL_PRTIMER_R4;
      break;
    }
    case TIMER5_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R5;
      *timer_pr_mask = SYSCTL_PRTIMER_R5;
      break;
    }
    default:
    {
      return false;
    }
  }
  return true;
}

//*****************************************************************************

//*****************************************************************************
void timer0_init(void)
{
	uint32_t base_addr = TIMER0_BASE;
  uint32_t timer_rcgc_mask;
  uint32_t timer_pr_mask;
  TIMER0_Type *gp_timer;

  
  // get the correct RCGC and PR masks for the base address
  get_clock_masks(base_addr, &timer_rcgc_mask, &timer_pr_mask);
  
  // Turn on the clock for the timer
  SYSCTL->RCGCTIMER |= timer_rcgc_mask;

  // Wait for the timer to turn on
  while( (SYSCTL->PRTIMER & timer_pr_mask) == 0) {};
  
  // Type cast the base address to a TIMER0_Type struct
  gp_timer = (TIMER0_Type *)base_addr;
    

  gp_timer->CTL &= ~(TIMER_CTL_TAEN | TIMER_CTL_TBEN); //Disable both the A and B timers 
		
  gp_timer->CFG = TIMER_CFG_16_BIT; //16 bits mode
		
  gp_timer->TAMR &= ~(TIMER_TAMR_TAMR_M); //clear mode
  gp_timer->TBMR &= ~(TIMER_TBMR_TBMR_M); //clear mode
		
		//periodic
  gp_timer->TAMR |= TIMER_TAMR_TAMR_PERIOD;
  gp_timer->TBMR |= TIMER_TBMR_TBMR_PERIOD;
	
			//Counting down
	gp_timer->TAMR &= ~(TIMER_TAMR_TACDIR);
  gp_timer->TBMR &= ~(TIMER_TBMR_TBCDIR);
		
		//set interrupt
	gp_timer->IMR |= TIMER_IMR_TATOIM;
	gp_timer->IMR |= TIMER_IMR_TBTOIM;
		
	//set ticks and prescalar
	gp_timer->TAPR 	= TIMER0A_PRESCALAR;
	gp_timer->TAILR = TIMER0A_TICKS;
	
	gp_timer->TBPR 	= TIMER0B_PRESCALAR;
	gp_timer->TBILR	= TIMER0B_TICKS;
	//clear status flag
	gp_timer->ICR |= (TIMER_ICR_TATOCINT | TIMER_ICR_CAMCINT | TIMER_ICR_CAECINT | TIMER_ICR_RTCCINT | TIMER_ICR_TAMCINT);
	
	NVIC_SetPriority(TIMER0A_IRQn, 2);
	NVIC_EnableIRQ(TIMER0A_IRQn);
		
  NVIC_SetPriority(TIMER0B_IRQn, 1);
	NVIC_EnableIRQ(TIMER0B_IRQn);
	
	gp_timer->CTL |= TIMER_CTL_TAEN; //enable 0A
 	gp_timer->CTL |= TIMER_CTL_TBEN; //enable 0B

}

void timer1_init(void){
	uint32_t base_addr = TIMER1_BASE;
  uint32_t timer_rcgc_mask;
  uint32_t timer_pr_mask;
  TIMER0_Type *gp_timer;

  
  // get the correct RCGC and PR masks for the base address
  get_clock_masks(base_addr, &timer_rcgc_mask, &timer_pr_mask);
  
  // Turn on the clock for the timer
  SYSCTL->RCGCTIMER |= timer_rcgc_mask;

  // Wait for the timer to turn on
  while( (SYSCTL->PRTIMER & timer_pr_mask) == 0) {};
  
  // Type cast the base address to a TIMER0_Type struct
  gp_timer = (TIMER0_Type *)base_addr;
    

  gp_timer->CTL &= ~(TIMER_CTL_TAEN | TIMER_CTL_TBEN); //Disable both the A and B timers 
		
  gp_timer->CFG = TIMER_CFG_32_BIT_TIMER; //32 bits mode
	
	gp_timer->TAMR |= TIMER_TAMR_TAMR_PERIOD;
		
			//Counting down
	gp_timer->TAMR &= ~(TIMER_TAMR_TACDIR);
		
		//set interrupt
	gp_timer->IMR |= TIMER_IMR_TATOIM;
		
		//set ticks and prescalar
	gp_timer->TAILR = TIMER1_TICKS;
	
	//clear status flag
	gp_timer->ICR |= (TIMER_ICR_TATOCINT | TIMER_ICR_CAMCINT | TIMER_ICR_CAECINT | TIMER_ICR_RTCCINT | TIMER_ICR_TAMCINT);
	
	NVIC_SetPriority(TIMER1A_IRQn, 2);
	NVIC_EnableIRQ(TIMER1A_IRQn);
		
	gp_timer->CTL |= TIMER_CTL_TAEN; //enable 1A

}

void watchdog_init(void){
	
	WATCHDOG0_Type	*wd = (WATCHDOG0_Type *)WATCHDOG0_BASE;
	
	uint32_t wd_rcgc_mask = SYSCTL_RCGCWD_R0;
  uint32_t wd_pr_mask = SYSCTL_PRWD_R0;
	
	// Turn on the clock for the timer
  SYSCTL->RCGCWD  |= wd_rcgc_mask;

  // Wait for the timer to turn on
  while( (SYSCTL->RCGCWD  & wd_pr_mask) == 0) {};
		
	//wait for peripheral to become active
	wd->CTL &= 0x3;
		
	wd->LOAD = WATCHDOG_TICKS; 
		
	wd->CTL |= 0x3;
	NVIC_SetPriority(WATCHDOG0_IRQn, 0);
	NVIC_EnableIRQ(WATCHDOG0_IRQn);	
}

void pet_wd(void){
	
	WATCHDOG0->ICR = 0;
}

