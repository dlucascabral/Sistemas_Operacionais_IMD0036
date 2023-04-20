#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <chrono>
#include <time.h>
using namespace std;



int main(int argc, char *argv[]){
 //função para poder gerar os números aleatórios
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
 //verificar se é possível calcular a matriz resultante 
    if (coluna1 != linha2)
    {
        cout<<"Erro, as dimensões escolhidas não são permitidas para a multiplicação de matrizes."<<endl;
        return 1;
    }
    
    /*int seg_id = shmget(IPC_PRIVATE, 20*sizeof(char), IPC_CREAT | 0666);*/

 /*alocando dinamicamente as matrizes com a função new*/
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
   /*loop para preencher com numeros aleatórios as matrizes*/
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
 /*vendo o que eu faço com essa criação de um processo filho.*/   
  /*  int pid;
    pid = fork();
    */
/*calculo da matriz resultante*/
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
/*usando a função delete para liberar os espaços utilizados na criação das matrizes*/
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
 
    
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    float tempo = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout<<"Tempo " << tempo/1000 << "[s]" <<endl;
    
    return 0;
}