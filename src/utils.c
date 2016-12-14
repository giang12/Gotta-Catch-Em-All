#include "utils.h"


bool sw_is_pressed(uint8_t pin)
{
	
  static uint16_t sw_values[5] = {0xFFFF};

	if(pin != SW1_PIN
		&& pin!= SW2_PIN)
	{
		return false;
	}
	
  sw_values[pin] = sw_values[pin] << 1;
  
  if( lp_io_read_pin(pin))
  {
    sw_values[pin] |= 0x01;
  }

  if( sw_values[pin] == 0xFFC0)
  {
    return true;
  }
  else
  {
    return false;
  }
  
}

bool btn_is_pressed(uint8_t pin){
	static uint16_t btn_values[4] = {0xFFFF};

	if(	pin != BTN_UP_PIN && 
			pin != BTN_DOWN_PIN &&
			pin != BTN_LEFT_PIN &&
			pin != BTN_RIGHT_PIN)
	{
		return false;
	}

	btn_values[pin] = btn_values[pin] << 1;
	
	if( io_expander_read_pin(IO_EXPANDER_I2C_BASE, BTN_GPIO_BASE, pin))
  {
    	btn_values[pin] |= 0x01;
  }

  if( 	btn_values[pin] == 0xFFC0)
  {
    return true;
  }
  else
  {
    return false;
  }
	//return !io_expander_read_pin(IO_EXPANDER_I2C_BASE, BTN_GPIO_BASE, pin); //1->not pressed, 0->pressed pullup
}

void eeprom_write_team_info(char  me[], char  you[], char  groupNum[])
{
	uint16_t addr;
	uint16_t count;
	printf("Writing %s \n\r %s \n\r %s \n\r", me, you, groupNum);
	//writing partner 1
  for(addr = 0, count=0; addr < 80; addr++,count++)
	{
		eeprom_byte_write(I2C1_BASE, addr, (unsigned char) me[count]);
	}

	//writing partner 2
	for(addr = 80, count = 0; addr < 80 + 80; addr++, count++)
	{
		eeprom_byte_write(I2C1_BASE, addr, (unsigned char) you[count]);
	}
	
	//writing group #
	for(addr = 160, count = 0; addr < 160 + 80; addr++, count++)
	{
		eeprom_byte_write(I2C1_BASE, addr, (unsigned char) groupNum[count]);
	}
}

void eeprom_read_team_info(void){
	char me [80];
	char you [80];
	char groupNum [80];
	uint16_t addr;
	uint16_t count;
	uint8_t temp;
	
	//reading partner 1
	addr = 0;
	count = 0;
	eeprom_byte_read(I2C1_BASE, addr, &temp);

	while(count < 80){
			me[count++] = (unsigned char) temp;
			addr++;
			eeprom_byte_read(I2C1_BASE, addr, &temp);
	}
	//reading partner 2
	addr = 80;
	count = 0;
	eeprom_byte_read(I2C1_BASE, addr, &temp);

	while(count < 80){
			you[count++] = (unsigned char) temp;
			addr++;
			eeprom_byte_read(I2C1_BASE, addr, &temp);
	}
	//reading team #
	addr = 160;
	count = 0;
	eeprom_byte_read(I2C1_BASE, addr, &temp);

	while(count < 80){
			groupNum[count++] = (unsigned char) temp;
			addr++;
			eeprom_byte_read(I2C1_BASE, addr, &temp);
	}
	
	
	printf("%s \n\r", me);
	printf("%s \n\r", you);
	printf("%s \n\r", groupNum);

}

