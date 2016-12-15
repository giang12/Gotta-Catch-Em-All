#include "utils.h"



//*****************************************************************************
// Busy wait
//*****************************************************************************
void wait(int load)
{
  int i = load;
  while(i >0)
  {
    i--;
  }
}
void DisableInterrupts(void)
{
  __asm {
         CPSID  I
  }
}
void EnableInterrupts(void)
{
  __asm {
	    CPSIE  I
  }
}

void draw_line(uint16_t x0, uint16_t xf, uint16_t y0, uint16_t yf, uint32_t pen_color)
{
		uint32_t x,y;

	for(x = x0; x < xf; x++){
				for(y = y0; y < yf; y++){
						lcd_set_pos(x ,x ,y, y);
						lcd_write_data_u16(pen_color);
				}
			}
}

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
bool debounce_ps_press_up(void)
{
	
  static uint16_t values = 0xFFFF;
	
  values = values << 1;
 
	if(ps2_press_up(ps2_get_y()))
  {
    values |= 0x01;
  }

  if( values == 0xFFC0)
  {
    return true;
  }
  else
  {
    return false;
  }
  
}

bool debounce_ps_press_down(void)
{
	
  static uint16_t values = 0xFFFF;

  values = values << 1;
 
	if(ps2_press_down(ps2_get_y()))
  {
    values |= 0x01;
  }

  if( values == 0xFFC0)
  {
    return true;
  }
  else
  {
    return false;
  }
  
}

bool debounce_ps_press_left(void)
{
	
  static uint16_t values = 0xFFFF;
	
  values = values << 1;
 
	if(ps2_press_left(ps2_get_x()))
  {
    values |= 0x01;
  }

  if( values == 0xFFC0)
  {
    return true;
  }
  else
  {
    return false;
  }
  
}

bool debounce_ps_press_right(void)
{
	
  static uint16_t values = 0xFFFF;

  values = values << 1;
 
	if(ps2_press_right(ps2_get_x()))
  {
    values |= 0x01;
  }

  if( values == 0xFFC0)
  {
    return true;
  }
  else
  {
    return false;
  }
  
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

