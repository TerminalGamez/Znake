#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <time.h>
#include <unistd.h>

#include "apple.h"
#include "canvas.h"
#include "input.h"
#include "znake.h"


#define WIDTH 20
#define HEIGHT 20
#define SPEED 250000

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




int main(){
  Canvas canvas;
  Znake znake;
  Apple apple;

  pthread_t thread;
  void* p[2];
  pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

  initTermios(0);
  srand(time(NULL));
  
  initZnake(&znake, WIDTH, HEIGHT);
  initCanvas(&canvas, WIDTH, HEIGHT);
  initApple(&apple);
  
  clearCanvas(&canvas);
  addZnakeToCanvas(&canvas, &znake);
  spawnApple(&apple, &canvas, znake.length);
  addAppleToCanvas(&canvas, &apple);
  printCanvas(&canvas);
  
  *p = &znake;
  *(p+1) = &lock;
  pthread_create(&thread, NULL, input, p);
  
  while(znake.alive){
    usleep(SPEED);
    clearCanvas(&canvas);
    if(apple.eaten){
      growZnake(&znake, &lock);
      apple.eaten = 0;
    }else{
      moveZnake(&znake, &lock);
    }
    addZnakeToCanvas(&canvas, &znake);
    eat(&znake, &apple);
    if(apple.eaten){
      spawnApple(&apple, &canvas, znake.length);
    }
    addAppleToCanvas(&canvas, &apple);
    printCanvas(&canvas);
    collide(&znake, &canvas);
  }
  
  pthread_join(thread, NULL);
  resetTermios();
  pthread_exit(NULL);
  return 0;
}
