/**
 * This program is based on the work from Taylor Hornby available here: https://github.com/defuse/flush-reload-attacks
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define REPEAT(A) A;A;A;A;A;A;A;A;A;A;
#define BYPASS_BRANCH_PREDICTION

void number_0() {
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
    printf("0");
}

void number_1() {
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
    printf("1");
}

void number_2() {
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
    printf("2");
}

void number_3() {
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
    printf("3");
}

int main(int argc, char **argv) {

    srand(time(NULL));

    for (int i = 0; i < 5; i++) {

        unsigned int input = rand() % 4;

#ifdef BYPASS_BRANCH_PREDICTION
        if (__builtin_expect(input == 0, 0)) {
            number_0();
        } else if (__builtin_expect(input == 1, 0)) {
            number_1();
        } else if (__builtin_expect(input == 2, 0)) {
            number_2();
        } else if (__builtin_expect(input == 3, 0)) {
            number_3();
        }
#else
        if (input == 0) {
            number_0();
        } else if (input == 1) {
            number_1();
        } else if (input == 2) {
            number_2();
        } else if (input == 3) {
            number_3();
        }
#endif
    }

}

