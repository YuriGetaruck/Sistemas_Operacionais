#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>


int contador = 0;
bool controle = true;
int resposta = 0;

void handler_c(){

    //printf("\nvoce apertou ctrl C\n");
    
    contador++;

}

void handler_z(){

    printf("\nvoce apertou ^C '%i' vezes\n", contador);

}

void alarmHandler(){

    printf("\nSe passaram 20 segundos e o programa ira finalizar \n");
    controle = 0;
}



int main(){

    signal(SIGINT,handler_c); 
    signal(SIGTSTP, handler_z);
    signal(SIGALRM, alarmHandler);



    while(controle){

        
        if (contador >= 3){

            printf("\nrealmente deseja sair do programa?[1/0]:");
            alarm(20);
            scanf("%d",&resposta);
            
            if(resposta==1){
                controle = 0;
                contador = 0;
            }if(resposta == 0){
                controle = 1;
                contador = 0;
            }
        }
    }
    
    printf("\nobrigado\n");

    return 0;
}
