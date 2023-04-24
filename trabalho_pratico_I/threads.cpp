#include <pthread.h>
#include <iostream>
#include <chrono>

using namespace std;


// A estrutura a seguir contém as informações das threads
// as linhas da matriz que serão multiplicadas por essa thread
// os ponteiros para as matrizes de entrada e de saída.
// A idéia é utilizar essa struct como variáveis globais
// pois aqui, diferentemente de processos, não temos espaço de memória compartilhada
struct thread_data {
    int id;
    int linha_ini;
    int linha_fim;
    int coluna;
    int **matrizA;
    int **matrizB;
    int **matrizR;
};

// A função abaixo é executada por cada thread e é responsável por multiplicar uma parte da matriz. 
void *multiplica_parte_matriz(void *arg) {
    struct thread_data *data = (struct thread_data *)arg;
    int id = data->id;
    int linha_ini = data->linha_ini;
    int linha_fim = data->linha_fim;
    int coluna = data->coluna;
    int **matrizA = data->matrizA;
    int **matrizB = data->matrizB;
    int **matrizR = data->matrizR;
    
    for (int i = linha_ini; i < linha_fim; i++) {
        for (int j = 0; j < coluna; j++) {
            for (int k = 0; k < coluna; k++) {
                matrizR[i][j] += matrizA[i][k] * matrizB[k][j];
            }
        }
    }
    
    pthread_exit(NULL);
}

void multiplica_matriz(int linha, int coluna, int **matrizA, int **matrizB, int **matrizR) {
    int nThreads = 4;
    pthread_t threads[nThreads];
    struct thread_data data[nThreads];
    
    // Divisão das linhas da matriz por threads
    int linhas_por_thread = linha / nThreads;
    int linha_ini = 0;
    
    for (int i = 0; i < nThreads; i++) {
        int linha_fim = linha_ini + linhas_por_thread;
        if (i == (nThreads-1)) linha_fim = linha; // Última thread pega as linhas restantes
        data[i].id = i;
        data[i].linha_ini = linha_ini;
        data[i].linha_fim = linha_fim;
        data[i].coluna = coluna;
        data[i].matrizA = matrizA;
        data[i].matrizB = matrizB;
        data[i].matrizR = matrizR;
        pthread_create(&threads[i], NULL, multiplica_parte_matriz, (void *)&data[i]); //passando como parâmetro os dados necessários para realizara a multiplicação, bem como armazenamento do resultado
        linha_ini = linha_fim;
    }
    
    // Espera que todas as threads terminem a execução
    for (int i = 0; i < nThreads; i++) {
        pthread_join(threads[i], NULL);
    }
}

void preeche_matriz(int linha, int coluna, int **matriz) {
    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            matriz[i][j] = rand()%10 + 1;
        }
        
    } 
}

void imprime_matriz(int linha, int coluna, int **matriz) {
    for (int i = 0; i < linha; i++)
        {
            for (int j = 0; j < coluna; j++)
            {
                cout << matriz[i][j] << " ";
            }
            cout << "" << endl;
        }
}

int main(int argc, char const *argv[])
{
    int linha1 = atoi(argv[1]);
    int coluna1 = atoi(argv[2]);
    int linha2 = atoi(argv[3]);
    int coluna2 = atoi(argv[4]);

    if (coluna1 != linha2)
    {
        cout << "A multiplicação não é possível" << endl;
        return 0;
    }

    int **matriz1 = new int*[linha1];
    int **matriz2 = new int*[linha2];
    int **matrizResultante = new int*[linha2];

    for (int i = 0; i < linha1; i++)
    {
        matriz1[i] = new int[coluna1];
    }
    for (int i = 0; i < linha2; i++)
    {
        matriz2[i] = new int[coluna2];
    }
    for (int i = 0; i < linha2; i++)
    {
        matrizResultante[i] = new int[coluna2];
    }

    preeche_matriz(linha1, coluna1, matriz1);
    preeche_matriz(linha2, coluna2, matriz2);
    
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    multiplica_matriz(linha1, coluna2, matriz1, matriz2, matrizResultante);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout<<"Tempo " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "[ms]" <<endl;
    
    
    return 0;
}