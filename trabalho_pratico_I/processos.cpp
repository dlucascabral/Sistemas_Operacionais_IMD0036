#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <chrono>

using namespace std;

int main(int argc, char *argv[]){
    
    int l1 = atoi(argv[1]);
    int c1 = atoi(argv[2]);
    int l2 = atoi(argv[3]);
    int c2 = atoi(argv[4]);    
    int linha1, coluna1, linha2, coluna2;
    int seg_id = shmget(IPC_PRIVATE, 20*sizeof(char), IPC_CREAT | 0666);
    int **matriz1, **matriz2, **matrizresultante;
    linha1 = l1;
    linha2 = l2;
    coluna1 = c1;
    coluna2 = c2;

    matriz1 = (int**)calloc(l1,sizeof(int *));
    for (int i = 0; i < c1; i++)
    {
        matriz1[i] = (int *)calloc(coluna1, sizeof(int));
    }
    
    //Para iterar o valor do P eu tenho que fazer o calculo
    //das matrizes pra descobrir quantas colunas eu tenho.
    //depois da multiplicação.
    //faz um exit pra finalizar o processo depois de fazer a resultante.
    //assim descendo até todas as linhas.

    pid = fork();
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout<<"Tempo" << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "[ms]" <<endl;
    return 0;
}