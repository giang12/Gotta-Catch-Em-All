#ifndef __WIRELESS_DRIVER_H__
#define __WIRELESS_DRIVER_H__


#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "spi_select.h"
#include "wireless.h"
#include "gpio_port.h"



typedef struct {
	uint32_t TOTAL_PACKAGES_SENT;
	uint32_t TOTAL_PACKAGES_DELIVERED;
	uint32_t TOTAL_PACKAGES_DROPPED;
	uint32_t TOTAL_PACKAGES_RECEIVED;
} WIRELESS_INFO;


//expose from wireless peripheral
extern bool wireless_configure_device( 
  uint8_t           *my_id,
  uint8_t           *dest_id
);

bool wireless_init(void);


//*****************************************************************************
// Transmits 4 bytes of data to the remote device.
//*****************************************************************************
wireless_com_status_t 
wireless_send(
  bool      block,
  bool      retry,
  uint32_t   data
  );

//*****************************************************************************
// Receives 4 bytes of data from the remote board.  The user can optionally
// block until data arrives.
//*****************************************************************************
wireless_com_status_t 
wireless_get(
  bool      blockOnEmpty,
  uint32_t  *data
  );



#endif

