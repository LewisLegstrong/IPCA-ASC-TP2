# Processo Pai:
---

# Processo Filho:
---

# Função fork():
- Permite que um processo crie uma cópia sua, através da chamada de sistema ```fork()```.
- O novo processo (Processo filho), consiste num elemento completamente independente do processo que o criou (Processo pai).
- Ambos os processos têm os mesmos recursos associados, embora em diferentes regiões de memória. Se se pretender que o processo filho execute um outro código, distinto do que “herdou” do processo pai, deve-se invocar a chamada de sistema execve().
- Esta função substitui o código do processo, pelo código executável contido na aplicação definida como parâmetro.

A duplicação de um processo é realizada pela função fork(), definida no _header_ file ```<unistd.h>```, como:

```c 
pid_t fork(void);
```

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

Quando o processo “lança” um novo processo, este processo filho fica ligado ao processo pai. Este tipo de dependência gera uma árvore de processos de sistema, onde é visível a relação entre os
processos em execução. Quando um processo termina a sua execução, todos os processos filhos são notificados desse evento. Caberá a cada um decidir se deve encerrar ou prosseguir com a execução.
O comando ```pstree``` permite visualizar essa hierarquia.

## Threads
Um thread consiste numa unidade básica de utilização de CPU (ou core), constituído por:
- Thread ID;
- Registos e stack (variáveis locais) própria;
- Program Counter (PC) e Stack Pointer (SP);
- Máscara de sinais (sigthreadmask);
- Prioridade;
- Valor de retorno.

Os threads de um mesmo processo, partilham:
- Instruções;
- Dados globais;
- Heap;
- “Descriptores” de ficheiros abertos;
- Sinais e gerenciadores de sinais (signal handlers – sigaction);
- Diretório de trabalho.

Um thread não mantém uma lista dos threads criados, nem possui qualquer informação sobre o thread que o criou.

A implementação de threads, em várias linguagens, suportam operações de:
- Criação e encerramento de threads;
- Sincronização (_join_ e bloqueio);
- Escalonamento;
- Gestão de dados e interação com o processo.
