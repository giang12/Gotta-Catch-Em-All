#ifndef __TIMERS_H__
#define __TIMERS_H__

#include <stdbool.h>
#include <stdint.h>

#include "driver_defines.h"

#define one_sec_ticks 50000000
#define WATCHDOG_TICKS 15*one_sec_ticks; //15s
#define TIMER1_TICKS 3*one_sec_ticks; //3s

#define TIMER0A_TICKS 10000; //.2ms
#define TIMER0A_PRESCALAR 5 ; //1ms

#define TIMER0B_TICKS 10000; //.2ms
#define TIMER0B_PRESCALAR 50 ; //10ms

static volatile bool ALERT_10MS;

void timer0_init(void);

void timer1_init(void);

void watchdog_init(void);

void pet_wd(void);

#endif
