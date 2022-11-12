#include "main.h"
#include "console.h"

/**
 * This is the C entry point, upcalled once the hardware has been setup properly
 * in assembly language, see the reset.s file.
 */

void _start() {
  uart_send_string(UART0, "\nQuit with \"C-a c\" and then type in \"quit\".\n");
  run();
}
