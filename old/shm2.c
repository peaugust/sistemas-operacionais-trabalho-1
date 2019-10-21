/* The second program is the producer and allows us to enter data for consumers.
 It's very similar to shm1.c and looks like this. */

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

char* accessMusic(char* music) {
    char * field_description = "Music: ";
    char * music_str = (char *) malloc(1 +sizeof(char*) * (strlen(field_description)+ strlen(music)));
    strcpy(music_str, field_description);
    strcat(music_str, music);
    return music_str;
}

char* accessAuthor(char* author) {
    char * field_description = "Author: ";
    char * author_str = (char *) malloc(1 +sizeof(char*) * (strlen(field_description)+ strlen(author)));
    strcpy(author_str, field_description);
    strcat(author_str, author);
    return author_str;
}

char* accessDurationTime(char* duration_time) {
    char * field_description = "Duration: ";
    char * duration_str = (char *) malloc(1 +sizeof(char*) * (strlen(field_description)+ strlen(duration_time)));
    strcpy(duration_str, field_description);
    strcat(duration_str, duration_time);
    return duration_str;
}

char* accessGenre(char* music_genre) {
    char* field_description = "Genre: ";
    char* genre_str = (char *) malloc(1 +sizeof(char*) * (strlen(field_description)+ strlen(music_genre)));
    strcpy(genre_str, field_description);
    strcat(genre_str, music_genre);
    return genre_str;
}

char* makeMusic(musics all_musics, int index){
    char* music = accessMusic(all_musics.array_music[index]);
    char* author = accessAuthor(all_musics.array_author[index]);
    char* final_str = (char *) malloc(1 +sizeof(char*) * (strlen(music)+ strlen(author)));
    strcpy(final_str, music);
    strcat(final_str, author);
    return final_str;
}

int main()
{
    int running = 1;
    void *shared_memory = (void *)0;
    struct shared_use_st *shared_stuff;
    char buffer[BUFSIZ];
    int shmid;
    musics all_musics = initMusics();

    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);

    if (shmid == -1) {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }

    shared_memory = shmat(shmid, (void *)0, 0);
    if (shared_memory == (void *)-1) {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Memory attached at %X\n", (int)shared_memory);

    shared_stuff = (struct shared_use_st *)shared_memory;
    while(running) {
        while(shared_stuff->music_counter == 1) {
            sleep(1);            
            printf("waiting for client...\n");
        }
        
        strncpy(shared_stuff->musics, makeMusic(all_musics, shared_stuff->music_counter), TEXT_SZ);
        shared_stuff->music_counter = 1;

        if (strncmp(buffer, "end", 3) == 0) {
                running = 0;
        }
    }

    if (shmdt(shared_memory) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}