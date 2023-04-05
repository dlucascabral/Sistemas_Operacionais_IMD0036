#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

int main(int argc, char const *argv[])
{
    
    // entrada do tamanho das matrizes via linha de comando

    int mat1_row_size = atoi(argv[1]);
    int mat1_column_size = atoi(argv[2]);
    int mat2_row_size = atoi(argv[3]);
    int mat2_column_size = atoi(argv[4]);
    
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

        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        for (int i = 0; i < matr_row_size; i++)
        {
            mtx_resulting.push_back(vector<int>());
            for (int j = 0; j < matr_column_size; j++)
            {
                mtx_resulting[i].push_back(0);
                for (int k = 0; k < mat1_column_size; k++)
                {
                    mtx_resulting[i][j] += mtx1[i][k] * mtx2[k][j];
                }
                
            }   
        }
        chrono::steady_clock::time_point end = chrono::steady_clock::now();
        int duration_time = chrono::duration_cast<chrono::microseconds>(end-begin).count();

        cout << "Tempo: " << duration_time << "ms" << endl;

        // imprimindo matriz resultante na tela
        // cout << "Matriz resultante" << endl;
        // for (int i = 0; i < matr_row_size; i++)
        // {
        //     for (int j = 0; j < matr_column_size; j++)
        //     {
        //         cout << mtx_resulting[i][j] << " ";
        //     }
        //     cout << "" << endl;
        // }

    }
    
    
    return 0;
}
