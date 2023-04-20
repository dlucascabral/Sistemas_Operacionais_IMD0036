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
    
    matriz2 = (int **)calloc(linha2,sizeof(int*));
    for (int i = 0; i < linha2; i++)
    {
        matriz2[i] = (int *)calloc(coluna2,sizeof(int));
    }
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    //gerar valores aleatorios
    for (int i = 0; i < linha1; i++)
    {
        for (int j = 0; j < coluna1; j++)
        {
            matriz1[i][j] = (rand()%10 +1);
        }
        
    }
    
    for (int i = 0; i < linha2; i++)
    {
        for (int j = 0; j < coluna2; j++)
        {
            matriz2[i][j] = (rand()%10 +1);
        }
        
    }

    //imprimir elas
    for (int i = 0; i < linha1; i++)
    {
        for (int j = 0; j < coluna1; j++)
        {
            printf("%5d",matriz1[i][j]);
        }
        cout<<endl;
        
    }
    cout<<"                                  "<<endl;
    for (int i = 0; i < linha2; i++)
    {
        for (int j = 0; j < coluna2; j++)
        {
            printf("%5d",matriz2[i][j]);
        }
        cout<<endl;
        
    }

    //matriz resultante
    
    matrizresultante = (int **)calloc(linha1, sizeof(int *));
    for (int i = 0; i < linha1; i++)
    {
        matrizresultante[i] = (int *)calloc(coluna2, sizeof(int));
    }
    int res;
    //Calculando
    for (int i = 0; i < linha1; i++)
    {
        for (int j = 0; j < coluna2; j++)
        {
            int a = j;
           matrizresultante[i][j]   = matrizresultante[i][j] + (matriz1[i][j] * matriz2[j][i]);
             
        }
         
    }
    cout<<"                                  "<<endl;
    for (int i = 0; i < linha1; i++)
    {
        for (int j = 0; j < coluna2; j++)
        {
            printf("%5d",matrizresultante[i][j]);
        }
        cout<<endl;
        
    }
    
    //Para iterar o valor do P eu tenho que fazer o calculo
    //das matrizes pra descobrir quantas colunas eu tenho.
    //depois da multiplicação.
    //faz um exit pra finalizar o processo depois de fazer a resultante.
    //assim descendo até todas as linhas.
    /*int pid;
    pid = fork();*/
    
    
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout<<"Tempo" << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "[ms]" <<endl;
    return 0;
}