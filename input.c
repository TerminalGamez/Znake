#include <pthread.h>
#include <stdio.h>

#include "znake.h"

void *input(void *param){
  Znake* znake;
  znake = (Znake*) param;

  char c = 'c';
  while(znake->alive){
    switch(getchar()){
      case 'q' :
        znake->alive = 0;
        break;
      case 'a' :
        if(znake->dirX != 1){
          znake->dirX = -1;
          znake->dirY = 0;
        }
        break;
      case 'w' :
        if(znake->dirY != 1){
          znake->dirX = 0;
          znake->dirY = -1;
        }
        break;
      case 'd' :
        if(znake->dirX != -1){
          znake->dirX = 1;
          znake->dirY = 0;
        }
        break;
      case 's' :
        if(znake->dirY != -1){
          znake->dirX = 0;
          znake->dirY = 1;
        }
        break;
      default:
        break;
    }
  }
  pthread_exit(NULL);
}
