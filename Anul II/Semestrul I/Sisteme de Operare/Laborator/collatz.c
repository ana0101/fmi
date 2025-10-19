#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main (int argc, char* argv[]) {
	char *a = argv[1];
	int n = atoi(a);
	
	pid_t pid = fork();
	
	if (pid < 0) {
		return errno;
	}
	else if (pid == 0) {
		// child
		// generate collatz
		printf("%d: ", n);
		while (n != 1) {
			printf("%d, ", n);
			if (n % 2)
				n = 3 * n + 1;
			else
				n /= 2;
		}
		printf("%d\n", n);
	}
	else {
		// parent
		wait(NULL);
		printf("Child %d finished\n", pid);
	}
	return 0;
}
