#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
	char *f1 = argv[1];
	char *f2 = argv[2];
	
	struct stat sb;
	stat(f1, &sb);
	
	int fd1 = open(f1, O_RDONLY);
	
	char buff[sb.st_size];
	read(fd1, buff, sb.st_size);
	
	int fd2 = open(f2, O_WRONLY);
	
	write(fd2, buff, sb.st_size);
	
	return 0;
}
