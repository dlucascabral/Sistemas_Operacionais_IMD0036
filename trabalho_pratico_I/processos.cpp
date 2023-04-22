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

// Divide o trabalho entre os processos com base no número de valores resultantes que cada processo deve calcular
    int P;
    cout << "Digite o número de valores que cada processo deve calcular: ";
    cin >> P;

    int numero_processos = (linha1 * coluna2) / P;
    if ((linha1 * coluna2) % P != 0) {
        numero_processos++;
    }

    int valor_por_processo[numero_processos];
    for (int i = 0; i < numero_processos; i++) {
        if (i == numero_processos - 1) {
            valor_por_processo[i] = (linha1 * coluna2) - (P * (numero_processos - 1));
        } else {
            valor_por_processo[i] = P;
        }
    }

    // Variáveis para controle dos processos
    int pid, status;
    int indiceatual = 0;
chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    for (int i = 0; i < numero_processos; i++) {
        pid = fork();
    if (pid == 0) {
    int primeire_indice = indiceatual;
    int indicefinal = indiceatual + valor_por_processo[i] - 1;
         for (int j = primeire_indice; j <= indicefinal; j++) {
            int linha = j / coluna2;
            int coluna = j % coluna2;

            int sum = 0;
            for (int k = 0; k < coluna1; k++) {
                sum += matriz1[linha][k] * matriz2[k][coluna];
            }

            matrizresultante[j] = sum;
        }
        shmdt(matrizresultante);
        exit(0);
    } 

    // Atualiza o índice atual
    indiceatual += valor_por_processo[i];

    // Espera pelo processo filho atual antes de criar o próximo
    /*if (i < numero_processos - 1) {
        wait(NULL);
    }*/
}

// Espera pelos processos filhos restantes
/*
for (int i = 0; i < numero_processos - 1; i++) {
    wait(NULL);
}*/
wait(NULL);
 
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
    cout<<"Tempo " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "[ms]" <<endl;
    return 0;
}