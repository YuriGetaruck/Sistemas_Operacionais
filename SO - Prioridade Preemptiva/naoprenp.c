void penp()
{ // nao preempitivo
    int ordem_exe[queueSize];
    int l = 0;
    gera_oredem(prior, ordem_exe, 0);
    printf("\nPrioridade Estatica Não-Preemptivo:\n\n");
    while (1)
    {
        if (l == queueSize) // se acabar a lista de prioridade
        {
            kill(spid[alterna], SIGSTOP);
            printf("\nPrioridade Estatica Não-Preemptivo finalizado!\n\n");
            break;
        }
        signal(SIGALRM, alternaTarefa); // caham o alarme quando a funcao alternaTarefa é solicitada
        if (alterna < 0)                // caso a variavel alterna seja menor do que 0 chama o alarm 1
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
        while (!receive) // enquanto reicive
            pause();
        receive = 0;
    }
}

void pep() // preempitivo
{
    int ordem_exe[queueSize];
    int l = 0;
    gera_ordem(prior, ordem_exe, 1);
    printf("\nPrioridade Estatica Preemptivo:\n\n");
    while (1)
    {
        if (l == queueSize) // se acabar a lista de prioridade
        {
            kill(spid[alterna], SIGSTOP);
            printf("\nPrioridade Estatica Preemptivo finalizado!\n\n");
            break;
        }
        signal(SIGALRM, alternaTarefa); // caham o alarme quando a funcao alternaTarefa é solicitada
        if (alterna < 0)                // caso a variavel alterna seja menor do que 0 chama o alarm 1
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
        while (!receive) // enquanto reicive
            pause();
        receive = 0;
    }
}