#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void filho_1();
void filho_2();

int main() {
    pid_t pid;
    int t;

    printf("começando programa familia.cpp\n");
    sleep(1);
    for (t = 0; t < 60; t++) {
        switch (t) {
        case 14:
            pid = fork();
            if (pid == 0)
                filho_1();
            printf("%d: Sou o pai, Tive o primeiro filho! ", t);
            break;
        case 16:
            pid = fork();
            if (pid == 0)
                filho_2();
            printf("%d: Sou o pai, Tive o segundo filho! ", t);
            break;
        default:
            printf("%d: ", t);
        }
        printf("pai: %d anos.\n", t);
        sleep(1);
    }
    printf("%d: Sou o pai e morri aos %d anos... :-(\n", t, t);

    return 0;
}

void neto_1();

void filho_1() {
    pid_t pid;
    int t;
    int gt = 14;

    for (t = 0; t < 30; t++) {
        switch (t) {
        case 12:
            pid = fork();
            if (pid == 0)
                neto_1();
            printf("%d:     Sou o filho 1, tive o primeiro filho! ", gt);
            break;
        default:
            printf("%d:     ", gt);
        }
        printf("filho 1: %d anos.\n", t);
        sleep(1);
        gt++;
    }

    printf("%d:     Sou o filho 1 e morri aos %d anos... :'-(\n", gt, t);
    exit(0);
}

void neto_2();

void filho_2() {
    pid_t pid;
    int t;
    int gt = 16;

    for (t = 0; t < 30; t++) {
        switch (t) {
        case 14:
            pid = fork();
            if (pid == 0)
                neto_2();
            printf("%d:     Sou o filho 2 e tive o primeiro filho! ", gt);
            break;
        default:
            printf("%d:     ", gt);
        }
        printf("filho 2: %d anos.\n", t);
        sleep(1);
        gt++;
    }

    printf("%d:     Sou o filho 2 e morri aos %d anos... :'-(\n", gt, t);
    exit(0);
}

void neto_1() {
    int t;
    int gt = 26;

    for (t = 0; t < 12; t++) {
        printf("%d:         neto 1: %d anos.\n", gt, t);
        sleep(1);
        gt++;
    }

    printf("%d:         Sou o neto 1 e morri aos %d anos... :'-(\n", gt, t);
    exit(0);
}

void neto_2() {
    int t;
    int gt = 30;

    for (t = 0; t < 18; t++) {
        printf("%d:         neto 2: %d anos.\n", gt, t);
        sleep(1);
        gt++;
    }

    printf("%d:         Sou o neto 2 e morri aos %d anos... :'-(\n", gt, t);
    exit(0);
}