#include <Arduino.h>
#include "sema.h"

Semaphore::Semaphore() {
	start_green = millis();
	start_yellow = millis();
	start_red = millis();
}