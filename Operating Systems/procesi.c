#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

int Id; /* identifikacijski broj segmenta */
int N;
int M;
/*_Atomic*/ int *A;

void fjaDjeteta(){
    for(int i = 0; i<M; i++)
        *A += 1;
}

void brisi(int sig){
    /* oslobađanje zajedničke memorije */
    (void) shmdt((char *) A);
    (void) shmctl(Id, IPC_RMID, NULL);
    exit(0);
}

int main(int argc, char *argv[]){
    N = atoi(argv[1]);
    M = atoi(argv[2]);
    /* zauzimanje zajedničke memorije */
    Id = shmget(IPC_PRIVATE, sizeof(int), 0600);
    if (Id == -1) exit(1);  /* greška - nema zajedničke memorije */
    A = (int *) shmat(Id, NULL, 0);
    *A = 0;
    sigset(SIGINT, brisi);//u slučaju prekida briši memoriju
    /* pokretanje paralelnih procesa */
    int i;
    for(i = 0; i < N; i++){
        switch (fork()){
        case 0:
            fjaDjeteta();
            exit(0);
        case -1:
            printf("Dretva %d se nije uspjela napraviti :(\n", i);
        default:
            break;
        }
    }
    while (i--) wait (NULL);
    printf("A=%d\n",*A);

    brisi(0);
    return 0;
}