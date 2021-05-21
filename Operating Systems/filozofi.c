#include <signal.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#define BROJ_DRETVI 5
char stanjeFilozofa[BROJ_DRETVI];
bool vilica[BROJ_DRETVI];
bool ponavljaj = true;
pthread_mutex_t M_filozofi;
pthread_cond_t cekaStapice[BROJ_DRETVI];
short ID = 0;

void kraj(int sig){  /* oslobađanje zajedničke memorije */
    ponavljaj = false;
}

void misli(){
    sleep(rand()%3+1);
}

void ispis(short id, char codeword[]){
    for(int i = 0; i < BROJ_DRETVI; i++){
        printf("%c ", stanjeFilozofa[i]);
    }
    printf(" (%hd %s)\n", id, codeword);
}

void jedi(short id){
    pthread_mutex_lock (&M_filozofi);
    stanjeFilozofa[id] = 'o';
    while(!vilica[id] || !vilica[(id+1)%BROJ_DRETVI]){
        pthread_cond_wait (&cekaStapice[id],&M_filozofi);
    }
    vilica[id] = 0;
    vilica[(id+1)%BROJ_DRETVI] = 0;
    stanjeFilozofa[id] = 'X';
    //printf("Dretva %d\n", id);
    ispis(id, "in");
    pthread_mutex_unlock (&M_filozofi);
    sleep(2); //njam-njam
    pthread_mutex_lock (&M_filozofi);
    stanjeFilozofa[id] = 'O';
    vilica[id] = 1;
    vilica[(id+1)%BROJ_DRETVI] = 1;
    pthread_cond_signal (&cekaStapice[id]);
    pthread_cond_signal (&cekaStapice[(id+1)%BROJ_DRETVI]);
    ispis(id, "out");
    pthread_mutex_unlock (&M_filozofi);

}

void *filozof(void *x){
    short id = ID;
    ID++;
    while(ponavljaj){
        //printf("Dretva %d krece u ciklus\n", id);
        misli();
        jedi(id);
    }
}

int main(){
    pthread_t thr_id[BROJ_DRETVI];
    srand(time(NULL));
    sigset(SIGINT, kraj);
    pthread_mutex_init (&M_filozofi, NULL);
    int i;

    for(i = 0; i < BROJ_DRETVI; i++){
        stanjeFilozofa[i] = 'O';
        vilica[i] = 1;
        pthread_cond_init (&cekaStapice[i], NULL);
    }

    for(i = 0; i < BROJ_DRETVI; i++){
        if (pthread_create(&thr_id[i], NULL, filozof, NULL) != 0){
            printf("Greska pri stvaranju dretve!\n");
            exit(1);  
        }
    }

    for(i = 0; i < BROJ_DRETVI; i++){
        pthread_join(thr_id[i], NULL);
    }

    return 0;
}