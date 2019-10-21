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

int main(){
    musics all_musics = initMusics();
    int index = 0;
    for(index; index < 7; index++){
        printf("%s\n", accessMusic(all_musics, index));
        printf("%s\n", accessAuthor(all_musics, index));
        printf("%s\n", accessDurationTime(all_musics, index));
        printf("%s\n", accessGenre(all_musics, index));
        printf("\n");
    }
}