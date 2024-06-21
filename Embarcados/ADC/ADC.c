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
    ADCSRA |= (1<<ADEN); // habilita o conversor
    ADCSRA |= (1<<ADIE); // habilita a interrupção do registrador ADCSRA
    ADCSRA |= (1<<ADIF); // limpa a flag da interrupção
    ADCSRA |= (1<<ADPS0); // escolhe a taxa de conversão, 
    ADMUX |= (1<<REFS0); // define qual o valor de referência do conversor
    ADMUX |= (1<<MUX0); // escolhe qual canal vai ser convertido
    // ADCL E ADCH, registradores da entrada
    // DIDR0, ativa o buffer de entrada digital do pino
    

    /* Habilita globalmente as instruções */
    sei();

    /* Aguarda mudar algo nos estados do botão. */
    while (1) {
       
}
    return 0;
}
