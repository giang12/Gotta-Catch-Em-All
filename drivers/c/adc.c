// Copyright (c) 2014, Joe Krachey
// All rights reserved.
//
// Redistribution and use in binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in binary form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "adc.h"
#include "driver_defines.h"

/******************************************************************************
 * Initializes ADC to use Sample Sequencer #2, triggered by the processor,
 * no IRQs
 *****************************************************************************/
bool initialize_adc(  uint32_t adc_base )
{
  ADC0_Type  *myADC;
  uint32_t rcgc_adc_mask;
  uint32_t pr_mask;
  

  // examine the adc_base.  Verify that it is either ADC0 or ADC1
  // Set the rcgc_adc_mask and pr_mask  
  switch (adc_base) 
  {
    case ADC0_BASE :
    {
      
      // ADD CODE
      // set rcgc_adc_mask
      rcgc_adc_mask = SYSCTL_RCGCADC_R0;        
      // ADD CODE
      // Set pr_mask 
      pr_mask = SYSCTL_PRADC_R0;
      break;
    }
    case ADC1_BASE :
    {
      // ADD CODE
      // set rcgc_adc_mask
      rcgc_adc_mask = SYSCTL_RCGCADC_R1;        
      // ADD CODE
      // Set pr_mask 
      pr_mask = SYSCTL_PRADC_R1;
      break;
    }
    
    default:
      return false;
  }
  
  // Turn on the ADC Clock
  SYSCTL->RCGCADC |= rcgc_adc_mask;
  
  // Wait for ADCx to become ready
  while( (pr_mask & SYSCTL->PRADC) != pr_mask){}
    
  // Type Cast adc_base and set it to myADC
  myADC = (ADC0_Type *)adc_base;
   // disable all the sample sequencers
  // corresponding ASENn bit in the ADCACTSS register 
	myADC->ACTSS &= ~(ADC_ACTSS_ASEN0 | ADC_ACTSS_ASEN1| ADC_ACTSS_ASEN2| ADC_ACTSS_ASEN3);
	
  myADC->ISC = 0xFFFFFFFF; //clear interrupt
		
	  // Sequencer 3 is the lowest priority
  myADC->SSPRI = ADC_SSPRI_SS3_4TH | ADC_SSPRI_SS2_3RD | ADC_SSPRI_SS1_2ND | ADC_SSPRI_SS0_1ST;

  // Set all the sample sequencers to be triggered by software.
	myADC->EMUX = ADC_EMUX_EM2_PROCESSOR;	
		
	  // Clear Averaging Bits
  myADC->SAC &= ~ADC_SAC_AVG_M  ;
  
  // Average 64 samples
  myADC->SAC |= ADC_SAC_AVG_8X;	
		
	// Configure SSMUX2 to read the raw ADC values

	myADC->SSMUX2 = 0x10; // Set the Channel [y,x]

  // Enable the interrupts for SS2
	myADC->IM = ADC_IM_MASK2; //enable interrupt
	
	 // Set the end of the sequence and when to generate interrupts
  myADC->SSCTL2 = ADC_SSCTL2_IE1 | ADC_SSCTL2_END1;
  
	// setting non SysTick interrupt top priority
	NVIC_SetPriority(ADC0SS2_IRQn, 0);  
	NVIC_EnableIRQ(ADC0SS2_IRQn);

  myADC->ACTSS |= ADC_ACTSS_ASEN2;  // Enable SS2
	
  return true;
}
