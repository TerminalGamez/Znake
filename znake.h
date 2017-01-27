#ifndef ZNAKE_H
#define ZNAKE_H

#include <pthread.h>

struct Znake;
typedef struct Znake Znake;

#include "apple.h"

struct Znake {
  int* x;
  int* y;
  int* headX;
  int* headY;
  int dirX;
  int dirY;
  int nextDirX;
  int nextDirY;
  int length;
  int alive;
};

void initZnake(Znake* znake, int width, int height);
void moveZnake(Znake* znake, pthread_mutex_t* lock);
void growZnake(Znake* znake, pthread_mutex_t* lock);
void eat(Znake* znake, Apple* apple);

int outOfBounds(Znake* znake, Canvas* canvas);
int selfCollision(Znake* znake);
void collide(Znake* znake, Canvas* canvas);

#endif // ZNAKE_H
