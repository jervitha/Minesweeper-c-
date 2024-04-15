#ifndef CELL_H
#define CELL_H

struct Cell {
public:
  enum Type { Invalid, Empty, Mine, Number };

  int x, y;
  Type type;
  int number;
  bool revealed = false;
  bool flagged = false;
  bool exploded = false;

  Cell()
      : x(0), y(0), type(Empty), number(0), revealed(false), flagged(false),
        exploded(false) {}

  Cell(int x, int y)
      : x(x), y(y), type(Empty), number(0), revealed(false), flagged(false),
        exploded(false) {}
};

#endif // CELL_H
