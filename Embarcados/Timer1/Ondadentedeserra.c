/* Necessário para funções e macros básicas */
#include <avr/io.h>

/* Os próximos dois includes são necessários quando se usa interrupçoes */
#include <avr/cpufunc.h>
#include <avr/interrupt.h>

#include <stdint.h>

#define F_CPU 16000000
// NÃO COLOCAR FREQUÊNCIAS MENORES DO QUE 2.44 Hz

void duty_cycle(int duty){
    OCR1A = duty*ICR1/100;

}

void frequencia_pwm(int F){
    ICR1 = F_CPU/(F*100);
}

void timer1(){
    TCCR1A |= (1<<WGM11)|(1<<COM1A1); // configura o timer para o modo fast PWM, 
    TCCR1B |= (1<<WGM13)|(1<<WGM12)|(1<<CS10); // Divide o clock da placa por 1024, e completa a configuração do modo fast pwm com a linha anterior
    TIMSK1 |= (0<<OCIE1A)|(1<<TOIE1); // Habilita a interrupção do comṕarador a
    TIFR1 |=  (1<<OCF1A)|(1<<TOV1); // Limpa a flag do comparador a
    //OCR1A = 2; // Define o tempo para a flag de interrupção
    //ICR1 = 255; // Muda o topo, se não for utilizado, el-e fica em 2**16-1
    TCNT1 = 0; // Neste caso não precisa, mas em alguns casos tem que escolher o ponto de início da contagem, mas como está em zero, não precisa pois o contador iniciará nessse ponto

}

ISR(TIMER1_OVF_vect) {
    static int n = 1;
    duty_cycle(n);
    if (n >= 99){
        n = 1; 
    }
    else {
        n += 1;    
    }
    
    
    //TIFR1 |= (1<<OCF1A)|(1<<TOV1);
}

int main(void) {
    /*
     Configurando o pino PB1 como saída
     */
    DDRB |= (1<<PB1);
    timer1();
    frequencia_pwm(100);
    //duty_cycle(75);
    

    /* Habilita as interrupções */
    sei();

    while (1) {       
    }

    return 0;
}
