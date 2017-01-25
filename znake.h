#ifndef ZNAKE_H
#define ZNAKE_H

struct Znake;
typedef struct Znake Znake;

#include "apple.h"

struct Znake {
  int* x;
  int* y;
  int dirX;
  int dirY;
  int length;
};

void initZnake(Znake* znake, int width, int hight);
void moveZnake(Znake* znake);
void growZnake(Znake* znake);
void eat(Znake* znake, Apple* apple);

#endif // ZNAKE_H
