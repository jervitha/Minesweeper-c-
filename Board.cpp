#include "Board.h"
#include "Cell.h"
#include <iostream>

Board::Board(int size) { Board::SIZE = size; }
int Board::SIZE = 0;
void Board::DrawBoard(Cell **board) {
  cout << endl << endl;
  for (int i = 0; i < Board::SIZE; i++) {
    cout << " ";
    for (int j = 0; j < Board::SIZE; j++) {
      Cell cell = board[i][j];
      cout << GetValue(cell) << " "
           << " ";
    }
    cout << endl;
  }
  cout << endl << endl;
}

char Board::GetValue(Cell data) {
  if (data.revealed) {
    return GetRevealedValue(data);
  } else if (data.flagged) {
    return Board::flag;
  } else {
    return Board::unknown;
  }
}

char Board::GetRevealedValue(Cell data) {
  switch (data.type) {
  default:
  case Cell::Empty:
    return Board::empty;
  case Cell::Mine:
    return Board::mine;
  case Cell::Number:
    return GetNumberValue(data);
  }
}

char Board::GetNumberValue(Cell data) {
  switch (data.number) {
  case 1:
    return Board::num1;
  case 2:
    return Board::num2;
  case 3:
    return Board::num3;
  case 4:
    return Board::num4;
  case 5:
    return Board::num5;
  case 6:
    return Board::num6;
  case 7:
    return Board::num7;
  case 8:
    return Board::num8;
  default:
    return 0;
  }
}
