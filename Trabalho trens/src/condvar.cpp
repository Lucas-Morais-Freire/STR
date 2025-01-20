#include <condvar.hpp>

condvar::condvar() {
    front = back = nullptr;
    pthread_mutex_init(&op_mtx, nullptr);
}

condvar::~condvar() {
    pthread_mutex_lock(&op_mtx);
    node* curr = front;
    node* prev;
    while(curr != nullptr) {
        prev = curr->prev;
        delete curr;
        curr = prev;
    }
    pthread_mutex_unlock(&op_mtx);
    pthread_mutex_destroy(&op_mtx);
}

void condvar::wait(pthread_mutex_t* mtx) {
    // bloquear o mutex de operacao
    pthread_mutex_lock(&op_mtx);

    node new_node;
    pthread_mutex_init(&new_node.priv_mtx, nullptr);
    pthread_mutex_lock(&new_node.priv_mtx);

    // colocar um novo mutex na fila
    new_node.prev = nullptr;    // como o no vai na traseira, nao ha ninguem atras dele
    if (back != nullptr) {      // se a fila nao estiver vazia
        back->prev = &new_node; // inserir  o no na traseira
    } else {
        front = &new_node;      // se a fila estiver vazia, inserir o no na fremte
    }
    back = &new_node;           // apontar a traseira para o novo no

    // agora que fomos inseridos na lista, liberar o acesso ao mutex 
    pthread_mutex_unlock(mtx);

    // permitir edicao da fila por outros mutexes
    pthread_mutex_unlock(&op_mtx);

    // colocar a thread para dormir
    pthread_mutex_lock(&new_node.priv_mtx);

    // utilizar um unlock extra por convercao
    pthread_mutex_unlock(&new_node.priv_mtx);

    // tentar readquirir o mutex de sincronizacao
    pthread_mutex_lock(mtx);
}

void condvar::broadcast() {
    pthread_mutex_lock(&op_mtx);

    node* to_release = front;

    while(front != nullptr) {
        front = to_release->prev;

        if (front == nullptr) {
            back = nullptr;
        }

        pthread_mutex_unlock(&to_release->priv_mtx);
        to_release = front;
    }

    pthread_mutex_unlock(&op_mtx);
}