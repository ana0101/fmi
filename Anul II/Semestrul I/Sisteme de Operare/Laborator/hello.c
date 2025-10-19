#include <unistd.h>

int main() {
	int fd = 0;	// pt consola
	char buff[15] = "Hello, World!\n";
	write(fd, buff, 15);
	return 0;
}
