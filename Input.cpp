#include "Input.h"
#include <iostream>
#include <limits>
using namespace std;

bool Input::GetInput(int &x, int &y, int &size, Cell **cell) {
  char isFlag = ' ';

  bool invalid = false;
  do {
    cout << "Enter x: ";
    cin >> x;
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      invalid = true;
      cout << "Invalid input. Please enter a number." << endl;
      continue;
    } else {
      invalid = false;
    }

    cout << "Enter y: ";
    cin >> y;
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      invalid = true;
      cout << "Invalid input. Please enter a number." << endl;
      continue;
    } else {
      invalid = false;
    }

    if (IsInvalid(x, y, size)) {
      invalid = true;
      cout << "Enter valid values within the board size." << endl;
    } else {
      invalid = false;
    }
  } while (invalid);

  cin.ignore(numeric_limits<streamsize>::max(),
             '\n'); // Clear any remaining characters

  if (!cell[x][y].revealed) {
    cout << "Press f to flag or enter to reveal" << endl;
    cin.get(isFlag);

    // Check if the input is 'f' or 'Enter', else mark as invalid
    if (isFlag != 'f' && isFlag != '\n') {
      invalid = true;
      cout << "Invalid input. Press 'f' for flag or 'Enter' to reveal." << endl;
    }
  }

  return isFlag == 'f';
}

bool Input::IsInvalid(int x, int y, int size) {
  return x < 0 || x >= size || y < 0 || y >= size;
}