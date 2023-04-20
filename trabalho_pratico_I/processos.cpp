#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <chrono>
#include <time.h>
using namespace std;



int main(int argc, char *argv[]){
    srand(time(NULL));
    int l1 = atoi(argv[1]);
    int c1 = atoi(argv[2]);
    int l2 = atoi(argv[3]);
    int c2 = atoi(argv[4]);    
    int linha1, coluna1, linha2, coluna2;
    linha1 = l1;
    linha2 = l2;
    coluna1 = c1;
    coluna2 = c2;
if (coluna1 != linha2)
    {
        cout<<"Erro, as dimensões escolhidas não são permitidas para a multiplicação de matrizes."<<endl;
        return 1;
    }
    
    //int seg_id = shmget(IPC_PRIVATE, 20*sizeof(char), IPC_CREAT | 0666);
    int **matriz1 = new int*[linha1];
    int **matriz2 = new int*[linha2];
    int **matrizresultante = new int*[linha1];
    for (int i = 0; i < linha1; i++)
    {
        matriz1[i] = new int[coluna1];
        matrizresultante[i] = new int[coluna2];
    }
    for (int i = 0; i < linha2; i++)
    {
        matriz2[i] = new int[coluna2];
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
/*
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
        
    }*/
    
    //Calculando
    for (int i = 0; i < linha1; i++)
    {
        for (int j = 0; j < coluna2; j++)
        {
           matrizresultante[i][j] = 0;
           for (int k = 0; k < coluna1; k++)
           {
             matrizresultante[i][j] += matriz1[i][k] * matriz2[k][j];
           }
           
        }
         
    }
   /* cout<<"                                  "<<endl;
    for (int i = 0; i < linha1; i++)
    {
        for (int j = 0; j < coluna2; j++)
        {
            printf("%5d",matrizresultante[i][j]);
        }
        cout<<endl;
        
    }*/

     for ( int i = 0; i < linha1; i++)
    {
        delete[] matriz1[i];
        delete[] matrizresultante[i];
    }

    for (int i = 0; i < linha2; i++)
    {
        delete[] matriz2[i];
    }
    
    delete[] matriz1;
    delete[] matriz2;
    delete[] matrizresultante;

     //Para iterar o valor do P eu tenho que fazer o calculo
    //das matrizes pra descobrir quantas colunas eu tenho.
    //depois da multiplicação.
    //faz um exit pra finalizar o processo depois de fazer a resultante.
    //assim descendo até todas as linhas.
    /*int pid;
    pid = fork();*/
    
    
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    float tempo = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout<<"Tempo " << tempo/1000 << "[s]" <<endl;
    
    return 0;
}