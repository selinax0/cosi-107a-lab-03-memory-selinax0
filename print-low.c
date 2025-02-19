#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
        if (argc<2) {
        return 1;
        }
        int arg = 0;
        for (int i = 1; i < argc; i++) {
                arg = arg + 1;
                long num = strtol(argv[i], NULL, 0); 
                long temp = num & 0xFF;
		printf("%d 0x", arg); 
		if (temp < 16) {
			printf("0"); 
		}
		printf("%X %3d\n", temp, temp);        
	}
        return 0;
}
