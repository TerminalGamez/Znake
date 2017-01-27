#include <stdio.h>
#include <stdlib.h>

#include "canvas.h"
#include "znake.h"

void initCanvas(Canvas* canvas, int width, int height){
  canvas->c = (char*) malloc(width*height*sizeof(char));
  canvas->width = width;
  canvas->height = height;
}

void clearCanvas(Canvas* canvas){
  for(int i=0; i<canvas->width*canvas->height; i++){
    *(canvas->c+i) = EMPTY_BLOCK;
  }
}

void printHorizontalBorder(int width){
  for(int x=0; x<width+2; x++){
    putchar(BORDER_BLOCK);
  }
  putchar('\n');
}
void printVerticalBorder(int end){
  putchar(BORDER_BLOCK);
  if(end){
    putchar('\n');
  }
}
void printCanvas(Canvas* canvas){
  printHorizontalBorder(canvas->width);
  for(int y=0; y<canvas->width; y++){
    printVerticalBorder(0);
    for(int x=0; x<canvas->height; x++){
      putchar(*(canvas->c+x+(y*canvas->width)));
    }
    printVerticalBorder(1);
  }
  printHorizontalBorder(canvas->width);
}

void addZnakeToCanvas(Canvas* canvas, Znake* znake){
  for(int i=0; i<znake->length; i++){
    *(canvas->c+*(znake->x+i)+(*(znake->y+i)*canvas->width)) = ZNAKE_BLOCK;
  }
}
void addAppleToCanvas(Canvas* canvas, Apple* apple){
    *(canvas->c + apple->x + apple->y*canvas->width) = APPLE_BLOCK;
}
