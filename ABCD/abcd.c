/**
 * This program is based on the work from Taylor Hornby available here: https://github.com/defuse/flush-reload-attacks
 */

#include <stdio.h>
#include <stdlib.h>

#define REPEAT(A) A;A;A;A;A;A;A;A;A;A;
#define BYPASS_BRANCH_PREDICTION

void input_A() {
    int x = 3;
    int y = 4;

    REPEAT(x += y;
                   x *= y)
    REPEAT(x += y;
                   x *= y)

    for (int i = 0; i < 30000; i++) {
        x *= y;
        x += y;
        x *= y;
        x *= y;
    }
    x *= y;
    x += y;
    x *= y;
    x *= y;
    printf("You entered A\n");
}

void input_B() {
    int x = 3;
    int y = 4;

    REPEAT(x += y;
                   x *= y)
    REPEAT(x += y;
                   x *= y)

    for (int i = 0; i < 30000; i++) {
        x *= y;
        x += y;
        x *= y;
        x *= y;
    }
    x *= y;
    x += y;
    x *= y;
    x *= y;
    printf("You entered B\n");
}

void input_C() {
    int x = 3;
    int y = 4;
    REPEAT(x += y;
                   x *= y)
    REPEAT(x += y;
                   x *= y)

    for (int i = 0; i < 30000; i++) {
        x *= y;
        x += y;
        x *= y;
        x *= y;
    }
    x *= y;
    x += y;
    x *= y;
    x *= y;
    printf("You entered C\n");
}

void input_D() {
    int x = 3;
    int y = 4;
    REPEAT(x += y;
                   x *= y)
    REPEAT(x += y;
                   x *= y)

    for (int i = 0; i < 30000; i++) {
        x *= y;
        x += y;
        x *= y;
        x *= y;
    }
    x *= y;
    x += y;
    x *= y;
    x *= y;
    printf("You entered D\n");
}

int main(int argc, char **argv) {
    char input[16];

    while (1) {

        printf("Enter either A, B, C, D or Q to quit:\n");
        fgets(input, 16, stdin);

        if (input[0] != 'A' && input[0] != 'B' && input[0] != 'C' && input[0] != 'D' && input[0] != 'Q') {
            printf("You're doing it wrong\n");
        } else {


#ifdef BYPASS_BRANCH_PREDICTION
            if (__builtin_expect(input[0] == 'A', 0)) {
                input_A();
            } else if (__builtin_expect(input[0] == 'B', 0)) {
                input_B();
            } else if (__builtin_expect(input[0] == 'C', 0)) {
                input_C();
            } else if (__builtin_expect(input[0] == 'D', 0)) {
                input_D();
            } else {
                exit(0);
            }
#else
            if (input[0] == 'A') {
                input_A();
            } else if (input[0] == 'B') {
                input_B();
            } else if (input[0] == 'C') {
                input_C();
            } else if (input[0] == 'D') {
                input_D();
            } else {
                exit(0);
            }
#endif
        }

    }
}
