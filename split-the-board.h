#include "cycle-of-barrier.h"

typedef struct thread_param_t
{
    int length;

    int f_row;

    int f_col;

    cyclic_barrier_t* barrier;

} thread_param_t;

int view_board(thread_param_t* t_list, int t_count, int rows, int columns);
