#ifndef CYCLIC_BARRIER_H
#define CYCLIC_BARRIER_H

#include <pthread.h>

typedef struct cyclic_barrier_t
{

  pthread_mutex_t barrier_mutex;

  pthread_cond_t barrier_cond;

  int members;

  int good;

  void (*barrier_action) (void);

}
cyclic_barrier_t;


int cyclic_barrier_init(cyclic_barrier_t* barrier, pthread_mutexattr_t* mutexattr_barrier, pthread_condattr_t* barrier_mutexattr, int members, void (*barrier_action)(void));

int cyclic_barrier_await(cyclic_barrier_t* barrier);

int cyclic_barrier_destroy(cyclic_barrier_t* barrier);

#endif
