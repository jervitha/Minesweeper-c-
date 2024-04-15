#include "Game.h"
#include <iostream>

void GameIntruction() {
  cout << "you have to put value between 0 to 9" << endl;
  cout << "First enter the index position where you want to put the input" << endl;
  cout << "then if you want to flag that position press f" << endl;
  cout << "Play until you win or loss" << endl;
}

int main() {
  GameIntruction();
  Game *game = new Game(10);
  game->StartGame();
  delete game;
}
