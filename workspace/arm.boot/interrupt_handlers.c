#include "interrupt_handlers.h"
#include "uart-irqs.h"

struct cb *transmit_cb;
struct cb *receive_cb;

void interrupts_handler(void *cookie) {  
    if(is_RX_interruption()){
        uart_rx_handler(cookie);
    }
    if(is_TIMEOUT_interruption()) {
        uart_timeout_handler(cookie);
    }
    if(is_TX_interruption()) {
        uart_tx_handler(cookie);
    }
    interrupt_clear();
}

void uart_rx_handler(void *cookie) {
    unsigned char c;
    uart_receive(UART0, &c);
    while (c != 0) {
        if (!cb_full(receive_cb)) { // We might drop data here
            cb_put(receive_cb, c);
        }
        c = uart_receive(UART0, &c);
    }
}

int circular_buffer_receive(int uart, unsigned char *c) {
    return (cb_get(receive_cb, c) + 1);
}

void uart_tx_handler(void *cookie) {
    // Not working
    unsigned char c;
    unsigned short* uart_fr = (unsigned short*) (UART0 + UART_FR);

    while(!(*uart_fr & UART_TXFF)){
        if (!cb_empty(transmit_cb)) {
            cb_get(transmit_cb, &c);
        }
        uart_send(UART0, c);
    }
}

void uart_timeout_handler(void *cookie){
    uart_rx_handler(cookie);
    debugkprintf("Timeout interruption\r\n");
}

void setup_interrupts() {
    setup_buffers();

    // FIFO setup
    uint16_t lcr = *(uint16_t*) (UART0 + CUARTLCR_H);
    lcr |= CUARTLCR_H_FEN;
    *(uint16_t*) (UART0 + CUARTLCR_H) = lcr;

    // Interruption setup
    unsigned short* imsc = (unsigned short*) (UART0 + UART_IMSC);
    *imsc = UART_IMSC_RXIM | UART_IMSC_TXIM | UART_IMSC_RTIM;
    *(uint16_t*) (UART0 + UART_IMSC) = imsc;
}

void setup_buffers() {
    cb_init(receive_cb);
    cb_init(transmit_cb);
}

int is_RX_interruption() {
    return UART_MIS_RXMIS & (UART0 + UART_MIS);
}

int is_TX_interruption() {
    return UART_MIS_TXMIS & (UART0 + UART_MIS);
}

int is_TIMEOUT_interruption() {
    return UART_MIS_RTMIS & (UART0 + UART_MIS);
}

void interrupt_clear() {
    unsigned short* uart_ICR = (unsigned short*) (UART0 + UART_ICR);
    *uart_ICR |= UART_ICR_RTIC | UART_ICR_TXIC | UART_ICR_RXIC;
}
