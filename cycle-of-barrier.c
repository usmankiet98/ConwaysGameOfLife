#include "cycle-of-barrier.h"

#include <pthread.h>

int cyclic_barrier_init(cyclic_barrier_t* barrier, pthread_mutexattr_t* mutexattr_barrier, pthread_condattr_t* barrier_mutexattr,  int members, void (*barrier_action)(void))
 {
  pthread_mutex_init(&(barrier->barrier_mutex), mutexattr_barrier);

  pthread_cond_init(&(barrier->barrier_cond), barrier_mutexattr);

  barrier->members = members;

  barrier->good = members;

  barrier->barrier_action = barrier_action;

  return 0;
}

int cyclic_barrier_await(cyclic_barrier_t* barrier)
{
  pthread_mutex_lock(&(barrier->barrier_mutex));

  barrier->good = barrier->good - 1;

  if (0 != barrier->good)
   {
    pthread_cond_wait(&(barrier->barrier_cond), &(barrier->barrier_mutex));
  } else
   {
    (barrier->barrier_action)();

    barrier->good = barrier->members;

    pthread_cond_broadcast(&(barrier->barrier_cond));

  }

  pthread_mutex_unlock(&(barrier->barrier_mutex));


  return 0;
}

int cyclic_barrier_destroy(cyclic_barrier_t* barrier)
{
  pthread_mutex_destroy(&(barrier->barrier_mutex));

  pthread_cond_destroy(&(barrier->barrier_cond));

  return 0;
}
