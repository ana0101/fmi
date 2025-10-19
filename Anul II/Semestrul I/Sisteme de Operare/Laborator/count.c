#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

#define MAX_RESOURCES 5
int available_resources = MAX_RESOURCES ;
pthread_mutex_t mtx ;

int decrease_count(int count) {
	if (available_resources < count) {
		return -1;
	}
	else {
		pthread_mutex_lock(&mtx);
		available_resources -= count;
		pthread_mutex_unlock(&mtx);
	}
	return 0;
}

int increase_count(int count) {
	pthread_mutex_lock(&mtx);
	available_resources += count ;
	pthread_mutex_unlock(&mtx);
	return 0;
}

void *foo(void *res) {
	int count = *(int*)res;
	int ok = -1;
	while (ok == -1) {
		ok = decrease_count(count);
	}
	printf("Got %d resources %d remaining\n", count, available_resources);
	increase_count(count);
	printf("Released %d resources %d remaining\n", count, available_resources);
}

int main() {
	int res[5] = {2, 3, 1, 2, 1};
	pthread_t tid[5];
	
	if (pthread_mutex_init(&mtx, NULL)) {
		perror(NULL);
		return errno ;
	}
	
	for (int i = 0; i < 5; i ++) {
		if (pthread_create(&tid[i], NULL, foo, (void*)(&res[i]))) { 
			perror(NULL);
			return errno;
		}
	}
	
	for (int i = 0; i < 5; i ++) {
		if (pthread_join(tid[i], NULL)) { 
		    perror(NULL);
		    return errno;
		}
	}
	
	pthread_mutex_destroy(&mtx);
	
	return 0;
}
