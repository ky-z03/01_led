#ifndef __ESPTIMER_H
#define __ESPTIMER_H

#include "esp_timer.h"

void esptimer_int_init(uint64_t tps);
void esptim_callback(void *arg);

#endif