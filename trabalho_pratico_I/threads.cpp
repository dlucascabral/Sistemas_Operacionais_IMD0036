#include <pthread.h>
#include <iostream>
#include <chrono>

#define NTHREADS 4

using namespace std;

// int contador = 1;

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

void multiplica_matriz(int linha, int coluna, int **matrizA, int **matrizB, int **matrizR) {
    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            for (int k = 0; k < coluna; k++)
            {
                matrizR[i][j] += matrizA[i][k] * matrizB[k][j];
            }
            
        }
        
    }
}

void preeche_matriz(int linha, int coluna, int **matriz) {
    for (int i = 0; i < linha; i++)
    {
        for (int j = 0; j < coluna; j++)
        {
            // matriz[i][j] = contador++;
            matriz[i][j] = rand()%10 + 1;
        }
        
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

    preeche_matriz(linha1, coluna2, matriz1);
    preeche_matriz(linha1, coluna2, matriz2);
    // cout << "Matriz 1" << endl;
    // imprime_matriz(linha1, coluna2, matriz1);
    // cout << "" << endl;
    // cout << "Matriz 2" << endl;
    // imprime_matriz(linha1, coluna2, matriz2);
    // cout << "" << endl;
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    multiplica_matriz(linha1, coluna2, matriz1, matriz2, matrizResultante);
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout<<"Tempo " << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "[ms]" <<endl;
    // cout << "Matriz resultante" << endl;
    // imprime_matriz(linha1, coluna2, matrizResultante);
    
    
    return 0;
}
