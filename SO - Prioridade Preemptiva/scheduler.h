#ifndef _SCHEDULER
#define _SCHEDULER
#define UNUSED(x) (void)(x)

#include "jobs.h"

extern int spid[100];
extern int queueSize;
extern int pidx;
int alterna;
int receive;
int *tempo;
int *prior;

void gera_ordem(int vet[], int dest[]);
void alternaTarefa(int signum);
void scheduler_init(char *jobs, float quantum);
void pep();

#endif
