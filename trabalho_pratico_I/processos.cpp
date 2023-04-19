#include <iostream>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <chrono>

using namespace std;

int main(int argc, char *argv[]){
    
    int n1 = atoi(argv[1]);
    int m1 = atoi(argv[2]);
    int n2 = atoi(argv[3]);
    int m2 = atoi(argv[4]);    
    pid_t pid;
    pid = fork();
   chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    if (pid<0)
    {
        printf("Erro ao criar processo \n");
        return 1;
    }
    
    else if (pid==0)
    {
        printf("Esta é a execução do filho(PID=%d), cujo pai tem PID=%d\n", getpid(),getppid());
        sleep(3);
    } 
    else{
        wait(NULL);
        printf("Processo-Filho finalizou\n");
    }
    chrono::steady_clock::time_point end = chrono::steady_clock::now();
    cout<<"Tempo" << chrono::duration_cast<chrono::milliseconds>(end - begin).count() << "[ms]" <<endl;
    return 0;
}