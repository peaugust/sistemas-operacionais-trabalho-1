/* Criacao de semaforo com a funcao semget, que retorna o ID do semaforo.
Este exemplo eh baseado no livro Beginning Linux Programming (Neil Matthew e Richard Stones)
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/sem.h>
#include "semun.h"

static int set_semvalue(void);
static void del_semvalue(void);
static int semaphore_p(void);   // para esperar pelo acesso
static int semaphore_v(void);   // para liberar o acesso

static int sem_id;

int main(int argc, char *argv[])
{
    int i;
    int pause_time;
    char op_char = 'O';

    srand((unsigned int)getpid());

// cria um novo semaforo ou obtem o semaforo para a chave especificada (caso ja exista)
// key: identificador do semaforo,
// num_sems: numero de semaforos solicitados (normalmente 1),
// flags: semelhante a abertura de arquivos (666 permite leitura e escrita).
// IPC_CREAT pode ser usada para garantir que sera criado um novo semaforo
// ou a funcao retornara um erro, caso o semafor ja exista
    sem_id = semget((key_t)1234, 1, 0666 | IPC_CREAT);

    if (argc > 1) {
        if (!set_semvalue()) {
            fprintf(stderr, "Falha ao inicializar o semaforo\n");
            exit(EXIT_FAILURE);
        }
        op_char = 'X';
        sleep(2);
    }

/* Este laco entra e sai da regiao critica 10 vezes.
 semaphore_p aguarda no semaforo ate que possa entrar na regiao critica
 */
    for(i = 0; i < 10; i++) {

        if (!semaphore_p())
            exit(EXIT_FAILURE);
        printf("%c", op_char);
        fflush(stdout);
        pause_time = rand() % 3;
        sleep(pause_time);
        printf("%c", op_char);
        fflush(stdout);

/*
Apos a regiao critica, eh chamado semaphore_v, liberando o semaforo.
*/
        if (!semaphore_v())
            exit(EXIT_FAILURE);

        pause_time = rand() % 2;
        sleep(pause_time);
    }

    printf("Processo \n%d finalizado\n", getpid());

// del_semvalue eh chamado para remover o semaforo
    if (argc > 1) {
        sleep(10);
        del_semvalue();
    }
    exit(EXIT_SUCCESS);
}

/*
set_semvalue inicializa o semaforo usando o comando SETVAL em uma chamada semctl.
*/

static int set_semvalue(void)
{
    union semun sem_union;
    sem_union.val = 1;
    if (semctl(sem_id, 0, SETVAL, sem_union) == -1)
        return(0);
    return(1);
}

/* del_semvalue remove o semaforo com identificador ID. Tambem usa semctl, mas
   o comando IPC_RMID remove o semaforo. */

static void del_semvalue(void)
{
    union semun sem_union;

    if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
        fprintf(stderr, "Falha ao remover o semaforo\n");
}

/* semaphore_p muda o semaforo para -1 (esperando). */

static int semaphore_p(void)
{
    struct sembuf sem_b;

    sem_b.sem_num = 0;
    sem_b.sem_op = -1; /* P() */
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1) {
        fprintf(stderr, "semaphore_p falhou\n");
        return(0);
    }
    return(1);
}

/* semaphore_v torna o semaforo disponivel, atribuindo 1 para a parte sem_op do buffer
   (estrutura sembuf),
*/

static int semaphore_v(void)
{
    struct sembuf sem_b;

    sem_b.sem_num = 0;
    sem_b.sem_op = 1; /* V() */
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1) {
        fprintf(stderr, "semaphore_v falhou\n");
        return(0);
    }
    return(1);
}
