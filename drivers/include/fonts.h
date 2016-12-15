#ifndef __ECE353_HW2_FONTS_H__
#define __ECE353_HW2_FONTS_H__

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "lcd.h"

#define       FONT_HEIGHT     16
#define       FONT_WIDTH      17

/* Font data for Sitka Small 12pt */
extern const uint8_t sitkaSmall_12ptBitmaps[];

/*******************************************************************************
* Function Name: lcd_print_string
********************************************************************************
* Summary: prints out a left justified string to the LCD
* Returns:
*  Nothing
*******************************************************************************/
void lcd_print_string(
    char *msg, 
    int8_t line_num, 
		uint16_t x_offset,
    uint16_t fg_color, 
    uint16_t bg_color
);
    
#endif
