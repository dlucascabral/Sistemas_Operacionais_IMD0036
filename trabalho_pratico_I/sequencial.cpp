#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
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
    }
    
    
    return 0;
}
