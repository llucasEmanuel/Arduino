  #include <Arduino.h>

#include "sema.h"
#include "ports.h"

/* Inicializa as variáveis básicas de ciclo */
Semaphore::Semaphore() {
	start_cycle = millis();
	is_counting = false;
}
