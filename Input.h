#include "Cell.h"
#ifndef INPUT_H
#define INPUT_H

class Input {
public:
  bool GetInput(int &x, int &y, int &size, Cell **isReviled);
  bool IsInvalid(int x, int y, int size);	
};
#endif // CELL_H