#include "Game.h"
#include <iostream>
#include <random>
using namespace std;

Game::Game(int size) {
  this->size = size;
  cells = new Cell *[size];
  board = new Board(size);
  input = new Input();
}

void Game::StartGame() {
  GenerateCell();
  GenerateMines();
  GenerateNumbers();
  board->DrawBoard(cells);
  Update();
}

void Game::Update() {
  while (!isGameLoss && !isGameWin) {
    int x, y;
    bool isFlag = input->GetInput(x, y, size, cells);

    if (IsFirstMove()) {
      GenerateMinesExcluding(x, y);
      SetFirstMove(false);
    }

    if (!GetCell(x, y)->revealed) {
      if (isFlag) {
        CheckFlag(x, y);
      } else {
        Reveal(x, y);
      }
      board->DrawBoard(cells);
    } else {
      cout << "Cell already revealed" << endl;
    }

    if (GetCell(x, y)->type == Cell::Type::Mine) {
      isGameLoss = true;
      cout << "Game over! You hit a mine." << endl;
      break;
    }

    if (CheckForWin()) {
      isGameWin = true;
      cout << "Congratulations! You win!" << endl;
      break;
    }
  }
}

bool Game::CheckForWin() {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      Cell *cell = GetCell(i, j);
      if (cell->type != Cell::Type::Mine && !cell->revealed) {
        return false;
      }
    }
  }
  return true;
}

void Game::Reveal(int x, int y) {
  Cell *cell = GetCell(x, y);
  if (cell->flagged || cell->revealed) {
    cout << "Cell is flagged or revealed" << endl;
    return;
  }
  if (cell->type == Cell::Type::Empty) {
    Flood(cell);
  }
  cell->revealed = true;
}

void Game::Flood(Cell *cell) {
  if (cell == nullptr || cell->revealed)
    return;
  if (cell->type == Cell::Mine || cell->type == Cell::Invalid)
    return;

  cell->revealed = true;
  if (cell->type == Cell::Empty) {
    int x = cell->x;
    int y = cell->y;

    if (IsValid(x - 1, y))
      Flood(GetCell(x - 1, y));
    if (IsValid(x + 1, y))
      Flood(GetCell(x + 1, y));
    if (IsValid(x, y - 1))
      Flood(GetCell(x, y - 1));
    if (IsValid(x, y + 1))
      Flood(GetCell(x, y + 1));
  }
}

bool Game::CheckFlag(int x, int y) {
  GetCell(x, y)->flagged = !GetCell(x, y)->flagged;
  return GetCell(x, y)->flagged;
}

void Game::GenerateMinesExcluding(int excludeX, int excludeY) {
  for (int i = 0; i < mineCount; i++) {
    int x = GetRandomNumber(0, size - 1);
    int y = GetRandomNumber(0, size - 1);

    while (cells[x][y].type == Cell::Type::Mine ||
           (x == excludeX && y == excludeY)) {
      x = GetRandomNumber(0, size - 1);
      y = GetRandomNumber(0, size - 1);
    }

    GetCell(x, y)->type = Cell::Mine;
  }
}

void Game::GenerateCell() {
  for (int i = 0; i < size; i++) {
    cells[i] = new Cell[size];
    for (int j = 0; j < size; j++) {
      Cell cell(i, j);
      cell.type = Cell::Type::Empty;
      SetCell(i, j, &cell);
    }
  }
}

Game::~Game() {
  for (int i = 0; i < size; i++) {
    delete[] cells[i];
  }
  delete[] cells;
  delete board;
  delete input;
}

void Game::GenerateMines() {
  for (int i = 0; i < mineCount; i++) {
    int x = GetRandomNumber(0, size - 1);
    int y = GetRandomNumber(0, size - 1);

    while (cells[x][y].type == Cell::Type::Mine) {
      x = GetRandomNumber(0, size - 1);
      y = GetRandomNumber(0, size - 1);
    }
    GetCell(x, y)->type = Cell::Type::Mine;
  }
}

int Game::GetRandomNumber(int min, int max) {
  random_device rd;
  mt19937 generator(rd());

  uniform_int_distribution<int> distribution(min, max);

  return distribution(generator);
}

void Game::GenerateNumbers() {
  for (int i = 0; i < Game::size; i++) {
    for (int j = 0; j < Game::size; j++) {
      Cell *cell = GetCell(i, j);

      if (cell->type == Cell::Type::Mine) {
        continue;
      }

      cell->number = CountMines(i, j);
      if (cell->number > 0) {
        cell->type = Cell::Type::Number;
      }
    }
  }
}

int Game::CountMines(int cellX, int cellY) {
  int count = 0;
  for (int adjX = -1; adjX <= 1; adjX++) {
    for (int adjY = -1; adjY <= 1; adjY++) {

      int x = cellX + adjX;
      int y = cellY + adjY;
      if (adjX == 0 && adjY == 0) {
        continue;
      }

      if (!IsValid(x, y))
        continue;

      if (GetCell(x, y)->type == Cell::Type::Mine) {
        count++;
      }
    }
  }
  return count;
}

Cell *Game::GetCell(int x, int y) { return &cells[x][y]; }

void Game::SetCell(int x, int y, Cell *cell) {
  if (IsValid(x, y)) {
    cells[x][y] = *cell;
  } else {
    cout << "Invalid cell" << endl;
  }
}

bool Game::IsValid(int x, int y) {
  return x >= 0 && x < size && y >= 0 && y < size;
}