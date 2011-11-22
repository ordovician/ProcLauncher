#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
	printf("First non error line\n");
	sleep(3);
	printf("Second line. Just after sleeping\n");
	printf("Third line\n");
	
	fprintf(stderr, "Fourth line, which is sendt to stderr\n");
	
	return 0;
}