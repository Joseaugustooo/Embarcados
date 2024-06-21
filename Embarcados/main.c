/* Necessário para funções e macros básicas */
#include <avr/io.h>

/* Os próximos dois includes são necessários quando se usa interrupçoes */
#include <avr/cpufunc.h>
#include <avr/interrupt.h>

#include <stdint.h>

ISR(INT0_vect) {
}

int main(void) {
    /* Configure aqui o pino INT0 (mapeado no pino PD2 da porta D)
     * como entrada com pull-up (ver seção 14.2.1 da folha de dados do
     * ATMega328p) */
    DDRD &= ~(1 << PD2);
    DDRD |= (1 << PD2);

    DDRB = 1 << PB5;
    PORTD |= (1 << PD5);

    /*
     * Configure aqui os registradores EICRA, EIFR e EIMSK aqui para
     * habilitar (ou não) a interrupção associada à mudança no pino
     * INT0 (veja Seção 13.2 da Folha de Dados do ATMega328p).
     */
    EICRA |= (1 << ISC01) | (1 << ISC11);
    EIFR |= (1 << INTF0) | (1 << INTF1);
    EIMSK |= (1 << INT0) | (0 << INT1);

    /* Habilita globalmente as instruções */
    sei();

    /* Aguarda mudar algo nos estados do botão. */
    while (1) {
        while (!g_pressed)
            ;
        g_pressed = 0;
    }

    return 0;
}
