#include <Arduino.h>

#include "sema.h"
#include "ports.h"

Semaphore::Semaphore() {
	start_green = millis();
	start_red = millis();
  	is_counting = false;
}
