#include "interrupts.h"

extern volatile uint16_t PS2_X_DATA;
extern volatile uint16_t PS2_Y_DATA;
extern volatile bool ALERT_NEW_ADC;

extern volatile bool WIRELESS_RX_ALERT;
extern volatile WIRELESS_INFO wireless_info;

extern volatile bool ALERT_10MS;
//*****************************************************************************
// Use Timer0A as a 16-bit count down timer with interrupts. 
// Used to start the analog to digital conversion on ADC0 every 1 milliseconds.
// You will need to use a prescalar to achieve this interrupt rate.
//*****************************************************************************
void TIMER0A_Handler(void)
{
	//printf("TIMER0A_Handler \n\r");
	
  TIMER0->ICR |= TIMER_ICR_TATOCINT;
  
  // Start the ADC Conversion
	ADC0->PSSI |=   ADC_PSSI_SS2;
  
}

//*****************************************************************************
// Use Timer0B as a 16-bit count down timer with interrupts. 
// Used to Indicate 10ms has passed.
// You will need to use a prescalar to achieve this interrupt rate.
//*****************************************************************************
void TIMER0B_Handler(void)
{
	
	//printf("TIMER0B_Handler \n\r");

  TIMER0->ICR |= TIMER_ICR_TBTOCINT;
  // Indicate 10ms has passed

  ALERT_10MS = true;
  
}
//*****************************************************************************
// Timer1A is configured as a 32-bit timer that generates interrupts once every
// 3 seconds. This timer is used to print updated wireless packet information
// to the UART0.
//*****************************************************************************
void TIMER1A_Handler(void){

	//printf("X: %d | Y: %d \n\r", PS2_X_DATA, PS2_Y_DATA);
	
	//printf("TOTAL_PACKAGES_SENT: %d \n\rTOTAL_PACKAGES_DROPPED: %d \n\rTOTAL_PACKAGES_RECEIVED: %d \n\r",
			//	wireless_info.TOTAL_PACKAGES_SENT, wireless_info.TOTAL_PACKAGES_DROPPED, wireless_info.TOTAL_PACKAGES_RECEIVED);
	
	TIMER1->ICR |= TIMER_ICR_TATOCINT;

}

//*****************************************************************************
// Have the watchdog timer HALT the board if data has not been received
// from the remote board in the last 15 seconds.
//*****************************************************************************

void WDT0_Handler(void) {
	printf("Watch dog timed out");
	while(1){};
}


//*****************************************************************************
// ADC0 SS2 ISR
//*****************************************************************************
void ADC0SS2_Handler(void)
{
  // Read from SS2 FIFO
  PS2_X_DATA = ADC0->SSFIFO2 & 0xFFF;    // Read 12-bit data
  PS2_Y_DATA = ADC0->SSFIFO2 & 0xFFF;    // Read 12-bit data
  
  // Clear the interrupt
  ADC0->ISC |= ADC_ISC_IN2;
  
  ALERT_NEW_ADC = true;
}

//*****************************************************************************
// Wireless RX IRQ on
//*****************************************************************************
void GPIOD_Handler(void)
{

	GPIOA_Type  *gpioPort = (GPIOA_Type *) RF_IRQ_GPIO_BASE;
	
	
	WIRELESS_RX_ALERT = true;


	gpioPort->ICR |= RF_IRQ_PIN;
}
