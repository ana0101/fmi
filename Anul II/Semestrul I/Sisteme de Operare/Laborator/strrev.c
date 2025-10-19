#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

char *sir_invers;
void *inversare(void *sir);

int main(int argc, char *argv[]) {
	pthread_t tid;
	pthread_attr_t attr;
	
	pthread_attr_init(&attr);
	
	if (pthread_create(&tid, &attr, inversare, argv[1])) {
		perror(NULL);
		return errno;
	}
	
	if (pthread_join(tid, NULL)) {
		perror(NULL);
		return errno;
	}
	
	printf("%s\n", sir_invers);
	return 0;
}

void *inversare(void *sir) {
	char *sir_init = (char*)sir;
	int n = strlen(sir_init);
	sir_invers = (char*)malloc((n+1) * sizeof(char));
	
	for (int i = 0; i < n; i ++) {
		sir_invers[i] = sir_init[n-i-1];
	}
	sir_invers[n] = '\0';
	pthread_exit(0);
}
