#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

pthread_mutex_t mtx;
sem_t sem;
int N = 5;
int cnt;

void barrier_point() {
	pthread_mutex_lock(&mtx);
	cnt --;
	pthread_mutex_unlock(&mtx);
	
	if (sem_wait(&sem)) {
		perror(NULL);
		return errno;
	}
	
	while (cnt > 0) {
	}
	
	if (sem_post(&sem)) {
		perror(NULL);
		return errno;
	}
}

void *tfun(void *v) {
	int *tid = (int*)v;
	printf("%d reached the barrier\n", *tid);
	barrier_point();
	printf("%d passed the barrier\n", *tid);
	return NULL;
}

int main() {
	if (pthread_mutex_init(&mtx, NULL)) {
		perror(NULL);
		return errno;
	}
	if (sem_init(&sem, 0, N)) {
		perror(NULL);
		return errno;
	}
	cnt = N;
	
	pthread_t tid[N];
	int ind[N];
	
	for (int i = 0; i < N; i ++) {
		ind[i] = i;
	}
	
	for (int i = 0; i < N; i ++) {
		if (pthread_create(&tid[i], NULL, tfun, (void*)(&ind[i]))) { 
			perror(NULL);
			return errno;
		}
	}
	
	for (int i = 0; i < N; i ++) {
		if (pthread_join(tid[i], NULL)) { 
		    perror(NULL);
		    return errno;
		}
	}
	
	pthread_mutex_destroy(&mtx);
	sem_destroy(&sem);
	
	return 0;
}
