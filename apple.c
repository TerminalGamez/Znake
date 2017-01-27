#include <stdlib.h>

#include "apple.h"
#include "canvas.h"

void initApple(Apple* apple){
  apple->x = 0;
  apple->y = 0;
  apple->eaten = 0;
}

void spawnApple(Apple* apple, Canvas* canvas, int znakeLength){
  int position = rand() % (canvas->width*canvas->height - znakeLength);
  for(int i=0; i<position+1; i++){
    if(*(canvas->c+i) != EMPTY_BLOCK){
      position++;
    }
  }
  apple->x = position % canvas->width;
  apple->y = position / canvas->width;
}

