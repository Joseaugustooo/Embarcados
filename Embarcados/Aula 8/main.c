/* Necessário para funções e macros básicas */
#include <avr/io.h>

/* Os próximos dois includes são necessários quando se usa interrupçoes */
#include <avr/cpufunc.h>
#include <avr/interrupt.h>

#include <stdint.h>


ISR(USART_RX_vect) {
    /* Verifique se houve erro. Se houve transmita o byte 0xDE. Se não
       houve, ecoe o byte recebido */
}

ISR(TIMER0_COMPA_vect) {
    /* Pisque o LED a cada 320 ms */
    static int i;
    i++;
    int x;
    if (i>=2000|| i < 0){
        PORTB ^= (1<<PB5);
        i = 0;
        for (x = 0; x<20;x++){
            asm("nop");
        }
    }
    
    /* Introduza um delay de 20 instruções NOP */
    
    TIFR0 |= (1<<OCIE0A);
}

/*
 * Função para criar um pequeno delay variável de aproximadamente n
 * us. Máximo de 255 us
 */
void delay(uint8_t n) {
    uint8_t i;

    while (n--)
        for (i=0; i<4; i++)
            asm("nop");
}

void bits(int x){
    int i;
    int c;
    PORTD &= ~(1<<PD6);
    for(i = 15;i>=0;i--){
        c = (1<<i);
        if(x & c){
            PORTD |= (1<<PD6); 
        }
        else{
            PORTD &= ~(1<<PD6);
        }      
        delay(3);
    }
    PORTD |= (1<<PD6);
}

int main(void) {
    /*
     * Configure aqui a porta que controla o LED, iniciando-o apagado
     */
    DDRB |= (1<<PB5);
    PORTB &= 0;
    DDRD |= (1<<PD6);

    /* Configura o timer 0 para dar timeout a cada 160 us (dica: use
       modo CTC) */
    TCCR0A |= (1<<WGM01); // configura o timer para o modo CTC
    TCCR0B |= (1<<CS02); // Divide o clock da placa por 1024
    TIMSK0 |= (1<<OCIE0A); // Habilita a interrupção do comṕarador a
    TIFR0 |=  (1<<OCF0A); // Limpa a flag do comparador a
    OCR0A = 10; // Define o tempo para a flag de interrupção
    TCNT0 = 0; // Neste caso não precisa, mas em alguns casos tem que 
    
    /* Configura a interface serial para receber dados no formato 8N1
       a 480 kHz */
    UCSR0A = 0;
    UCSR0B = 0;
    UCSR0C = 0;

    /* Habilita as interrupções */
    sei();

    /* Gera o sinal digital correspondente a 0xAA55. Se usar loop,
       coloque um delay de 2 instruções NOP antes de mudar o sinal */
    while (1) {
        bits(0xAA55);
        delay(20);        
    }

    return 0;
}
