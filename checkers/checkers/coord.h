// 
// Coordinates of checkers board.
//

#ifndef COORD_H_
#define COORD_H_

struct Coord {
  Coord(int new_x = 0, int new_y = 0) : x(new_x), y(new_y) {}
  ~Coord() {}

  Coord* Average(Coord* coord) {
    return new Coord((x + coord->x) >> 1, (y + coord->y) >> 1);
  }

  bool Equal(Coord* coord) {
    return x == coord->x && y == coord->y;
  }

  int x;
  int y;
};

#endif    // COORD_H_
