#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main (int argc, char *argv[]) {
	int nr = argc;
	
	for (int i = 0; i < nr; i ++) {
		pid_t pid = fork();
	
		if (pid < 0) {
			return errno;
		}
		else if (pid == 0) {
			// child
			// generate collatz
			char *a = argv[i+1];
			int n = atoi(a);
			printf("%d: ", n);
			
			while (n != 1) {
				printf("%d, ", n);
				if (n % 2)
					n = 3 * n + 1;
				else
					n /= 2;
			}
			printf("%d\n", n);
			printf("Done Parent %d Child %d\n", getppid(), getpid());
			exit(0);
		}
	}
	
	for (int i = 0; i < nr; i ++) {
		wait(NULL);
	}
	
	return 0;
}
