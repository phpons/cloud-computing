#include "main.h"
#include "console.h"
#include "uart-irqs.h"
#include "board_vab.h"
#include "vic.h"
#include "interrupt_handlers.h"


/**
 * This is the C entry point, upcalled once the hardware has been setup properly
 * in assembly language, see the reset.s file.
 */

void _start() {
  uart_send_string(UART0, "\nQuit with \"C-a c\" and then type in \"quit\".\n");
 
  vic_setup();
  void *cookie=NULL;
  vic_irq_enable(UART0_IRQ, interrupts_handler, cookie);
  setup_interrupts();
  vic_enable();

  while (1) {
    unsigned char c;
    while (circular_buffer_receive(UART0, &c) == 0) {
      wfi();
    }
    if (c == '\r') {
        kprintf("\r\n");
    } else {
        uart_send(UART0, c);
    }
  }
}
// cd projects/CloudWeek1/workspace/arm.boot