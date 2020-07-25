#include "cyclic_barrier.h"

typedef struct thread_param_t {
    int length;
    int first_row;
    int first_col;
    cyclic_barrier_t* barrier;
} thread_param_t;

int splitBoard(thread_param_t* threadList, int threadCount, int rows, int columns);