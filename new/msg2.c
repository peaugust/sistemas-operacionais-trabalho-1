/* The sender program is very similar to msg1.c. In the main set up, delete the
 msg_to_receive declaration and replace it with buffer[BUFSIZ], remove the message
 queue delete and make the following changes to the running loop.
 We now have a call to msgsnd to send the entered text to the queue. */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>

#include <sys/msg.h>

struct musics {
    char array_music[10][80] = {"Alone", "A Luz de Tieta", "Don't Stop Me Now", "Instant Crush", "Imagination", "The Pretender", "Super Fantastico"};
    char array_author[10][80] = {"Halsey", "Caetano Veloso", "Queen", "Daft Punk", "Foster The People", "Foo Fighters", "Balao Magico"};
    char array_duration_time[10][10] = {"3:25", "4:26", "3:37", "5:39", "4:17", "4:30", "3:13"};
    char array_genre[10][80] = {"Pop", "MPB", "Rock", "House", "Indie Pop", "Alternative Rock", "Infantil"};
}

char[] accessMusics(int musicsIndex) {
    char musicString [200] = {"Autor: ", musics.array_music[musicsIndex]}
}

#define MAX_TEXT 512

struct my_msg_st {
    long int my_msg_type;
    char some_text[MAX_TEXT];
};

int main()
{
    int musicsIndex = 0;
    int running = 1;
    struct my_msg_st some_data;
    int msgid;
    char buffer[BUFSIZ];

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);

    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error: %d\n", errno);
        exit(EXIT_FAILURE);
    }

    while(running) {
        printf("Enter some text: ");
        fgets(buffer, BUFSIZ, stdin);
        some_data.my_msg_type = 1;
        strcpy(some_data.some_text, buffer);

        if (msgsnd(msgid, (void *)&some_data, MAX_TEXT, 0) == -1) {
            fprintf(stderr, "msgsnd failed\n");
            exit(EXIT_FAILURE);
        }
        if (strncmp(buffer, "end", 3) == 0) {
            running = 0;
        }
    }

    exit(EXIT_SUCCESS);
}
