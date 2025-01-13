# Relatório

## Processo Pai:
O __processo pai__ é o processo que __chama__ a função _```fork()```_. Após a execução desta função, o processo pai continua a sua execução, mas agora possui uma cópia sua, o __processo filho__. O processo pai __recebe__ como retorno da função _```fork()```_ o PID _(Process ID)_ do processo filho. Fazendo assim com que seja possível identificá-lo e interagir com o mesmo.

## Processo Filho:
O __processo filho__ é uma __cópia quase idêntica__ do processo pai, criada pela função _```fork()```_. Embora compartilhem o mesmo código, o processo filho possui o seu próprio espaço de memória e um __PID único__, o que o torna __independente__. O retorno da função _```fork()```_ do __processo filho__ é sempre __0__ de maneira a que seja possível diferenciar a execução deste processo da execução do processo pai.

## Função _fork()_:
Um processo pode criar uma cópia sua, através da chamada de sistema _```fork()```_. O novo processo (Processo filho), consiste num elemento completamente independente do processo que o criou (Processo pai). Apesar de serem independentes, ambos os processos têm os mesmos recursos associados, mas alocados em diferentes regiões de memória.

__Sabemos que:__
- Apesar do processo filho ser uma cópia do processo pai, ele possui o seu próprio PID (_Process ID_).
- O processo pai não transmite para o processo filho qualquer bloqueio de memória, ou sinais pendentes.

__Quando executada com sucesso, a função _```fork()```_ retorna:__
- __No processo pai:__ o PID do processo filho; -1 em caso de erro;
- __No processo filho:__ 0 (zero).


## _Threads_

### O que é um _thread_?
Um _thread_ é uma ferramenta que permite a execução de tarefas em simultâneo dentro de um processo, sendo ideal para aplicações que requerem processamento paralelo. São utilizados para melhorar a eficiência e a responsividade de programas em sistemas _multi-core_.

### _Threads_ num programa
- Em um programa _single-thread_, há apenas um fluxo de execução, e todas as instruções são processadas sequencialmente.
- Em um programa _multi-thread_, múltiplos _threads_ podem executar ao mesmo tempo, aumentando a eficiência e a responsividade do programa.

### Secções Críticas
Constitui uma sequência de instruções que não pode ser acedida em simultâneo por mais que um _thread_. As secções críticas devem ser protegidas para que tal não aconteça. Existem quando, por exemplo, um _thread_ A e um _thread_ B tentam aceder simultaneamente a uma variável partilhada (ou espaço de memória).

### Como proteger uma secção crítica?
Existem diferentes mecanismos de sincronização que asseguram que apenas uma unidade de execução possa aceder à secção crítica de cada vez.

## _Mutex_
___Mutex___ (___Mutual Exclusion___, ou __Exclusão Mútua__) é um dos mecanismos acima mencionados. O _mutex_ funciona como uma espécie de __"cadeado"__, ou seja, quando um _thread_ pretende entrar numa secção crítica, este deve bloquear o _mutex_ antes de aceder ao recurso, para que desta forma, se outro _thread_ tentar aceder a este recurso o _mutex_ não o permitir.

### Estados do _Mutex_
O ___mutex___ tem apenas dois estados:
- __Desbloqueado (_Unlocked_):__ O recurso protegido pelo _mutex_ está livre para ser acedido.

- __Bloqueado (_Locked_):__ O recurso está em uso e outros threads necessitam de aguardar que o _mutex_ seja desbloqueado.

### Como funciona o _lock_ e o _unlock_?
__Bloquear (_lock_):__
- O _thread_ solicita o bloqueio do _mutex_ antes de entrar na secção crítica.
- Se o _mutex_ já se encontrar bloqueado, o _thread_ será colocado em espera até que o _mutex_ seja desbloqueado.

__Desbloquear (_unlock_):__ 
- Após terminar o acesso ao recurso, o _thread_ desbloqueia o _mutex_, permitindo assim que outros _thread_ acessem o recurso.


## Enunciado

### Objetivo:
Desenvolva um sistema, em linguagem C, que utilize a chamada de sistema ```fork()``` para criação de processos e a biblioteca _Pthreads_ para criação de _threads_. Este sistema deverá simular o controlo de sensores de temperatura e humidade, realizando a leitura simultânea desses sensores e tomando decisões com base nos dados recolhidos.

## Código

### Sumário da estrutura do código

(INCOMPLETO)

vai executar a leitura de um sensor e faz a escrita num buffer partilhado e quando este buffer é acessado tem de estar protegido

(RASCUNHO)