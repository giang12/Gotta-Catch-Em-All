# Gotta-Catch-Em-All

# ADC0 - PS2 Joystick
Configure ADC0 to convert the X and Y directions of the PS2 Joystick using Sample Sequencer #2. ADC0 conversion are trigged using Timer0A interrupts.

# ADC0 - Interrupts
ADC0, Sample Sequencer #2 should be configured to generate an interrupt after sequence has completed.

# ADC0 - Timer0A
ADC0 conversions will be triggered using Timer0A interrupts at a rate of 1000 times per second.

# UART0
Used for serial debug. 115200 baud with interrupts

# LCD - Graphics
Display non-trivial graphic images. Graphics must be something other than graphics provided in class.

# LCD - Animate
Animate a non-trivial motion of an image

# LCD Capacitive Touch Used in Game
Use the capacitive touch abilities of the LCD to support user input.

# Wireless Communication - Tx and Rx
Transmit and receive on both devices

# Wireless - Dropped/Sent Packets Total
Keep a running total of packets transmitted and received.

# Wireless - External Interrupts
Utilize external interrupt pin to detect received data

# Timers - Timer0A
Use Timer0A as a 16-bit count down timer with interrupts. Used to start the analog to digital conversion on ADC0 every 1 milliseconds. You will need to use a prescalar to achieve this interrupt rate.

# Timers - Timer1A Interrupts
Timer1A is configured as a 32-bit timer that generates interrupts once every 3 seconds. This timer is used to print updated wireless packet information to the UART0.

# Timers - Watchdog Timer
Have the watchdog timer HALT the board if data has not been received from the remote board in the last 15 seconds.

# EEPROM - Read Board Data
The following information should be read from the EEPROM and printed to UART0 when the MCU is reset. All three fields are terminated with a NULL character. Reserve 80 characters for each field.

-	Student 1: Your name 
-	Student 2: Your partner’s name
-	Team Number: xx 

# EEPROM - Write
When the SW2 pushbutton is pressed down, the application should write the following information to the EEPROM. 

-	Student 1: Your name 
-	Student 2: Your partner’s name
-	Team Number: xx 

# EEPROM - Game Data
Read/Write stateful data such as a high score to the EEPROM

# Directional Pushbuttons and Red LEDs
Use the four directional push buttons and 8 RED LEDs that are connected to the I2C I/O Expander
