/* The sender program is very similar to msg1.c. In the main set up, delete the
 msg_to_receive declaration and replace it with buffer[BUFSIZ], remove the message
 queue delete and make the following changes to the running loop.
 We now have a call to msgsnd to send the entered text to the queue. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <sys/msg.h>

#define MAX_TEXT 512

struct my_msg_st {
    long int my_msg_type;
    char some_text[MAX_TEXT];
};

typedef struct musics {
    char array_music[10][80];
    char array_author[10][300];
    char array_duration_time[10][10];
    char array_genre[10][80];
} musics;

musics initMusics() {
    musics all_musics = {
        {"Alone", "A Luz de Tieta", "Don't Stop Me Now", "Instant Crush", "Imagination", "The Pretender", "Super Fantastico"},
        {"Halsey", "Caetano Veloso", "Queen", "Daft Punk", "Foster The People", "Foo Fighters", "Balao Magico"},
        {"3:25", "4:26", "3:37", "5:39", "4:17", "4:30", "3:13"},
        {"Pop", "MPB", "Rock", "House", "Indie Pop", "Alternative Rock", "Infantil"},
    };

    return all_musics;
}

char* accessAuthor(musics all_musics, int index) {
    char* author = all_musics.array_author[index];
    return author;
}

char* accessMusic(musics all_musics, int index) {
    char* music = all_musics.array_music[index];
    return music;
}

char* accessDurationTime(musics all_musics, int index) {
    char* duration = all_musics.array_duration_time[index];
    return duration;
}

char* accessGenre(musics all_musics, int index) {
    char* genre = all_musics.array_genre[index];
    return genre;
}

int main()
{
    int running = 1;
    musics all_musics = initMusics();
    struct my_msg_st some_data;
    int msgid;
    char buffer[BUFSIZ];

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    while(running) {
        some_data.my_msg_type = 1;
        if(musicsIndex > 5){
           exit(EXIT_SUCCESS);
        }
        strcpy(some_data.some_text, all_musics.array_author[musicsIndex]);

        if (msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) == -1) {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
        if (strncmp(buffer, "end", 3) == 0) {
            running = 0;
        }
        musicsIndex++;
    }

    exit(EXIT_SUCCESS);
}
