#include <mpi.h>
#include <stdio.h>
#define GERENTE 0


int main(int argc , char **argv){

    int i, id , size ,len , tag = 666;
    char *enviado;
    char recebido[50];
    char *resposta;
    MPI_Status stats; // Status da mensagem recebida

    MPI_Init (&argc , &argv);
    MPI_Comm_rank(MPI_COMM_WORLD , &id);
    MPI_Comm_size(MPI_COMM_WORLD , &size); //size == número de processos

    if (id == GERENTE) {
        for (i = 1; i < size; ++i) {
        MPI_Recv (&recebido , 50 , MPI_CHAR , i, tag , MPI_COMM_WORLD ,
        &stats);
        printf("Mensagem recebida do processo %d: %s \n\n", i, recebido);
        resposta = "Chama os famosos bombeiros la\n\n";
        MPI_Send(resposta, 50, MPI_CHAR, i, tag, MPI_COMM_WORLD);
        }
    } else {
        enviado = "OLOKO ta pegando fogo bicho\n\n";
        MPI_Send (enviado, 50, MPI_CHAR, GERENTE, tag,MPI_COMM_WORLD);
        MPI_Recv(&recebido , 50 , MPI_CHAR , i, tag , MPI_COMM_WORLD ,
        &stats);
        printf("msg recebida do processo %d: %s", i, recebido);
    }

    MPI_Finalize();

    return 0;
}