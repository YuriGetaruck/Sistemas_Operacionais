#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <sys/wait.h>



int main(){


    int pid, status;

    pid = fork();

    int a = 0;

    if(pid<0){
        perror("Error: erro no fork\n");
    }else if(pid == 0){
        a += 100;
        printf("Processo filho %d\t%d\n", getpid(), a);
        //while(1);
        execl("/bin/ls","ln","--l", "NULL");
    }else{
        a += 10;
        printf("Processo pai %d\t%d\n", getpid(),a);
        wait(&status);
    }   

    return 0;
}