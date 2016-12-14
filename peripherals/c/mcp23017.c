#include "mcp23017.h"

static 
i2c_status_t wait_for_write( int32_t  i2c_base)
{
  
  i2c_status_t status;
  
  if( !i2cVerifyBaseAddr(i2c_base) )
  {
    return  I2C_INVALID_BASE;
  }

  // Set the I2C address to be the EEPROM and in Write Mode
  status = i2cSetSlaveAddr(i2c_base, MCP23017_DEV_ID, I2C_WRITE);

  // Poll while the device is busy.  The  MCP24LC32AT will not ACK
  // writing an address while the write has not finished.
  do 
  {
    // The data we send does not matter.  This has been set to 0x00, but could
    // be set to anything
    status = i2cSendByte( i2c_base, 0x00, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);
    
    // Wait for the address to finish transmitting
    while ( I2CMasterBusy(i2c_base)) {};
    
    // If the address was not ACKed, try again.
  } while (I2CMasterAdrAck(i2c_base) == false);

  return  status;
}

bool io_expander_init(uint32_t  i2c_base)
{
	i2c_status_t status;
	//set LED TO BE OUTPUT
	status = io_expander_byte_write(i2c_base, IODIRA, 0x00);
	if(status != I2C_OK) return false;
	
	/*
	status = io_expander_byte_write(i2c_base, 0x0B, 0x6C);
	if(status != I2C_OK) return false;
	*/
	
	// Set directional BTNS to be input
	status = io_expander_byte_write(i2c_base, IODIRB, 0xFF);
	if(status != I2C_OK) return false;
	
	//set portb pins pullup
	status = io_expander_byte_write(i2c_base, 0x0D, 0xFF);
	if(status != I2C_OK) return false;
	

	//TO BE REMOVED
	io_expander_set_pin(i2c_base,LED_GPIO_BASE,LED0_PIN);
	io_expander_set_pin(i2c_base,LED_GPIO_BASE,LED2_PIN);
	io_expander_set_pin(i2c_base,LED_GPIO_BASE,LED4_PIN);
	io_expander_set_pin(i2c_base,LED_GPIO_BASE,LED6_PIN);



	return true;
}



i2c_status_t io_expander_byte_write
( 
  uint32_t  i2c_base,
  uint16_t  address,
  uint8_t   data
)
{
  i2c_status_t status;
  
  // Before doing anything, make sure the I2C device is idle
  while ( I2CMasterBusy(i2c_base)) {};

  //==============================================================
  // Set the I2C address to be the EEPROM
	// ADD CODE
  //==============================================================
	status = i2cSetSlaveAddr(i2c_base, MCP23017_DEV_ID, I2C_WRITE);
	if ( status != I2C_OK )return status;

  // If the EEPROM is still writing the last byte written, wait
  wait_for_write(i2c_base);
  
  //==============================================================
  // Send the Upper byte of the address
	// ADD CODE	
	// NO NEED sice mcp23017 only has 1 byte addressable
  //==============================================================
	//	status = i2cSendByte( i2c_base, (uint8_t)(address >> 8) , I2C_MCS_START | I2C_MCS_RUN);
	//if ( status != I2C_OK )return status;
  //==============================================================
  // Send the Lower byte of the address
	// ADD CODE
  //==============================================================
  status = i2cSendByte( i2c_base, (uint8_t)(address) , I2C_MCS_START | I2C_MCS_RUN);
	if ( status != I2C_OK )return status;

  //==============================================================
  // Send the Byte of data to write
	// ADD CODE
  //==============================================================
  status = i2cSendByte( i2c_base, data, I2C_MCS_RUN | I2C_MCS_STOP);

  return status;
}


i2c_status_t io_expander_byte_read
( 
  uint32_t  i2c_base,
  uint16_t  address,
  uint8_t   *data
)
{
  i2c_status_t status;
  
  // Before doing anything, make sure the I2C device is idle
  while ( I2CMasterBusy(i2c_base)) {};

  // If the EEPROM is still writing the last byte written, wait
  wait_for_write(i2c_base);

  //==============================================================
  // Set the I2C slave address to be the EEPROM and in Write Mode
	// ADD CODE
  //==============================================================
	status = i2cSetSlaveAddr(i2c_base, MCP23017_DEV_ID, I2C_WRITE);
	if ( status != I2C_OK )return status;

  //==============================================================
  // Send the Upper byte of the address
	// ADD CODE
	// NO NEED sice mcp23017 only has 1 byte addressable
  //==============================================================
  // status = i2cSendByte( i2c_base, (uint8_t)(address >> 8) , I2C_MCS_START | I2C_MCS_RUN);
	// if ( status != I2C_OK )return status;

  //==============================================================
  // Send the Lower byte of the address
	// ADD CODE
  //==============================================================
  status = i2cSendByte( i2c_base, (uint8_t)(address) , I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);
	if ( status != I2C_OK )return status;

  //==============================================================
  // Set the I2C slave address to be the EEPROM and in Read Mode
	// ADD CODE
  //==============================================================
	status = i2cSetSlaveAddr(i2c_base, MCP23017_DEV_ID, I2C_READ);
	if ( status != I2C_OK )return status;

  //==============================================================
  // Read the data returned by the EEPROM
	// ADD CODE
  //==============================================================
  status = i2cGetByte( i2c_base, data, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);

  return status;
}


bool  io_expander_set_pin(uint32_t  i2c_base, uint16_t  address, uint8_t pin_number)
{
	uint8_t data;
	
	i2c_status_t status;
	status = io_expander_byte_read(i2c_base, address, &data);
	if ( status != I2C_OK )return status;

  data |= 0x01 << pin_number;
	
	status = io_expander_byte_write(i2c_base, address, data);
	if ( status != I2C_OK )return status;

	return true;
}

//*****************************************************************************
// Clears a given GPIO pin to 0.  All other pins retain their value
//
// Paramters
//    pin_number  The pin number of port F to turn off
//              
//
//*****************************************************************************
bool  io_expander_clear_pin(uint32_t  i2c_base, uint16_t  address, uint8_t pin_number)
{	
	uint8_t data;
	
	i2c_status_t status;
	status = io_expander_byte_read(i2c_base, address, &data);
	if ( status != I2C_OK )return status;

  data &= ~(0x01 << pin_number);
	
	status = io_expander_byte_write(i2c_base, address, data);
	if ( status != I2C_OK )return status;

	return true;
}

//*****************************************************************************
// Reads a the current value of a pin.
//
// Paramters
//    pin_number  The pin number to be read
//              
// Returns
//    true if the value is a 1 
//    false if the value is a 0
//*****************************************************************************
bool  io_expander_read_pin(uint32_t  i2c_base, uint16_t  address, uint8_t pin_number)
{
	uint8_t   data;
	i2c_status_t status;
	
	status = io_expander_byte_read(i2c_base, address, &data);
	
	
	if ( status != I2C_OK )return status;

	
	if((data & (0x01 << pin_number)) >> pin_number)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}
