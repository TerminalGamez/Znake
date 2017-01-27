#include <pthread.h>
#include <stdio.h>

#include "znake.h"

void* input(void* param){
  void** p = (void**) param;
  Znake* znake = (Znake*) *p;
  pthread_mutex_t* lock = (pthread_mutex_t*) *(p+1);

  while(znake->alive){
    switch(getchar()){
      case 'q' :
        znake->alive = 0;
        break;
      case 'a' :
        pthread_mutex_lock(lock);
          if(znake->dirX != 1){
            znake->nextDirX = -1;
            znake->nextDirY = 0;
          }
        pthread_mutex_unlock(lock);
        break;
      case 'w' :
        pthread_mutex_lock(lock);
          if(znake->dirY != 1){
            znake->nextDirX = 0;
            znake->nextDirY = -1;
          }
        pthread_mutex_unlock(lock);
        break;
      case 'd' :
        pthread_mutex_lock(lock);
          if(znake->dirX != -1){
            znake->nextDirX = 1;
            znake->nextDirY = 0;
          }
        pthread_mutex_unlock(lock);
        break;
      case 's' :
        pthread_mutex_lock(lock);
          if(znake->dirY != -1){
            znake->nextDirX = 0;
            znake->nextDirY = 1;
          }
        pthread_mutex_unlock(lock);
        break;
      default:
        break;
    }
  }
  pthread_exit(NULL);
}
