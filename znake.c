#include <stdlib.h>

#include "apple.h"
#include "znake.h"

void initZnake(Znake* znake, int width, int hight){
  znake->x = (int*) malloc(width*hight*(sizeof(int)));
  znake->y = (int*) malloc(width*hight*(sizeof(int)));
  *(znake->x) = width/2;
  *(znake->y) = hight/2;
  znake->headX = znake->x;
  znake->headY = znake->y;
  znake->dirX = 1;
  znake->dirY = 0;
  znake->length = 1;
  znake->alive = 1;
}

void moveZnake(Znake* znake){
  int prevX = *znake->headX;
  int prevY = *znake->headY;
  *znake->headX = prevX + znake->dirX;
  *znake->headY = prevY + znake->dirY;
  for(int i=znake->length-2; i>=0; i--){
      int tempX  = *(znake->x+i);
      int tempY  = *(znake->y+i);
      *(znake->x+i) = prevX;
      *(znake->y+i) = prevY;
      prevX  = tempX;
      prevY  = tempY;
  }
}
void growZnake(Znake* znake){
  *(znake->headX+1) = *znake->headX + znake->dirX;
  *(znake->headY+1) = *znake->headY + znake->dirY;
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
         (*znake->headY < 0 || *znake->headY >= canvas->hight);
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



