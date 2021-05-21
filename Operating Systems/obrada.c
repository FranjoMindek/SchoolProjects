#include <stdio.h>
#include <signal.h>

#define N 6    /* broj razina proriteta */

int OZNAKA_CEKANJA[N];
int PRIORITET[N];
int TEKUCI_PRIORITET;
 
int sig[]={SIGUSR1, SIGUSR2, SIGCONT, SIGTERM, SIGINT};

void zabrani_prekidanje(){
   int i;
   for(i=0; i<5; i++)
      sighold(sig[i]);
}

void dozvoli_prekidanje(){
   int i;
   for(i=0; i<5; i++)
      sigrelse(sig[i]);
}

void obrada_prekida(int i){
    switch(i){
        case 1: 
            printf(" -  P  -  -  -  -\n");
            break;
        case 2: 
            printf(" -  -  P  -  -  -\n");
            break;
        case 3: 
            printf(" -  -  -  P  -  -\n");
            break;
        case 4: 
            printf(" -  -  -  -  P  -\n");
            break;
        case 5: 
            printf(" -  -  -  -  -  P\n");
            break;
    }
    for(int j = 1; j<=5; j++){
        sleep(1);
        switch(i){
        case 1: 
            printf(" -  %d  -  -  -  -\n", j);
            break;
        case 2: 
            printf(" -  -  %d  -  -  -\n", j);
            break;
        case 3: 
            printf(" -  -  -  %d  -  -\n", j);
            break;
        case 4: 
            printf(" -  -  -  -  %d  -\n", j);
            break;
        case 5: 
            printf(" -  -  -  -  -  %d\n", j);
            break;
        }
    }
    switch(i){
        case 1: 
            printf(" -  K  -  -  -  -\n");
            break;
        case 2: 
            printf(" -  -  K  -  -  -\n");
            break;
        case 3: 
            printf(" -  -  -  K  -  -\n");
            break;
        case 4: 
            printf(" -  -  -  -  K  -\n");
            break;
        case 5: 
            printf(" -  -  -  -  -  K\n");
            break;
    }
}

void prekidna_rutina(int sig){
   int n=-1;
   zabrani_prekidanje();
   switch(sig){
        case SIGUSR1: 
            n=1; 
            printf(" -  X  -  -  -  -\n");
            break;
        case SIGUSR2: 
            n=2; 
            printf(" -  -  X  -  -  -\n");
            break;
        case SIGCONT: 
            n=3; 
            printf(" -  -  -  X  -  -\n");
            break;
        case SIGTERM: 
            n=4; 
            printf(" -  -  -  -  X  -\n");
            break;
        case SIGINT: 
            n=5; 
            printf(" -  -  -  -  -  X\n");
            break;
   }

    OZNAKA_CEKANJA[n]=1;
    int x;
    do{
        x = 0;
        for(int j=TEKUCI_PRIORITET+1; j<N; j++)
            if (OZNAKA_CEKANJA[j]!=0)
                x=j;
        if(x > 0) {
            OZNAKA_CEKANJA[x] = 0;
            PRIORITET[x] = TEKUCI_PRIORITET;
            TEKUCI_PRIORITET = x;
            dozvoli_prekidanje();
            obrada_prekida(x);
            zabrani_prekidanje();
            TEKUCI_PRIORITET = PRIORITET[x];
        }
   }while(x > 0);
   dozvoli_prekidanje();
}

int main ( void )
{
   sigset (SIGUSR1, prekidna_rutina);
   sigset (SIGUSR2, prekidna_rutina);
   sigset (SIGCONT, prekidna_rutina);
   sigset (SIGTERM, prekidna_rutina);
   sigset (SIGINT, prekidna_rutina);
   
   printf("Proces obrade prekida, PID=%d\n", getpid());
   printf("GP S1 S2 S3 S4 S5\n");
   printf("-----------------\n");
   for(int p = 1; p<=10; p++){
        sleep(1);
        printf("%2d  -  -  -  -  -\n", p);
   }
   printf ("Zavrsio osnovni program\n");
   return 0;
}

