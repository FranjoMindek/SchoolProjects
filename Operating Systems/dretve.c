#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

/*_Atomic*/ int A;
int N;
int M;

void *fjaNeGlavneDretve(void *x){
    for(int i = 0; i<M; i++)
        A++;
}

int main(int argc, char *argv[]){
    N = atoi(argv[1]);
    M = atoi(argv[2]);
    int i;
    pthread_t thr_id[N];
    A = 0;
    for(i = 0; i < N; i++){
        if (pthread_create(&thr_id[i], NULL, fjaNeGlavneDretve, NULL) != 0){
            printf("Greska pri stvaranju dretve!\n");
            exit(1);  
        }
    }
    /* pokretanje dretvi */
    for(i = 0; i < N; i++){
        pthread_join(thr_id[i], NULL);
    }
    printf("A=%d\n",A);

    return 0;
}