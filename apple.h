#ifndef APPLE_H
#define APPLE_H

struct Apple;
typedef struct Apple Apple;

#include "canvas.h"

struct Apple {
  int x;
  int y;
  int eaten;
};

void initApple(Apple* apple);
void spawnApple(Apple* apple, Canvas* canvas, int znakeLength);

#endif // APPLE_H
