#include <stdio.h>
#include <stdlib.h>
#include "mythreads.h"

// Initialize the counter as a global variable
static volatile int counter = 0;

static pthread_mutex_t lock; // global because both threads need to acquire lock

// add any global declarations here
// Hint: Declare your lock here

// This routine will be called twice and 
// increments the counter 10000000 each
// Do not remove the print calls!
void *thread_count(void *args) {
  printf("%s: begin\n", (char *) args);
  print_thread_info();

  // Add your code below
  for (int i = 0; i < 10000000; i++) {
      pthread_mutex_lock(&lock);
      counter = counter + 1;
      pthread_mutex_unlock(&lock);
  }
  // Add your code above

  printf("%ld done\n",Thread_gettid());
  return NULL;
}

int main (int argc, char **argv)
{
  pthread_t p1, p2;

  // Initialize the lock below
  Pthread_mutex_init(&lock, NULL);
  
  Pthread_create(&p1,NULL,thread_count,"A");
  Pthread_create(&p2,NULL,thread_count,"B");
  Pthread_join(p1,NULL);
  Pthread_join(p2,NULL);
  printf("main: result %d\n", counter);

  pthread_mutex_destroy(&lock);

  return (0);
}
