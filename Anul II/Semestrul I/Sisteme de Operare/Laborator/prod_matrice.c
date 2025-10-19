#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>

int m = 2, p = 3, n = 4;
int a[2][3] = {{1, 2, 3}, {4, 5, 6}};
int b[3][4] = {{2, 1, 3, 5}, {3, 4, 1, 6}, {5, 6, 2, 3}};
int c[2][4];

void *calc_elem(void *ind);

int main(int argc, char *argv[]) {
	pthread_t tid[m*n];
	int ind[m*n][2];
    
    int count = 0;
    for (int i = 0; i < m; i ++) {
    	for (int j = 0; j < n; j ++) {
			ind[count][0] = i;
			ind[count][1] = j;
    		
    		if (pthread_create(&tid[count], NULL, calc_elem, (void*)ind[count])) { 
		        perror(NULL);
		        return errno;
		    }
		    count ++;
		}
	}
    
    count = 0;
    for (int i = 0; i < m; i ++) {
    	for (int j = 0; j < n; j ++) {
    		int *elem;
		    if (pthread_join(tid[count], (void*)&elem)) { 
		        perror(NULL);
		        return errno;
		    }
		    printf("%d ", *elem);
		    count ++;
		    c[i][j] = *elem;
		}
		printf("\n");
	}
    
    return 0;
}

void *calc_elem(void *ind) {
	int i = ((int*)ind)[0];
	int j = ((int*)ind)[1];         
    int *elem = malloc(sizeof(int)); 
    *elem = 0;
    for(int k = 0; k < p; k ++){
    	*elem += a[i][k] * b[k][j];
    }
    pthread_exit((void*)elem);
}
