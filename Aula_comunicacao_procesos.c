#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main(){
    
    //processos
    int pid, status;

    //pipes
    int pip[2];
    int pip2 [2];
    pipe(pip);
    pipe(pip2);
    int size;
    
    pid = fork();//cria os processos
    
    if(pid<0){
        perror("Error: erro no fork\n");
    }else if(pid == 0){
        
        char *msg = "Oloko bicho, ta pegando fogo aqui meu.. ";
        size = strlen(msg);
    
        write(pip[1], msg, size);
        write(pip2[1], &size, sizeof(int));

    }else{
        
        int tamanho = 0;

        read(pip2[0], &tamanho, sizeof(int));
        char buf[tamanho];
        //buf = (char*) malloc(sizeof(char)*tamanho);


        wait(&status);
        read(pip[0], buf, tamanho);

        printf("%sChama la os bombeiros...", buf);    
    }

    return 0;
}