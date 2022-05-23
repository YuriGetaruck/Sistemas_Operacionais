#ifndef _JOBS
#define _JOBS

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <unistd.h> //ta declarado duas vezes
#include <sys/types.h>
#include <sys/wait.h>

char **fila;
char **argumentos;
int queueSize; /*Tamanho da Fila de tarefas*/
int spid[100];
int pidx;
int tipo_esc;

void print_jobsQueue();
void iniciarProcesso(int index);

#endif
