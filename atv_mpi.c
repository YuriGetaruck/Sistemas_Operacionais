#include <mpi.h>
#include <stdio.h>
#define COORDENADOR 0

int mat3[3][3] = {{0,0,0},{0,0,0},{0,0,0}};

int main(int argc, char **argv)
{
    int i, id, size, len, tag = 666;

    int *linha;
    int *buffmat2[3][3];

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
        int mat1[3][3] = {{0, 1, 2}, {1, 4, 3}, {5, 6, 2}};
        int mat2[3][3] = {{0, 1, 2}, {1, 4, 3}, {5, 6, 2}};
        printf("entrouaqui1 ");
        for (i = 1; i < size; ++i)
        {
            printf("entrouaqui2 ");

                //envia a linha m1
                printf("entrouaqui3\n ");
                MPI_Send(mat1[i-1], 1, MPI_INT, i, tag, MPI_COMM_WORLD);
                printf("entrouaqui4\n");

                //envia a matriz m2
                MPI_Send(mat2, 3*3, MPI_INT, i, tag, MPI_COMM_WORLD);

                //recebe a linha da matriz nova m3


                //aloca a linha na matriz nova m3

        }
    }
    if(id > 0)
    {
        printf("entrouaqui5 ");
        MPI_Recv(&linha, 3, MPI_INT, COORDENADOR, tag, MPI_COMM_WORLD, &stats);
        printf("entrou aqui6 \n");
        MPI_Recv(&buffmat2, 3*3, MPI_INT, COORDENADOR, tag, MPI_COMM_WORLD, &stats);
        printf("entrou aqui6 \n");
        printf("\nO processo %d recebeu a linha com digito inicial: %d", i, linha[0]);


        for(int k = 0; k > 3 ; k++){
            printf("multiplica\n");
            mat3[i-1][k] = mat3[i-1][k] + linha[k] * *buffmat2[k][i-1];
        }
    }




    MPI_Finalize();

            for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                printf("[%d]\t", mat3[i][j]);
            }
            printf("\n");
        }

    return 0;
}