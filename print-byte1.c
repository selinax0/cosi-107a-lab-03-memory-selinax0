#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
        if (argc<2) {
        return 1;
        }
        for (int i = 1; i < argc; i++) {
                long num = strtol(argv[i], NULL, 0); 
                long temp = (num >> 8) & 0xFF;
		printf("0x"); 
		if (temp < 16) {
			printf("0"); 
		}
		printf("%X %3d\n", temp, temp);        
	}
        return 0;
}
