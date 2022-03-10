#include "stdio.h"
#include "string.h"
#include "unistd.h"
#include "stdbool.h"
#include "stdlib.h"
#include "signal.h"


void handler(){
    printf("print do alarm\n");
}

void myprintf(int x, int y, char* msg){
 
    int segundos=3;
    int size = strlen(msg);
    char msg2[11];


    strcpy(msg2,"\033[ B\033[ C");   
    
    
    msg2[2]= x + '0';
    msg2[6]= y + '0';

    for(int i=0; i<=10; i++){
        printf("%d", i);
    }
    printf(" (posicao y da tela)\n");

    write(1, msg2, 8);
    write(1, msg, 20);

    
    printf("\n\n");

    // while(1){
    //     alarm(segundos);
    //     pause();
    //     sginal(SIGALRM, handler());
    // }

       
    //TODO implementar os writes
}

int main(){

    int x = 3;
    int y = 7;
    char *msg = malloc(20*sizeof(char));

    myprintf(x,y,"teste");

    return 0;
}