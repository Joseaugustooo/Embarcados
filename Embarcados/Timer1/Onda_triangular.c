/* O código a seguir mostra como fazer um led piscar em forma de onda 
  triangular usando Timer/Counter01 no modo PWM Fast.
*/

/* Necessário para funções e macros básicas */
#include <avr/io.h>

/* Os próximos dois includes são necessários quando se usa interrupções */
#include <avr/cpufunc.h>
#include <avr/interrupt.h>

/* O include a seguir será necessário para fazer manipulação de bits nos registradores*/
#include <stdint.h>
#define F_CPU 16000000
int way = 1;

// Frequência do sinal PWM em OC1A (essa euqação se encontra no datasheet pag. 102)
void Frequencia_PWM(uint32_t f_pwm){
  ICR1 = (F_CPU/(1024UL*f_pwm))-1;            
}

// Duty Cycle do sinal PWM
void Duty_Cycle(uint8_t n){
  OCR1A = (n*ICR1)/100;       // Relaciona OCR1A com o TOP (definido como ICR1) para determinar o duty cycle onde "n/100" é uma porcentagem. Exemplo: duty cycle de 50% basta fazer n = 50.
}

// Triangle wave
void Triangle_wave(){
  static uint8_t duty_cycle = 0;      // Inicial duty cycle

  if(way == 1){
                  // Para way == true ocorrerá um aumento do duty cycleque que vai de 0 a 100
    if(duty_cycle <= 100){
      Duty_Cycle(duty_cycle);
      duty_cycle+=1;
    }
    else{
      way ^= 1;
      duty_cycle-=1;
      Duty_Cycle(duty_cycle);
    }
  }
  else{                             // Para way == false haverá uma dimuniução do dutyc cycle que vai 100 a 0
    if(duty_cycle > 0){
      Duty_Cycle(duty_cycle);
      duty_cycle-=1;
    }
    else{
      way ^= 1;
      Duty_Cycle(duty_cycle);
    }
  }
}

// Setting Timer/Counter01
void timer1_init()
{   // Clear OC1A/OC1B on compare match, set OC1A/OC1B at BOTTOM (non-inverting mode)
    TCCR1A |= (1 << COM1A1); 
    // Fast PWM Mode with ICR1 = TOP
    TCCR1A |= (1 << WGM11);
    TCCR1B |= (1 << WGM12) | (1 << WGM13) ;   

    //Set up timer to  clkI/O / 1024 (from prescaler) 
    TCCR1B |= (1 << CS12)|(1 << CS10);

    // Enable overflow interrupt
    TIMSK1 |= (1 << OCIE1A);        

    Frequencia_PWM(100);

    // Enable global interrupts
    sei();
}

// Interrupt service routine for Timer1 overflow
ISR(TIMER1_COMPA_vect){
  Triangle_wave();
}

int main(void)
{
    // Set PORTD1 as output
    DDRB |= (1 << DDB1);
    
    // Initialize Timer0
    timer1_init();

    // Loop forever
    while(1)
    {
        
    }
}
