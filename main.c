#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>

#include "apple.h"
#include "canvas.h"
#include "znake.h"


#define WIDTH 20
#define HIGHT 20

static struct termios old, new;

/* Initialize new terminal i/o settings */
void initTermios(int echo) 
{
  tcgetattr(0, &old); /* grab old terminal i/o settings */
  new = old; /* make new settings same as old settings */
  new.c_lflag &= ~ICANON; /* disable buffered i/o */
  new.c_lflag &= echo ? ECHO : ~ECHO; /* set echo mode */
  tcsetattr(0, TCSANOW, &new); /* use these new terminal i/o settings now */
}

/* Restore old terminal i/o settings */
void resetTermios(void) 
{
  tcsetattr(0, TCSANOW, &old);
}

Canvas canvas;

Znake znake;

Apple apple;

int loop = 1;

int main(){
  initTermios(0);
  srand(time(NULL));
  initZnake(&znake, WIDTH, HIGHT);
  initCanvas(&canvas, WIDTH, HIGHT);
  initApple(&apple);
  
  clearCanvas(&canvas);
  addZnakeToCanvas(&canvas, &znake);
  spawnApple(&apple, &canvas, znake.length);
  
  while(loop){
    switch(getchar()){
      case 'q' :
        loop = 0;
        continue;
      case 'a' :
        if(znake.dirX == 1){
          continue;
        }else{
          znake.dirX = -1;
          znake.dirY = 0;
          break;
        }
      case 'w' :
        if(znake.dirY == 1){
          continue;
        }else{
          znake.dirX = 0;
          znake.dirY = -1;
          break;
        }
      case 'd' :
        if(znake.dirX == -1){
          continue;
        }else{
          znake.dirX = 1;
          znake.dirY = 0;
          break;
        }
      case 's' :
        if(znake.dirY == -1){
          continue;
        }else{
          znake.dirX = 0;
          znake.dirY = 1;
          break;
        }
      case 'p' :
        apple.eaten = 1;
        continue;
      default:
        continue;
    }
    if(apple.eaten){
      growZnake(&znake);
      apple.eaten = 0;
    }else{
      moveZnake(&znake);
    }
    clearCanvas(&canvas);
    addZnakeToCanvas(&canvas, &znake);
    eat(&znake, &apple);
    if(apple.eaten){
      spawnApple(&apple, &canvas, znake.length);
    }
    addAppleToCanvas(&canvas, &apple);
    printCanvas(&canvas);
  }
  resetTermios();
  return 0;
}
