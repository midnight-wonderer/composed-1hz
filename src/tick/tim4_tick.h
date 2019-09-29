// Copyright (c) 2018 Sarun Rattanasiri
// under the MIT License https://opensource.org/licenses/MIT

#ifndef __TIM4_TICK_H
#define __TIM4_TICK_H

#include <stdint.h>
#include "stm8s_itc.h"
#include "stm8s_tim4.h"

typedef struct _tim4_tick__config {
  TIM4_Prescaler_TypeDef prescaler;
  uint8_t reload_value;
  void (*tick)();
} Tim4Tick_Config;

// example config parameters for 2 MHz PSC
// prescaler = TIM4_PRESCALER_16
// reload_value = (0x100 - 125)

void tim4_tick__setup(Tim4Tick_Config* config);
INTERRUPT_HANDLER(tim4_tick__interrupt_routine, ITC_IRQ_TIM4_OVF);

#endif
