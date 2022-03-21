#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/wait.h>



int main(){


    int pid, status;

    pid = fork();


    if(pid<0){

        perror("Error: erro no fork\n");

    }else if(pid == 0){

        pid = fork();

        if(pid<0){
            perror("Error: erro no fork\n");
            
        }else if(pid == 0){

            printf("Processo C %d, filho do processo B: %d\n", getpid(), getppid());

        }else{
            wait(&status);
            sleep(1);
            printf("Processo B %d, filho do processo A: %d\n", getpid(), getppid());

            
        } 

    }else{
        wait(&status);
        sleep(1);
        printf("Processo A %d\n", getpid());
    }   

    return 0;
}
