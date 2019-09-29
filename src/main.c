#include <stdint.h>
#include "stm8s_tim4.h"
#include "tick/tim4_tick.h"

CONST Tim4Tick_Config ms_tick_config = {
    .prescaler = TIM4_PRESCALER_16,
    .reload_value = (0x100 - 125),
    .tick = &ms_handler,
};

int main() {
  disableInterrupts();
  SetBit(GPIOB->DDR, 5);
  SetBit(GPIOB->ODR, 5);
  tim4_tick__setup(&ms_tick_config);
  enableInterrupts();
  for (;;) {
    wfi();
  }
}

uint8_t count = 0;
void ms_handler() {
  count++;
  if (count)
    return;
  ChgBit(GPIOB->ODR, 5);
}
