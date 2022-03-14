#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

int contador = 0;
char controle;
bool controle_while = true;

void alarmHandler(){

    printf("voce tem 20 segundos para se decidir, caso contrario o programa fecahrá\n");
    controle_while = false;
}

void handler_c(int signum){
    pause();
    contador=contador+1;
    printf("%d",contador);
}

void handler_z(){
    pause();
    printf("voce apertou ^C '%d' vezes", contador);
}

int main(){

    signal(SIGINT,handler_c);        
    signal(SIGTSTP, handler_z);

    while(controle_while){

        if (contador >= 3){

            printf("realmente deseja sair do programa?[y/n]");
            scanf("%controle",&controle);
            
            if(controle=="y"){
                controle_while = false;
            }if(controle == "n"){
                controle_while = true;
                contador = 0 ;
            }
            if(contador >=3){
                alarm(20);
                signal(SIGALRM, alarmHandler);
            }
        }
    }    

    printf("\n\nobrigado por usar o prgrama\n\n");

    return 0;
}
