#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main() {
	pid_t pid = fork();
	if (pid < 0) {
		return errno;
	}
	else if (pid == 0) {
		// child
		char *argv[] = {"ls", NULL};
		execve("/usr/bin/ls", argv, NULL);
		perror("NULL");
	}
	else {
		// parent
		printf("Parent %d Child %d\n", getpid(), pid);
		wait(NULL);
		printf("Child %d finished\n", pid);
	}
	return 0;
}
