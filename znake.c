#include <stdlib.h>

#include "apple.h"
#include "znake.h"

void initZnake(Znake* znake, int width, int hight){
  znake->x = (int*) malloc(width*hight*(sizeof(int)));
  znake->y = (int*) malloc(width*hight*(sizeof(int)));
  *(znake->x) = width/2;
  *(znake->y) = hight/2;
  znake->dirX = 1;
  znake->dirY = 0;
  znake->length = 1;
}

int  tempX;
int  tempY;
int  prevX;
int  prevY;
int* headX;
int* headY; 
void moveZnake(Znake* znake){
  headX = znake->x+znake->length-1;
  headY = znake->y+znake->length-1;
  prevX = *headX;
  prevY = *headY;
  *headX = prevX + znake->dirX;
  *headY = prevY + znake->dirY;
  for(int i=znake->length-2; i>=0; i--){
      tempX  = *(znake->x+i);
      tempY  = *(znake->y+i);
      *(znake->x+i) = prevX;
      *(znake->y+i) = prevY;
      prevX  = tempX;
      prevY  = tempY;
  }
}
void growZnake(Znake* znake){
  headX = znake->x + znake->length - 1;
  headY = znake->y + znake->length - 1;
  *(headX+1) = *headX + znake->dirX;
  *(headY+1) = *headY + znake->dirY;
  znake->length++;
}

void eat(Znake* znake, Apple* apple){
  headX = znake->x + znake->length-1;
  headY = znake->y + znake->length-1;
  if(*headX == apple->x && *headY == apple->y){
    apple->eaten = 1;
  }
}
