#include "wireless_driver.h"

volatile WIRELESS_INFO wireless_info = {0};

volatile bool WIRELESS_RX_ALERT = false; //FLAG ON NEW DATA

bool rx_enable_interrupt(void)
{
	gpio_enable_port(RF_IRQ_GPIO_BASE);
	gpio_config_digital_enable(RF_IRQ_GPIO_BASE, RF_IRQ_PIN);
	gpio_config_enable_input(RF_IRQ_GPIO_BASE, RF_IRQ_PIN);
	gpio_config_enable_pullup(RF_IRQ_GPIO_BASE, RF_IRQ_PIN);

	gpio_config_falling_edge_irq(RF_IRQ_GPIO_BASE, RF_IRQ_PIN);
	
	NVIC_SetPriority(GPIOD_IRQn, 0);
	NVIC_EnableIRQ(GPIOD_IRQn);
	
	return true;
}

bool wireless_init(void)
{
  if(!spi_select_init()) return false; //SPI CHIP SELECT INIT
	
	spi_select(NORDIC); //NORDIC FOR WIRELESS COMMUNICATION

	wireless_initialize(); //CONFIG  SPI: CLK MISO MOSI lines between GPIOA and SSI0
	
	
	if(!rx_enable_interrupt()) return false;
	
	return true;
}


wireless_com_status_t 
wireless_send(
  bool      blockOnFull,
  bool      retry,
  uint32_t   data
){
	 
	 wireless_com_status_t status;
	
	status = wireless_send_32(blockOnFull, retry, data);
	
	if(status == NRF24L01_ERR) return status; //error sending, no increment count
	
	wireless_info.TOTAL_PACKAGES_SENT++;
	
	status == NRF24L01_TX_SUCCESS ? wireless_info.TOTAL_PACKAGES_DELIVERED++ : wireless_info.TOTAL_PACKAGES_DROPPED++;
	
	return status;
}


wireless_com_status_t 
wireless_get(
  bool      blockOnEmpty,
  uint32_t  *data
){
	wireless_com_status_t status;
	
	status = wireless_get_32(blockOnEmpty, data);
	
	if(status != NRF24L01_RX_SUCCESS) return status;
	
	wireless_info.TOTAL_PACKAGES_RECEIVED++;
	
	return status;
	
}

