# Relatório

## Processo Pai:
---

## Processo Filho:
---

## Função fork():
- Permite que um processo crie uma cópia sua, através da chamada de sistema ```fork()```.
- O novo processo (Processo filho), consiste num elemento completamente independente do processo que o criou (Processo pai).
- Ambos os processos têm os mesmos recursos associados, embora em diferentes regiões de memória.

__Sabemos que:__
- Apesar do processo filho ser uma cópia do processo pai, ele possui o seu próprio PID (_Process ID_).
- O processo pai não transmite para o processo filho qualquer bloqueio de memória, ou sinais pendentes.
- O processo filho, quando iniciado, inicia a zero os contadores de recursos ```getrusage()``` e ```times()```.

__Quando executada com sucesso, a função ```fork()``` retorna:__
- No processo pai: o PID do processo filho; -1 em caso de erro;
- No processo filho: 0 (zero).

Em determinadas situações poderá ser útil a uma aplicação efetuar a leitura/verificação do seu próprio PID, ou obter do PID do processo que a gerou (Processo pai). As funções ```getpid()``` e ```getppid()``` retornam, respetivamente, o PID do próprio processo, e o PID do processo pai.

```c 
#include <sys/types.h>
#include <unistd.h>
pid_t getpid(void);
pid_t getppid(void);
```

Quando o processo “lança” um novo processo, este processo filho fica ligado ao processo pai. Este tipo de dependência gera uma árvore de processos de sistema, onde é visível a relação entre os processos em execução. Quando um processo termina a sua execução, todos os processos filhos são notificados desse evento. Caberá a cada um decidir se deve encerrar ou prosseguir com a execução. O comando ```pstree``` permite visualizar essa hierarquia.

## Threads

### O que é um thread?


### Threads num programa
- Em um programa single-thread, há apenas um fluxo de execução, e todas as instruções são processadas sequencialmente.
- Em um programa multi-thread, múltiplos threads podem executar ao mesmo tempo, aumentando a eficiência e a responsividade do programa.

### Secções Críticas
Constitui uma sequência de instruções que não pode ser acedida em simultâneo por mais que um thread. As secções críticas devem ser protegidas para que tal não aconteça. Existem quando, por exemplo, um thread A e um thread B tentam aceder simultaneamente a uma variável partilhada (ou espaço de memória).

### Como proteger uma secção crítica?
Existem diferentes mecanismos de sincronização que asseguram que apenas uma unidade de execução possa aceder à secção crítica de cada vez.

## Mutex

## Semáforos

## Variáveis de condição

## Monitores






--------------------------------------------


## Enunciado

### Objetivo:
Desenvolva um sistema, em linguagem C, que utilize a chamada de sistema fork() para criação de processos e a biblioteca Pthreads para criação de threads. Este sistema deverá simular o controlo de sensores de temperatura e humidade, realizando a leitura simultânea desses sensores e tomando
decisões com base nos dados recolhidos

## Código

### Sumário da estrutura do código

(INCOMPLETO)

vai executar a leitura de um sensor e faz a escrita num buffer partilhado e quando este buffer é acessado tem de estar protegido

(RASCUNHO)

