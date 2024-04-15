#include "Cell.h"
#include <iostream>
using namespace std;
#ifndef BOARD_H
#define BOARD_H

class Board {
public:
  char unknown = '.';
  char empty = '_';
  char mine = '*';
  char exploaded = '!';
  char flag = 'F';
  char num1 = '1';
  char num2 = '2';
  char num3 = '3';
  char num4 = '4';
  char num5 = '5';
  char num6 = '6';
  char num7 = '7';
  char num8 = '8';

  static int SIZE;

  Board(int size);

  void DrawBoard(Cell **board);
  char GetValue(Cell data);
  char GetRevealedValue(Cell data);
  char GetNumberValue(Cell data);

  
};
#endif