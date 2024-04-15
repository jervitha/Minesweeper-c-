#include "Board.h"
#include "Input.h"
#include <iostream>

using namespace std;

class Game {
private:
  bool isGameLoss = false;
  bool isGameWin = false;
  bool firstMove = true;

  Input *input;
  Board *board;
  Cell **cells;
  int size;
  const int mineCount = 10;

  void GenerateCell();
  void GenerateMines();
  void GenerateNumbers();
  int CountMines(int x, int y);
  void Update();
  bool CheckFlag(int x, int y);
  Cell *GetCell(int x, int y);
  void SetCell(int x, int y, Cell *cell);
  bool IsValid(int x, int y);
  void Reveal(int x, int y);
  void Flood(Cell *cell);
  bool IsFirstMove() const { return firstMove; }
  void SetFirstMove(bool value) { firstMove = value; }
  void GenerateMinesExcluding(int excludeX, int excludeY);
  bool CheckForWin();

public:
  Game(int size);

  void StartGame();

  int GetRandomNumber(int min, int max);
  ~Game();
};