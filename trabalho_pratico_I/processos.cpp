#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <cstdlib>
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

 /*alocando dinamicamente as matrizes com a função new*/
    int **matriz1 = new int*[linha1];
    int **matriz2 = new int*[linha2];
    int *matrizresultante;
//pegando os valores aleatórios para as matrizes 1 e 2 respectivamente.
    for (int i = 0; i < linha1; i++)
    {
        matriz1[i] = new int[coluna1];
    }
    for (int i = 0; i < linha2; i++)
    {
        matriz2[i] = new int[coluna2];
    }
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
//criação da memoria partilhada entre os processos.
    int memoria = shmget(IPC_PRIVATE, linha1 * coluna2 * sizeof(int), IPC_CREAT | 0666);
    if (memoria == -1)
    {
        cerr << "Erro na criação da memória."<<endl;
        exit(EXIT_FAILURE);
    }
    matrizresultante = (int *) shmat(memoria, NULL, 0);
//criando os processos 1 e 2

    pid_t processo1, processo2;
    int metade = linha1/2;
    processo1 = fork();
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    if (processo1 < 0)
    {
        cerr<<"Erro na criação do processo1"<<endl;
        exit(EXIT_FAILURE);
    }
    else if (processo1 == 0)//Aqui o processo 1 vai executar a metade da matriz resultante.
    {
        for (int i = 0; i < metade; i++)
        {
            for (int j = 0; j < coluna2; j++)
            {
                int calculo = 0;
                for (int k = 0; k < coluna1; k++)
                {
                    calculo += matriz1[i][k] * matriz2[k][j];
                }
                matrizresultante[(i*coluna2)+j] = calculo;
            }
            
        }
        shmdt(matrizresultante);//desanexando a memoria partilhada desse processo.
        exit(EXIT_SUCCESS);
        
    }
    else{ //processo pai
        processo2 = fork();//O processo 2 vai terminar a outra metade da matriz resultante.
        if (processo2 < 0)
        {
            cerr<<"Erro na criação do processo2."<<endl;
            exit(EXIT_FAILURE);
        }
        else if (processo2 == 0)
        {
            for (int i = metade; i < linha1; i++)
            {
                for (int j = 0; j < coluna2; j++)
                {
                    int calculo = 0;
                    for (int k = 0; k < coluna1; k++)
                    {
                        calculo += matriz1[i][k] * matriz2[k][j];
                    }
                    matrizresultante[(i*coluna2)+j] = calculo;
                }
                
            }
            shmdt(matrizresultante);//desanexando a memoria partilhada desse processo.
            exit(EXIT_SUCCESS);
        }
    }
//esperando os dois processos acabarem para retomar ao processo pai.
    for (int i = 0; i < 2; i++)
    {
        wait(NULL);
    }
    shmctl(memoria, IPC_RMID, NULL);
//desalocando as memórias.
     for ( int i = 0; i < linha1; i++)
    {
        delete[] matriz1[i];
    }

    for (int i = 0; i < linha2; i++)
    {
        delete[] matriz2[i];
    }
    
    delete[] matriz1;
    delete[] matriz2;
 
    
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    float tempo = chrono::duration_cast<chrono::milliseconds>(end - begin).count();
    cout<<"Tempo " << tempo << "[ms]" <<endl;
    
    return 0;
}