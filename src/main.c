#include "stm8s.h"
#include "tim4_periodic_timer.h"
#include "time_prescaler8.h"

CONST TimePrescaler8_Config prescaler_config = {.target = &half_second_handler,
                                                .reload_value = (0x100 - 250)};
static TimePrescaler8_State prescaler_state;
void half_second_handler(void) {
  ChgBit(GPIOB->ODR, 5);
}

CONST Tim4PeriodicTimer_Config two_millisecond_timer_config = {
    .prescaler = TIM4_PRESCALER_32,
    .reload_value = (0x100 - 125),
    .ticked = &two_millisecond_handler,
};
void two_millisecond_handler(void) {
  time_prescaler8__tick(&prescaler_config, &prescaler_state);
}

int main() {
  disableInterrupts();
  SetBit(GPIOB->DDR, 5);
  SetBit(GPIOB->ODR, 5);
  time_prescaler8__init(&prescaler_config, &prescaler_state);
  tim4_periodic_timer__setup(&two_millisecond_timer_config);
  enableInterrupts();
  for (;;) {
    wfi();
  }
}
