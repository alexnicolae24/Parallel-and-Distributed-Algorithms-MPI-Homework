#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M0 0

//functie pentru afisare topologiei
void print_topology(int rank, int mat[20][20]){
    printf("%d -> 0:", rank);
        for (int i = 0; i < 20; i++){
            if (mat[M0][i+1] != 0){
                    printf("%d,", mat[M0][i]);
                }
                else {
                    printf("%d ", mat[M0][i]);
                    break;
                }
        }

    printf("1:");
    for (int i = 0; i < 20; i++){
        if (mat[M0+1][i+1] != 0){
                printf("%d,", mat[M0+1][i]);
        }
        else{
            printf("%d ", mat[M0+1][i]);
            break;
        }
    }

    printf("2:");
    for (int i = 0; i < 20; i++){
        if (mat[M0+2][i+1] != 0){
                printf("%d,", mat[M0+2][i]);
        }
        else{
            printf("%d ", mat[M0+2][i]);
            break;
        }
    }

    printf("3:");
    for (int i = 0; i < 20; i ++){
        if (mat[M0+3][i+1] != 0){
                printf("%d,", mat[M0+3][i]);
        }
        else{
            printf("%d ", mat[M0+3][i]);
            break;
        }
    }
    printf("\n");
}

int main (int argc, char *argv[])
{
    int procs, rank;
    int master = 0;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Status status;
    
    //Declarare matrice de workeri
    int mat[20][20] = {0};

    //Declararea numarul de workeri si al vectorilor de workeri
    int nr_w0 = 0,nr_w1 = 0,nr_w2 = 0,nr_w3 = 0;
    int* workers0; 
    int* workers1; 
    int* workers2; 
    int* workers3; 

    if(rank == M0){
        //Citirea din fisier si retinerea workerilor rankului 0 in matrice
        FILE *cluster0 = fopen("cluster0.txt", "r");
        fscanf(cluster0, "%d", &nr_w0);
        workers0 = malloc(nr_w0 * sizeof(int));
        for (int i = 0; i < nr_w0; i++){
            fscanf(cluster0, "%d", &workers0[i]);  
            mat[rank][i] = workers0[i];  
        }
        fclose(cluster0);

        //Trimiterea matricei catre procesul 1
        MPI_Send(mat, 400, MPI_INT, M0+1, 0, MPI_COMM_WORLD);
        
        //Trimiterea rank-ului procesului master catre workeri
        master = M0;
        for (int i = 0; i < nr_w0; i++){
            MPI_Send(&master, 1, MPI_INT, workers0[i], 0, MPI_COMM_WORLD);
            printf("M(%d,%d)\n", rank, workers0[i]);  
            //MPI_Send(mat, 400, MPI_INT, workers0[i], 0, MPI_COMM_WORLD);
        }
    }
    else if(rank == M0 + 1){
            //Primirea matrciei de la procesul 0
            MPI_Recv(mat, 400, MPI_INT, M0, 0, MPI_COMM_WORLD, &status);

            //Citirea din fisier si retinerea workerilor rankului 1 in matrice
            FILE *cluster1 = fopen("cluster1.txt", "r");
            fscanf(cluster1, "%d", &nr_w1);
            workers1 = malloc(nr_w1 * sizeof(int));
            for (int i = 0; i < nr_w1; i++){
                fscanf(cluster1, "%d", &workers1[i]);    
                mat[rank][i] = workers1[i];
            }
            fclose(cluster1);

            //Trimiterea matricei catre procesul 2
            MPI_Send(mat, 400, MPI_INT, M0+2, 0, MPI_COMM_WORLD);
            
            //Trimiterea rank-ului procesului master catre workeri
            master = M0 + 1;
            for (int i = 0; i < nr_w1; i++){
                MPI_Send(&master, 1, MPI_INT, workers1[i], 0, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, workers1[i]);  
                //MPI_Send(mat, 400, MPI_INT, workers1[i], 0, MPI_COMM_WORLD);
            }
        }
        else if (rank == M0 + 2){
            //Primirea matrciei de la procesul 1
            MPI_Recv(mat, 400, MPI_INT, M0+1, 0, MPI_COMM_WORLD, &status);

            //Citirea din fisier si retinerea workerilor rankului 1 in matrice
            FILE *cluster2 = fopen("cluster2.txt", "r");
            fscanf(cluster2, "%d", &nr_w2);
            workers2 = malloc(nr_w2 * sizeof(int));
            for (int i = 0; i < nr_w2; i++){
                fscanf(cluster2, "%d", &workers2[i]);    
                mat[rank][i] = workers2[i];
            }
            fclose(cluster2);
           
            //Trimiterea matricei catre procesul 3
            MPI_Send(mat, 400, MPI_INT, M0+3, 0, MPI_COMM_WORLD);
            
            //Trimiterea rank-ului procesului master catre workeri
            master = M0 + 2;
            for (int i = 0; i < nr_w2; i++){
                MPI_Send(&master, 1, MPI_INT, workers2[i], 0, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, workers2[i]);  
                //MPI_Send(mat, 400, MPI_INT, workers2[i], 0, MPI_COMM_WORLD);
            }
	    }
        else if (rank == M0 + 3){
            //Primirea matrciei de la procesul 2
            MPI_Recv(mat, 400, MPI_INT, M0+2, 0, MPI_COMM_WORLD, &status);

            //Citirea din fisier si retinerea workerilor rankului 1 in matrice
            FILE *cluster3 = fopen("cluster3.txt", "r");
            fscanf(cluster3, "%d", &nr_w3);
            workers3 = malloc(nr_w3 * sizeof(int));
            for (int i = 0; i < nr_w3; i++){
                fscanf(cluster3, "%d", &workers3[i]);    
                mat[rank][i] = workers3[i];
            }
            fclose(cluster3);

            //Afisarea topologiei pentru rankul 3
            print_topology(rank,mat);

            //Trimiterea matricei catre procesele 0 si 2
            MPI_Send(mat, 400, MPI_INT, M0, 0, MPI_COMM_WORLD);

            //Trimiterea rank-ului procesului master catre workeri si afisarea topologiei pentru fiecare worker
            master = M0 + 3;
            for (int i = 0; i < nr_w3; i++){
                MPI_Send(&master, 1, MPI_INT, workers3[i], 0, MPI_COMM_WORLD);
                printf("M(%d,%d)\n", rank, workers3[i]); 
                MPI_Send(mat, 400, MPI_INT, mat[M0+3][i], 0, MPI_COMM_WORLD);
                
            }
            
           
        }
        else{
            //Primirea rankurilor si a matricei de  proceselor master
            MPI_Recv(&master, 1, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            //
        }

        nr_w0 = 0; 
        nr_w1 = 0;
        nr_w2 = 0;
        nr_w3 = 0;

        //Afisarea topologiei pentru procesele 0,1,2 si workerii acestora
        if(rank == M0){
		    MPI_Recv(mat, 400, MPI_INT, M0+3, 0, MPI_COMM_WORLD, &status);
            print_topology(rank,mat);
            for(int j = 0; j < 20; j++){
                if(mat[M0][j] != 0){
                    nr_w0++;
                }
            }
            for(int j = 0; j < nr_w0; j++){
                MPI_Send(mat, 400, MPI_INT, mat[M0][j], 0, MPI_COMM_WORLD);
            }
            MPI_Send(mat, 400, MPI_INT, M0+1, 0, MPI_COMM_WORLD);
        }

        if(rank == M0+1){
		    MPI_Recv(mat, 400, MPI_INT, M0, 0, MPI_COMM_WORLD, &status);
            print_topology(rank,mat);
            for(int j = 0; j < 20; j++){
                if(mat[M0+1][j] != 0){
                    nr_w1++;
                }
            }
            for(int j = 0; j < nr_w1; j++){
                 MPI_Send(mat, 400, MPI_INT, mat[M0+1][j], 0, MPI_COMM_WORLD);
            }
            MPI_Send(mat, 400, MPI_INT, M0+2, 0, MPI_COMM_WORLD);

        }      

        if(rank == M0+2){
		    MPI_Recv(mat, 400, MPI_INT, M0+1, 0, MPI_COMM_WORLD, &status);
            print_topology(rank,mat);
            for(int j = 0; j < 20; j++){
                if(mat[M0+2][j] != 0){
                    nr_w2++;
                }
            }
           
            for(int j = 0; j < nr_w2; j++){
                MPI_Send(mat, 400, MPI_INT, mat[M0+2][j], 0, MPI_COMM_WORLD);
            }
        }

        if(rank >= 4){
            MPI_Recv(mat, 400, MPI_INT, MPI_ANY_SOURCE, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            print_topology(rank,mat);
        }
                      
    MPI_Finalize();
}