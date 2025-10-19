#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <string.h>

int main (int argc, char *argv[]) {
	int nr = argc;
	
	char shm_name[] = "myshm";
	int shm_fd;
	shm_fd = shm_open(shm_name, O_CREAT | O_RDWR , S_IRUSR | S_IWUSR);
	
	if (shm_fd < 0) {
		perror(NULL);
		return errno;
	}
		
	int dim = getpagesize();	// cati bytes are fiecare proces sa scrie
	size_t shm_size = (nr-1) * dim;
	
	if (ftruncate(shm_fd, shm_size) == -1) {
		perror(NULL);
		shm_unlink(shm_name);
		return errno ;
	}
			
	for (int i = 1; i < nr; i ++) {
		pid_t pid = fork();
			
		if (pid < 0) {
			return errno;
		}
		else if (pid == 0) {
			// child
			int n = atoi(argv[i]);
			void *shm_ptr = mmap(0, dim, PROT_WRITE, MAP_SHARED, shm_fd, (i-1) * dim);
			
			if (shm_ptr == MAP_FAILED) {
				perror(NULL);
				shm_unlink(shm_name);
				return errno ;
			}
			
			// generate collatz			
			sprintf((char*)shm_ptr, "%d ", n);
			shm_ptr += sizeof(n);
					
			while (n != 1) {
				if (n % 2)
					n = 3 * n + 1;
				else
					n /= 2;
				sprintf((char*)shm_ptr, "%d ", n);
				shm_ptr += sizeof(n);
			}
			sprintf((char*)shm_ptr, "z");
			munmap(shm_ptr, dim);
			printf("Done Parent %d Child %d\n", getppid(), getpid());
			exit(0);
		}
	}
	
	for (int i = 1; i < nr; i ++) {
		wait(NULL);
	}
	
	void *shm_ptr = mmap(0, nr*dim, PROT_READ, MAP_SHARED, shm_fd, 0);
			
	if (shm_ptr == MAP_FAILED) {
		perror(NULL);
		shm_unlink(shm_name);
		return errno ;
	}
	
	int d = sizeof(char);
	for (int i = 1; i < nr; i ++) {
		int p = 0;
		while (strcmp((char*)shm_ptr + (i-1) * dim + p * d, "z") != 0) {
			printf("%c", *((char*)shm_ptr + (i-1) * dim + p * d));
			p ++;
		}
		printf("\n");
	}
		
	munmap(shm_ptr, shm_size);
	shm_unlink(shm_name);

	return 0;
}
