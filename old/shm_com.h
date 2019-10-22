/* A common header file to describe the shared memory we wish to pass about. */

#define TEXT_SZ 2048

struct shared_use_st {
    int music_counter;
    char musics[100][TEXT_SZ];
};

