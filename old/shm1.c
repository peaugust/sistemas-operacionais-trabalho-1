/* Our first program is a consumer. After the headers the shared memory segment
 (the size of our shared memory structure) is created with a call to shmget,
 with the IPC_CREAT bit specified. */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/shm.h>

#include "shm_com.h"

typedef struct musics {
    char array_music[10][80];
    char array_author[10][300];
    char array_duration_time[10][10];
    char array_genre[10][80];
} musics;

musics initMusics() {
    musics all_musics = {
        {"Alone\n", "A Luz de Tieta\n", "Don't Stop Me Now\n", "Instant Crush\n", "Imagination\n", "The Pretender\n", "Super Fantastico\n"},
        {"Halsey\n", "Caetano Veloso\n", "Queen\n", "Daft Punk\n", "Foster The People\n", "Foo Fighters\n", "Balao Magico\n"},
        {"3:25\n", "4:26\n", "3:37\n", "5:39\n", "4:17\n", "4:30\n", "3:13\n"},
        {"Pop\n", "MPB\n", "Rock\n", "House\n", "Indie Pop\n", "Alternative Rock\n", "Infantil\n"},
    };

    return all_musics;
}

char* accessMusic(musics all_musics, int index) {
    char * field_description = "Music: ";
    char * music_name = (char *) all_musics.array_music[index];
    char * music_str = (char *) malloc(1 +sizeof(char*) * (strlen(field_description)+ strlen(music_name)));
    strcpy(music_str, field_description);
    strcat(music_str, music_name);
    return music_str;
}

char* accessAuthor(musics all_musics, int index) {
    char * field_description = "Author: ";
    char * author_name = (char *) all_musics.array_author[index];
    char * author_str = (char *) malloc(1 +sizeof(char*) * (strlen(field_description)+ strlen(author_name)));
    strcpy(author_str, field_description);
    strcat(author_str, author_name);
    return author_str;
}

char* accessDurationTime(musics all_musics, int index) {
    char * field_description = "Duration: ";
    char * duration_time = (char *) all_musics.array_duration_time[index];
    char * duration_str = (char *) malloc(1 +sizeof(char*) * (strlen(field_description)+ strlen(duration_time)));
    strcpy(duration_str, field_description);
    strcat(duration_str, duration_time);
    return duration_str;
}

char* accessGenre(musics all_musics, int index) {
    char * field_description = "Genre: ";
    char * music_genre = (char *) all_musics.array_genre[index];
    char * genre_str = (char *) malloc(1 +sizeof(char*) * (strlen(field_description)+ strlen(music_genre)));
    strcpy(genre_str, field_description);
    strcat(genre_str, music_genre);
    return genre_str;
}


int main()
{
    musics all_musics = initMusics();
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
    shared_stuff->music_counter = 0;
    strcpy(shared_stuff->musics, accessMusic(all_musics, shared_stuff->music_counter));
    while(running) {
        if (shared_stuff->music_counter) {
            printf("Insere a musica de nome: %s\n");
            printf("%s\n", shared_stuff->musics);
            sleep( rand() % 4 ); /* make the other process wait for us ! */
            shared_stuff->music_counter = 0;
            if (strncmp(shared_stuff->musics, "end", 3) == 0) {
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

