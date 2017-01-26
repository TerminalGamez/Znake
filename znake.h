#ifndef ZNAKE_H
#define ZNAKE_H

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
  int length;
  int alive;
};

void initZnake(Znake* znake, int width, int hight);
void moveZnake(Znake* znake);
void growZnake(Znake* znake);
void eat(Znake* znake, Apple* apple);

int outOfBounds(Znake* znake, Canvas* canvas);
int selfCollision(Znake* znake);
void collide(Znake* znake, Canvas* canvas);

#endif // ZNAKE_H
