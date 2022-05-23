#include "scheduler.h"
#include "load_jobs.h"
#include <unistd.h>
#include <signal.h>

void gera_ordem(int vet[], int dest[])
{
	int i, j, maior, pos_index;
	int aux[queueSize];
	pos_index = -1;
	for (i = 0; i < queueSize; i++)
		aux[i] = vet[i];
	for (i = 0; i < queueSize; i++)
	{
		maior = -1;
		for (j = 0; j < queueSize; j++)
		{
			if (aux[j] > maior)
			{
				maior = aux[j];
				pos_index = j;
			}
		}
		dest[i] = pos_index;
		aux[pos_index] = -1;
	}
}

void scheduler_init(char *jobs, float quantum)
{

	pidx = 0;
	receive = 0;

	loadJobs(jobs);

	print_jobsQueue();

	int i, l;

	tempo = (int *)malloc(queueSize * sizeof(int));
	prior = (int *)malloc(queueSize * sizeof(int));

	for (l = 0; l < queueSize * 2; l += 2)
	{
		tempo[l / 2] = atoi(argumentos[l]);
		prior[l / 2] = atoi(argumentos[l + 1]);
	}

	for (i = 0; i < queueSize; i++)
	{
		iniciarProcesso(i);
		kill(spid[i], SIGSTOP);
	}

	alterna = -1;

	switch (tipo_esc)
	{
	case 0: /* Prioridade Preemptiva: */
		pep();
		break;
	case 1: /* Prioridade Naõ-Preemptiva: */
		printf("Prioridade Naõ-Preemptiva\n");
		break;
	}
}

void pep()
{
	int ordem_exe[queueSize];
	int l = 0;
	gera_ordem(prior, ordem_exe, 1);
	printf("\nPrioridade Estatica Preemptivo:\n\n");
	while (1)
	{
		if (l == queueSize)
		{
			kill(spid[alterna], SIGSTOP);
			printf("\nPrioridade Estatica Preemptivo finalizado!\n\n");
			break;
		}
		signal(SIGALRM, alternaTarefa);
		if (alterna < 0)
			alarm(1);
		else
		{
			if (alterna != ordem_exe[l])
				alternaTarefa(0);
			else
			{
				alarm(tempo[alterna]);
				l++;
			}
		}
		while (!receive)
			pause();
		receive = 0;
	}
}

void alternaTarefa(int signum)
{
	UNUSED(signum);

	receive = 1;
	kill(spid[alterna], SIGSTOP);

	if (!alterna)
		alterna++;
	else
		alterna = 0;

	kill(spid[alterna], SIGCONT);
}