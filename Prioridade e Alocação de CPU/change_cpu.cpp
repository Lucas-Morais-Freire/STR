#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

int main(int argc, char** argv) {
    if (argc != 3) {
        printf("Quantidade de argumentos invalida: %d.\n", argc);
        return 1;
    }

    pid_t proc_pid = strtol(argv[1], nullptr, 10);
    unsigned char cpu = strtol(argv[2], nullptr, 10);
    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(cpu, &mask);

    int result = sched_setaffinity(proc_pid, sizeof(mask), &mask);

    if (result == -1) {
        printf("Falha em escalonar a cpu.\n");
        return 1;
    }

    printf("A CPU do processo %d foi trocada para %d\n", proc_pid, cpu);

    return 0;
}