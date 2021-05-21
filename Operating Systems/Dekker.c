#define _XOPEN_SOURCE
#define _XOPEN_SOURCE_EXTENDED
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdatomic.h>
#include <unistd.h>

int N;
int Id; /* identifikacijski broj segmenta */
atomic_int *PRAVO;
atomic_int *ZASTAVICA;
int *A;


void ulaz(int trenutni,int drugi){
    *(ZASTAVICA+trenutni)=1;
    //printf("%d podize svoju zastavicu, ZASTAVICA = [%d,%d]\n", trenutni, *ZASTAVICA, *(ZASTAVICA+1));
    while(*(ZASTAVICA+drugi)!=0){
        if(*PRAVO==drugi){
            *(ZASTAVICA+trenutni)=0;
            while(*PRAVO==drugi){
                ;} //koristan rad
            *(ZASTAVICA+trenutni)=1;
        }
    }
}

void izlaz(int trenutni,int drugi){
    //printf("PRAVO %d -> %d\n",*PRAVO, drugi);
    *PRAVO=drugi;
    *(ZASTAVICA+trenutni)=0;
    //printf("%d smanjuje svoju zastavicu, ZASTAVICA = [%d,%d]\n", trenutni, *ZASTAVICA, *(ZASTAVICA+1));
}

void proc(int id){
    for(int i = 0; i<N; i++){
        ulaz(id, 1-id);
        //sleep(1);
        //printf("Proces %d rad povecava A za 1 u iteracija %d.\n", id, i);
        *A += 1;
        izlaz(id, 1-id);
    };
}

void brisi(int sig){  /* oslobađanje zajedničke memorije */
    (void) shmdt((char *) PRAVO);
    (void) shmctl(Id, IPC_RMID, NULL);
    exit(0);
}

int main(int argc, char *argv[]){
    N = atoi(argv[1]);
    Id = shmget(IPC_PRIVATE, sizeof(atomic_int)*3+sizeof(int), 0600); /* zauzimanje zajedničke memorije */
    if (Id == -1) exit(1);  /* greška - nema zajedničke memorije */
    PRAVO = (atomic_int*) shmat(Id, NULL, 0);
    ZASTAVICA = (atomic_int*)(PRAVO+1);
    A = (int*) (ZASTAVICA+2);
    *A = 0;
    *PRAVO=1;
    *ZASTAVICA = 0;
    *(ZASTAVICA+1) = 0;

    sigset(SIGINT, brisi);  //u slučaju prekida briši memoriju

    switch (fork()){    /* pokretanje paralelnih procesa */
        case 0:
            proc(1);
            exit(0);
        case -1:
            printf("Druga dretva se nije uspjela napraviti :(\n");
            return 1;
        default:
            proc(0);
    }
    wait (NULL);
    printf("%d\n",*A);
    brisi(0);
    return 0;
}