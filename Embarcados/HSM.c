#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum{
    a, b, c, d
} estados;

estados state = a;  

void soma(float x){
    float y;
    printf("Digite o valor que sera somado com %f",x);
    fflush(stdin);
    scanf("%f", &y);
    printf("%f",x+y);
}

void multiplicacao(float x){
    float y;
    printf("Digite o valor que sera multiplicado com %f",x);
    fflush(stdin);
    scanf("%f", &y);
    printf("%f",x+y);
}

void subtracao(float x){
    float y;
    printf("Digite o valor que sera subtraido de %f",x);
    fflush(stdin);
    scanf("%f", &y);
    printf("%f",x-y);
}

void divisao(float x){
    float y;
    printf("Digite o valor que sera o divisor de %f",x);
    fflush(stdin);
    scanf("%f", &y);
    printf("%f",x/y);
}

int main(void){
    char escolha;
    float x;
    estados state;    
    while(1){    
    prinft("Digite seu primeiro operando");
    fflush(stdin);
    scanf("%f",&x);
    printf("Digite o estado que voce quer ");
    fflush(stdin);
    scanf("%c",escolha);
    }

}


