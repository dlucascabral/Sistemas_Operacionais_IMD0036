#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

void matrix_mult(int size, int row, int col, vector<vector<int>> m1, vector<vector<int>> m2, vector<vector<int>> mtx_r) {
    for (int i = 0; i < size; i++)
    {
        mtx_r[row][col] += m1[row][i] * m2[i][col];       
    }
    
}

int main(int argc, char const *argv[])
{
    // multiplicação de matrizes utilizando threads

    // entrada do tamanho das matrizes via linha de comando

    int mat1_row_size = atoi(argv[1]);
    int mat1_column_size = atoi(argv[2]);
    int mat2_row_size = atoi(argv[3]);
    int mat2_column_size = atoi(argv[4]);
    int p = 4; // número de threads, nome da variável definida no escopo do projeto
    
    // verificando se é possível multiplicas as matrizes

    if (mat1_column_size != mat2_row_size)
    {
        cout << "A multiplicação não é possível" << endl;
    }
    else
    {
        cout << "A multiplicação é possível" << endl;

        // criando as matrizes
        vector<vector<int>> mtx1;
        vector<vector<int>> mtx2;

        // preenchendo as matrizes com valores aleatórios

        for (int i = 0; i < mat1_row_size; i++)
        {
            mtx1.push_back(vector<int>());
            for (int j = 0; j < mat1_column_size; j++)
            {
                mtx1[i].push_back(rand() % 100);
            }
            
        }

        for (int i = 0; i < mat2_row_size; i++)
        {
            mtx2.push_back(vector<int>());
            for (int j = 0; j < mat1_column_size; j++)
            {
                mtx2[i].push_back(rand() % 100);
            }
            
        }

        // imprimindo matrizes na tela
        
        // cout << "Matriz 1" << endl;
        // for (int i = 0; i < mat1_row_size; i++)
        // {
        //     for (int j = 0; j < mat1_column_size; j++)
        //     {
        //         cout << mtx1[i][j] << " ";
        //     }
        //     cout << "" << endl;
        // }

        // cout << "Matriz 2" << endl;
        // for (int i = 0; i < mat2_row_size; i++)
        // {
        //     for (int j = 0; j < mat2_column_size; j++)
        //     {
        //         cout << mtx2[i][j] << " ";
        //     }
        //     cout << "" << endl;
        // }

        // multiplicação das matrizes
        int matr_row_size = mat1_row_size;
        int matr_column_size = mat2_column_size;
        vector<vector<int>> mtx_resulting;
        
        for (int i = 0; i < matr_row_size; i++)
        {
            mtx_resulting.push_back(vector<int>());
            for (int j = 0; j < matr_column_size; j++)
            {
                mtx_resulting[i].push_back(0);
            }
            
        }
        
        // imprimindo matriz resultante inicializada
        // cout << "Matriz Resultante" << endl;
        // for (int i = 0; i < matr_row_size; i++)
        // {
        //     for (int j = 0; j < matr_column_size; j++)
        //     {
        //         cout << mtx_resulting[i][j] << " ";
        //     }
        //     cout << "" << endl;
        // }

        // // criando as threads
        // std::thread t1();
        // std::thread t2();
        // std::thread t3();
        // std::thread t4();


        // chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        
        // //IDEIA
        // //UTILIZAR 4 THREADS
        // //CRIAR QUATRO LAÇOS DE REPETIÇÃO
        // //1 PARA CADA THREAD
        // //ONDE CADA THREAD FICARA RESPONSÁVEL PELA EXECUÇÃO DE UMA MULTIPLICAÇÃO LxC

        // chrono::steady_clock::time_point end = chrono::steady_clock::now();
        // int duration_time = chrono::duration_cast<chrono::microseconds>(end-begin).count();

        // cout << "Tempo: " << duration_time << "ms" << endl;

        // // imprimindo matriz resultante na tela
        // // cout << "Matriz resultante" << endl;
        // // for (int i = 0; i < matr_row_size; i++)
        // // {
        // //     for (int j = 0; j < matr_column_size; j++)
        // //     {
        // //         cout << mtx_resulting[i][j] << " ";
        // //     }
        // //     cout << "" << endl;
        // // }

    }
    
    
    return 0;
}
