#include <stdio.h>

int crash() {
    int *x = 0;

    printf("I'm going to print x!\n");
    printf("The value of *x is %ld\n", *x);
}

int main(int argc, char **argv) {
    print("We're going to crash!\n");
    crash();
    printf("Back after the crash?\n");
}
