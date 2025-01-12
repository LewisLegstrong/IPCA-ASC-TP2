#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int pid_filho;                                  // Identificador do processo filho
    int pid_filho2;
    pid_filho = fork();                             // Replicação do processo
    
    if(pid_filho < 0) {                             // Se o fork() retornou erro
        perror("Error: ");
        return -1;
    }
    else if(pid_filho > 0) {                        // Se é o processo pai
        pid_filho2 = fork();                        // Replicação do processo
        if(pid_filho2 < 0) {                        // Se o fork() retornou erro
            perror("Error: ");
            return -1;
        }
        else if(pid_filho2 > 0) {                   // Se é o processo pai
            wait(0);                                // Aguarda até que o filho conclua a sua execução
        }
        else {
            printf("Son 2");                   // Executa o programa no processo filho 2
        }
        wait(0);
    }
    else {
        printf("Son 1");                   // Executa o programa no processo filho 1
    }


    // // Mensagem exibida pelo processo pai, no final da execução
    printf("Exit\n");
    return 0;
}