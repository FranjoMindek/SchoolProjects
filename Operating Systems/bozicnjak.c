#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include <semaphore.h>
#include <unistd.h>

sem_t *S_KO;
sem_t *S_djedBozicnjak; 
sem_t *S_patuljak;  
sem_t *S_sob;
int *brSob;
int *brPatuljak;
int ID;

//sem_wait (sem); i/ili sem_post (sem);
void djedBozicnjak()
{	
	while(1){
		sem_wait(S_djedBozicnjak);
		sem_wait(S_KO);
		printf("Djed Bozicnjak se probudio, na vratima su %d soba i %d patuljka\n", *brSob, *brPatuljak);
		if(*brSob == 10 && *brPatuljak > 0){
			sem_post(S_KO);
			printf("Djed Bozicnjak raznosi pakete\n");
			sleep(2);
			printf("Djed Bozicnjak je raznjeo pakete\n");
			sem_wait(S_KO);
			for(int i = 0; i<10; i++)
				sem_post(S_sob);
			*brSob = 0;
		}
		if(*brSob == 10){
			sem_post(S_KO);
			printf("Djed Bozicnjak hrani sobove\n");
			sleep(2);
			printf("Djed Bozicnjak je nahranio sobove\n");
			sem_wait(S_KO);
		}
		while(*brPatuljak >= 3){
			sem_post(S_KO);
			printf("Djed Bozicnjak konzultira patuljke\n");
			sleep(2);
			printf("Djed Bozicnjak je konzultirao patuljke\n");
			sem_wait(S_KO);
			for(int i = 0; i<3; i++)
				sem_post(S_patuljak);
			*brPatuljak = *brPatuljak - 3;
		}
		sem_post(S_KO);
	}
}

void patuljak(){
    sem_wait(S_KO);
	*brPatuljak = *brPatuljak + 1;
	printf("Patuljak %d stvoren\n", *brPatuljak);
	if(*brPatuljak == 3)
		sem_post(S_djedBozicnjak);
	sem_post(S_KO);
	sem_wait(S_patuljak);
}

void sob(){
    sem_wait(S_KO);
	*brSob = *brSob + 1;
	printf("Sob %d stvoren\n", *brSob);
	if(*brSob == 10)
		sem_post(S_djedBozicnjak);
	sem_post(S_KO);
	sem_wait(S_sob);
}

void brisi(int sig){  /* oslobađanje zajedničke memorije */
    (void) shmdt((char *) S_KO);
    exit(0);
}

int main()
{
	ID = shmget (IPC_PRIVATE, sizeof(sem_t)*4 + sizeof(int)*2, 0600);
	if(ID == -1) exit(1);
	S_KO = (sem_t*) shmat(ID, NULL, 0);
	S_djedBozicnjak = (sem_t*)(S_KO + 1);
	S_patuljak = (sem_t*)(S_djedBozicnjak + 1);
	S_sob = (sem_t*)(S_patuljak + 1);
	brSob = (int*)(S_sob + 1);
	brPatuljak = (int*)(brSob + 1);
	shmctl (ID, IPC_RMID, NULL); //moze odmah ovdje, nakon shmat, ili na kraju nakon shmdt jer IPC_RMID oznacava da segment treba izbrisati nakon sto se zadnji proces odijeli od tog segmenta (detach)
	sem_init (S_KO, 1, 1); 
	sem_init (S_djedBozicnjak, 1, 0);
	sem_init (S_patuljak, 1, 0);
	sem_init (S_sob, 1, 0);
	*brSob = 0;
	*brPatuljak = 0;
	sigset(SIGINT, brisi); //safety
	srand(time(NULL));
	if(fork() == 0){
		//funkcija djedaBozicnjaka
		djedBozicnjak();
		exit(0);
	}
	//posao sjevernog pola
	while(1){
		sleep(rand()%3+1);
		if(rand()%101 > 50 && *brSob != 10){
			//printf("Stvaram soba...\n");
			if(fork() == 0){ //djete
				//funkcija soba
				sob();
				exit(0);
			}
		}
		if(rand()%101 > 50){
			//printf("Stvaram patuljka...\n");
			if(fork() == 0){ //djete
				//funkcija patuljka
				patuljak();
				exit(0);
			}
		}
	}

	sem_destroy (S_KO);
	sem_destroy (S_djedBozicnjak);
	sem_destroy (S_patuljak);
	sem_destroy (S_sob);
	(void) shmdt((char *) S_KO);

	return 0;
}