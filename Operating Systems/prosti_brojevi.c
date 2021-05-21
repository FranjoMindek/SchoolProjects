#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<math.h>
#include<stdlib.h>
#include <sys/time.h>


int pauza = 0;
unsigned long broj = 1000000001;
unsigned long zadnji = 1000000001;


int prost ( unsigned long n ) {
	unsigned long i, max;
	if ((n&1) == 0) /* je li paran? */
		return 0;
	max = sqrt(n);
	for(i=3; i <= max; i+=2)
		if((n%i) == 0)
			return 0;
	return 1; /* broj je prost! */
}

void postavi_pauzu () {
	pauza = 1-pauza;
}

void periodicki_ispis () {
	printf("%ld\n", zadnji);
}

void prekini () {
	printf("%ld\n", zadnji);
	exit(0);
}

int main() {
	printf("Poceo osnovni program PID=%d\n", getpid());
	sigset (SIGINT, postavi_pauzu);
	sigset (SIGTERM, prekini);
	sigset (SIGALRM, periodicki_ispis);
	struct itimerval t;
	t.it_value.tv_sec = 5;
	t.it_value.tv_usec = 0;
	t.it_interval.tv_sec = 5;
	t.it_interval.tv_usec = 0;
	setitimer ( ITIMER_REAL, &t, NULL );

	while(1){
		if(prost(broj))
			zadnji = broj;
		broj++;
		while(pauza == 1){
			pause();
		}
	}
	return 0;
}

