#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define ULC "\u250f"
#define HL  "\u2501"
#define URC "\u2513"
#define VL  "\u2503"
#define DLC "\u2517"
#define DRC "\u251b"

pthread_mutex_t m1, m2;

inline void L1() {sleep(1);}
inline void L2() {sleep(1);}

inline void L3() {sleep(1);}

inline void L4() {sleep(1);}
inline void L5() {sleep(3);}

inline void L6() {sleep(3);}

inline void L7() {sleep(3);}
inline void L8() {sleep(5);}
inline void L9() {sleep(5);}
inline void L10() {sleep(5);}

char* g[] = {
    ULC, HL , HL , HL , URC, ULC, HL , HL , HL , URC, ULC, HL , HL , HL , URC, "\n",
    VL , " ", " ", " ", VL , VL , " ", " ", " ", VL , VL , " ", " ", " ", VL , "\n",
    DLC, HL , HL , HL , DRC, DLC, HL , HL , HL , DRC, DLC, HL , HL , HL , DRC
};

bool done[3] = {false, false, false};

void* train1(void*) {
    while(1) {
        g[16*2 + 2] = HL;
        g[16*1 + 0] = "1";
        L1();
        g[16*1 + 0] = VL;
        g[16*0 + 2] = "1";
        L2();
        pthread_mutex_lock(&m1);
        g[16*0 + 2] = HL;
        g[16*1 + 4] = "1";
        L3();
        pthread_mutex_unlock(&m1);
        g[16*1 + 4] = VL;
        g[16*2 + 2] = "1";
        L4();
    }
}

void* train2(void*) {
    while(1) {
        pthread_mutex_lock(&m1);
        g[16*2 + 7] = HL;
        g[16*1 + 5] = "2";
        L3();
        pthread_mutex_unlock(&m1);
        g[16*1 + 5] = VL;
        g[16*0 + 7] = "2";
        L5();
        pthread_mutex_lock(&m2);
        g[16*0 + 7] = HL;
        g[16*1 + 9] = "2";
        L6();
        pthread_mutex_unlock(&m2);
        g[16*1 + 9] = VL;
        g[16*2 + 7] = "2";
        L7();
    }
}

void* train3(void*) {
    while(1) {
        pthread_mutex_lock(&m2);
        g[16*2 + 12] = HL;
        g[16*1 + 10] = "3";
        L6();
        pthread_mutex_unlock(&m2);
        g[16*1 + 10] = VL;
        g[16*0 + 12] = "3";
        L8();
        g[16*0 + 12] = HL;
        g[16*1 + 14] = "3";
        L9();
        g[16*1 + 14] = VL;
        g[16*2 + 12] = "3";
        L10();
    }
}

int main() {
    pthread_mutex_init(&m1, nullptr);
    pthread_mutex_init(&m2, nullptr);

    pthread_t t1, t2, t3;

    pthread_create(&t1, nullptr, train1, nullptr);
    pthread_create(&t2, nullptr, train2, nullptr);
    pthread_create(&t3, nullptr, train3, nullptr);

    usleep(250);
    while(1) {
        system("clear");
        for (int i = 0; i < 47; i++) {
            printf("%s", g[i]);
        }
        printf("\n");
        sleep(1);
    }

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(t3, nullptr);

    pthread_mutex_destroy(&m1);
    pthread_mutex_destroy(&m2);
    return 0;
}