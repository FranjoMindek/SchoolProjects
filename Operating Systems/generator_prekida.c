#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>

int pid=0;

void prekidna_rutina(int sig){
   kill(pid, SIGKILL);
   exit(0);
}

int main(int argc, char *argv[]){
   pid=atoi(argv[1]);
   sigset(SIGINT, prekidna_rutina);
   srand(time(NULL));   
   while(1){
       int r;
       r =rand()%3 + 3;
       //printf("slip %d\n", r);
       sleep(r);
       r = rand()%4;
       //printf("sig %d\n", r);
       switch (r)
       {
       case 0:
           kill(pid, SIGUSR1);
           break;
       case 1:
           kill(pid, SIGUSR2);
           break;
       case 2:
           kill(pid, SIGCONT);
           break;
       case 3:
           kill(pid, SIGTERM);
           break;       
       }  
   }
   return 0;
}