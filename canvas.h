#ifndef CANVAS_H
#define CANVAS_H

struct Canvas;
typedef struct Canvas Canvas;

#include "apple.h"
#include "znake.h"


#define EMPTY_BLOCK  ' '
#define BORDER_BLOCK '#'
#define ZNAKE_BLOCK  'O'
#define APPLE_BLOCK  '*'

struct Canvas {
  char* c;
  int width;
  int height;
};

void initCanvas(Canvas* canvas, int width, int height);

void clearCanvas(Canvas* canvas);

void printHorizontalBorder(int width);
void printVerticalBorder(int end);
void printCanvas(Canvas* canvas);

void addZnakeToCanvas(Canvas* canvas, Znake* znake);
void addAppleToCanvas(Canvas* canvas, Apple* apple);
void addTextToCanvas(Canvas* canvas, int y, char* text, int textLength);
void addGameOverToCanvas(Canvas* canvas);

#endif // CANVAS_H
