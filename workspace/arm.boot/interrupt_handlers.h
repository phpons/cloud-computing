#ifndef INTERRUPT_HANDLERS_H_
#define INTERRUPT_HANDLERS_H_

#include "main.h"
#include "uart.h"
#include "cb.h"

void setup_interrupts();
void setup_buffers();

void interrupts_handler(void *cookie);
void uart_rx_handler(void *cookie);
void uart_tx_handler(void *cookie);

int circular_buffer_receive(int uart, unsigned char *c);

#endif
