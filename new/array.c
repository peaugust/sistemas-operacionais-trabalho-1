#include <stdlib.h>
#include <stdio.h>
#include <string.h>


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

int main(){
    musics all_musics = initMusics();
    printf("Nome do(a) autor: %s\n",accessAuthor(all_musics, 0));
    printf("Nome da música: %s\n",accessMusic(all_musics, 0));
    printf("Duração: %s\n",accessDurationTime(all_musics, 0));
    printf("Gênero: %s\n",accessGenre(all_musics, 0));
}