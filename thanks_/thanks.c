#include <stdio.h>

int main(int argc, char* argv[]) {
	for (int i = 1; i < argc - 1; i++) {
		printf("%s ", argv[i]);
	}
	printf("%s: no problem :)", argv[argc - 1]);
}
