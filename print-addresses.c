#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc<2) {
	return 1;
	}
	for (int i = 1; i < argc; i++) {
		long num = strtol(argv[i], NULL, 10);
		int count = 0;
		long temp = num;
		while (temp > 0) {
			temp /= 16;
			count++;
		}
		printf("0x");
		for (int j = 0; j < 12 - count; j++) {
		printf("0");
		}
		printf("%lX\n", num);
	}
	return 0;
}
