#include "ws2812b.h"

void ws2812b_rotate( WS2812B_t *base, uint8_t num_leds)
{
  WS2812B_t save = *(base+num_leds-1);
  int i = 0; 
  for(i = 0; i < num_leds; i++)
  {
	  WS2812B_t tmp = *(base+i);
    *(base+i) = save; 
	  save = tmp;
	
  }
}

void ws2812b_pulse( WS2812B_t *base, uint8_t num_leds)
{
  static int direction = 1; 
  int i = 0; 
  for(i = 0; i < num_leds; i++)
  {
    if(direction == 1 && (base + i)->red < 0xFF)
	{
	  (base+i)->red++;
	}
	else if(direction == 1 && (base + i)->red == 0xFF)
	{
	  direction = 0; 
	  (base + i)->red--;
	}
    else if(direction == 0 && (base + i)->red > 0x00)
	{
	  (base+i)->red--;
	}
	else if(direction == 0 && (base + i)->red == 0x00)
	{
	  direction = 1; 
	  (base + i)->red++;
	}
	else
	{}
  }


}

