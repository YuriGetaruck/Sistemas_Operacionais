#include <mpi.h>
#include <stdio.h>
#define COORDENADOR 0

int main(int argc, char **argv)
{

    // for(int i = 0; o < 3; i++){
    //     for(int j = 0, j < 3; j++){
    //         printf("Defina o valor da matriz na prosicao M[%d][%d]", i, j);
    //         scanf(%d, &matriz[i][j]);
    //     }
    // }

    int mat1[3][3] = {{0, 1, 2}, {1, 4, 3}, {5, 6, 2}};
    int mat2[3][3] = {{0, 1, 2}, {1, 4, 3}, {5, 6, 2}};
    int mat3[3][3];

    int i, id, size, len, tag = 666;
    int *enviado;
    int termo_recebido1;
    int termo_recebido2;
    int *termo1;
    int *termo2;
    MPI_Status stats; // Status da mensagem recebida

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &size); // size == número de processos

    if (id == COORDENADOR)
    {
        for (i = 1; i < size; ++i)
        {
            for (int j = 0; j < 3; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    int somaprod = 0;
                    for (int l = 0; l < 3; l++)
                    {
                        termo1 = mat1[j][l];
                        termo2 = mat2[i][k];
                        MPI_Send(termo1, 1, MPI_INT, i, tag, MPI_COMM_WORLD);
                        MPI_Send(termo2, 1, MPI_INT, i, tag, MPI_COMM_WORLD);
                        somaprod += mat1[j][l] * mat2[i][k];
                        mat3[j][k] = somaprod;
                    }
                }
            }
        }
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                printf("[%d]\t", mat3[i][j]);
            }
            printf("\n");
        }
    }
    else
    {
        MPI_Recv(&termo_recebido1, 1, MPI_INT, COORDENADOR, tag, MPI_COMM_WORLD, &stats);
        MPI_Recv(&termo_recebido2, 1, MPI_INT, COORDENADOR, tag, MPI_COMM_WORLD, &stats);

        int somaprod = 0;

        somaprod = termo_recebido1 * termo_recebido2;

        printf("\nO processo %d recebeu %d e %d, e esta retornando %d\n", i, termo_recebido1, termo_recebido2, somaprod);

        MPI_Send(&somaprod, 1, MPI_INT, COORDENADOR, tag, MPI_COOM_WORLD);
    }

    MPI_Finalize();

    return 0;
}