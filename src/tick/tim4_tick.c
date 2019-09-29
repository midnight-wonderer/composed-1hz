// Copyright (c) 2018 Sarun Rattanasiri
// under the MIT License https://opensource.org/licenses/MIT

#ifndef __TIM4_TICK_C
#define __TIM4_TICK_C

#include "tim4_tick.h"
#include "stm8s.h"
#include "stm8s_itc.h"

void (*tim4_tick__tick)();

void tim4_tick__setup(Tim4Tick_Config* config) {
  TIM4->PSCR = config->prescaler;
  TIM4->ARR = config->reload_value;
  tim4_tick__tick = config->tick;
  TIM4->CNTR = 0;
  TIM4->IER = 0x01;
  TIM4->CR1 = 0x85;
}

INTERRUPT_HANDLER(tim4_tick__interrupt_routine, ITC_IRQ_TIM4_OVF) {
  TIM4->SR1 &= ~1;
  if (tim4_tick__tick)
    tim4_tick__tick();
}

#endif
