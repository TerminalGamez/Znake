#ifndef CANVAS_H
#define CANVAS_H

struct Canvas;
typedef struct Canvas Canvas;

#include "apple.h"
#include "znake.h"


#define EMPTY_BLOCK  ' '
#define BORDER_BLOCK '#'
#define ZNAKE_BLOCK  'O'
#define APPLE_BLOCK  '0'

struct Canvas {
  char* c;
  int width;
  int hight;
};

void initCanvas(Canvas* canvas, int width, int hight);

void clearCanvas(Canvas* canvas);

void printHorizontalBorder(int width);
void printVerticalBorder(int end);
void printCanvas(Canvas* canvas);

void addZnakeToCanvas(Canvas* canvas, Znake* znake);
void addAppleToCanvas(Canvas* canvas, Apple* apple);

#endif // CANVAS_H
