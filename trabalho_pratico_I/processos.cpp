#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    
    int n1 = atoi(argv[1]);
    int m1 = atoi(argv[2]);
    int n2 = atoi(argv[3]);
    int m2 = atoi(argv[4]);    
    pid_t pid;
    pid = fork();
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
    return 0;
}