/* Our first program is a consumer. After the headers the shared memory segment
 (the size of our shared memory structure) is created with a call to shmget,
 with the IPC_CREAT bit specified. */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/shm.h>

#include "shm_com.h"

int main()
{
    int running = 1;
    void *shared_memory = (void *)0;
    struct shared_use_st *shared_stuff;
    int shmid;

    srand((unsigned int)getpid());    

    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);

    if (shmid == -1) {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }

/* We now make the shared memory accessible to the program. */

    shared_memory = shmat(shmid, (void *)0, 0);
    if (shared_memory == (void *)-1) {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Memory attached at %X\n", (int)shared_memory);

/* The next portion of the program assigns the shared_memory segment to shared_stuff,
 which then prints out any text in music_counter. The loop continues until end is found
 in music_counter. The call to sleep forces the consumer to sit in its critical section,
 which makes the producer wait. */

    shared_stuff = (struct shared_use_st *)shared_memory;
    // strcpy(shared_stuff->musics, accessMusic(all_musics, shared_stuff->music_counter));
    while(running) {
        int array_size = sizeof(shared_stuff)/sizeof(int);
        if (shared_stuff->music_counter == 1) {
            for(int i = 0; i < array_size; i++) {
                if(strlen(shared_stuff->musics[i]) > 2){
                    printf("Insere a musica de nome: %s\n");
                    printf("%s\n", shared_stuff->musics[i]);
                    strcpy(shared_stuff->musics[i], "");
                    i = array_size;
                }
            }
            sleep( rand() % 4 ); /* make the other process wait for us ! */
            // printf("Insere a musica de nome: %s\n");
            // printf("%s\n", shared_stuff->musics);
            // sleep( rand() % 4 ); /* make the other process wait for us ! */
            shared_stuff->music_counter = 0;
            if (strncmp(shared_stuff->musics[0], "end", 3) == 0) {
                running = 0;
            }
        }
    }

/* Lastly, the shared memory is detached and then deleted. */

    if (shmdt(shared_memory) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}

