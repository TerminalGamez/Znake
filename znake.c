#include <pthread.h>
#include <stdlib.h>

#include "apple.h"
#include "znake.h"

void initZnake(Znake* znake, int width, int height){
  znake->x = (int*) malloc(width*height*(sizeof(int)));
  znake->y = (int*) malloc(width*height*(sizeof(int)));
  *(znake->x) = width/2;
  *(znake->y) = height/2;
  znake->headX = znake->x;
  znake->headY = znake->y;
  znake->dirX = 1;
  znake->dirY = 0;
  znake->nextDirX = 1;
  znake->nextDirY = 0;
  znake->length = 1;
  znake->alive = 1;
}

void moveZnake(Znake* znake, pthread_mutex_t* lock){
  int prevX = *znake->headX;
  int prevY = *znake->headY;
  pthread_mutex_lock(lock);
    *znake->headX = prevX + znake->nextDirX;
    *znake->headY = prevY + znake->nextDirY;
    znake->dirX = znake->nextDirX;
    znake->dirY = znake->nextDirY;
  pthread_mutex_unlock(lock);
  for(int i=znake->length-2; i>=0; i--){
      int tempX  = *(znake->x+i);
      int tempY  = *(znake->y+i);
      *(znake->x+i) = prevX;
      *(znake->y+i) = prevY;
      prevX  = tempX;
      prevY  = tempY;
  }
}
void growZnake(Znake* znake, pthread_mutex_t* lock){
  pthread_mutex_lock(lock);
    *(znake->headX+1) = *znake->headX + znake->nextDirX;
    *(znake->headY+1) = *znake->headY + znake->nextDirY;
    znake->dirX = znake->nextDirX;
    znake->dirY = znake->nextDirY;
  pthread_mutex_unlock(lock);
  znake->headX++;
  znake->headY++;
  znake->length++;
}

void eat(Znake* znake, Apple* apple){
  if(*znake->headX == apple->x && *znake->headY == apple->y){
    apple->eaten = 1;
  }
}

int outOfBounds(Znake* znake, Canvas* canvas){
  return (*znake->headX < 0 || *znake->headX >= canvas->width) ||
         (*znake->headY < 0 || *znake->headY >= canvas->height);
}

int selfCollision(Znake* znake){
  for(int i=0; i<znake->length-1; i++){
    if(*znake->headX == *(znake->x + i) && *znake->headY == *(znake->y + i)){
      return 1;
    }
  }
  return 0;
}

void collide(Znake* znake, Canvas* canvas){
  if( outOfBounds(znake, canvas) || selfCollision(znake) ){
    znake->alive = 0;
  }
}



