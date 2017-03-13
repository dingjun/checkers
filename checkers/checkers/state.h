//
// Expressing board state and current player.
// 

#ifndef STATE_H_
#define STATE_H_

#include <vector>
#include "turn.h"
#include "coord.h"

class Turn;


class State {
public:
  const static int kBoardSize = 8;
  const static int kIdIndex = kBoardSize * kBoardSize;
  const static int kDataLength = kIdIndex + 1 + 1;

  State();
  ~State() {}

  void BuildListValidTurns();
  void Print() const;

  bool CheckMatchingVaildTurn(Turn* turn) const;
  void Move(Turn* turn);
  void SetNextPlayer();
  void SetInvalidTurn();
  
  char get_player() const;
  int get_winner_code() const;

  char* data() { return data_; }

private:
  const static int kManKingDiff = 'a' - 'A';
  const static char kLegalSpace = '.';
  const static char kIllegaleSpace = ' ';
  const static char kValidPlayerO = 'o';
  const static char kValidPlayerX = 'x';
  const static char kInvalidPlayerO = 'p';
  const static char kInvalidPlayerX = 'y';
  const static char kWinningPlayerO = 'O';
  const static char kWinningPlayerX = 'X';

  void CheckValidTurns(Coord* coord);

  bool CheckValidJumpTurns(
    Coord* pre_coord, Coord* new_coord, std::vector<Coord*> coords, bool king);
  void CheckValidMoveTurns(Coord* coord);

  void AddValidJumpTurn(const std::vector<Coord*> coords);
  void AddValidMoveTurn(Coord* pre_coord, Coord* new_coord);

  bool is_valid_coord(const Coord* coord) const;
  bool is_own_piece(const Coord* coord) const;
  bool is_opponent_piece(const Coord* coord) const;
  bool is_legal(const Coord* coord) const;
  bool is_king(const Coord* coord) const;

  bool is_valid_direction(Coord* pre_coord, Coord* new_coord) const;
  bool is_moveable(Coord* pre_coord, Coord* new_coord) const;
  bool is_jumpable(Coord* pre_coord, Coord* new_coord, bool king) const;
  
  char get_opponent() const;

  void set_player(const char player);

  void set_piece(const Coord* coord, const char piece);
  char get_piece(const Coord* coord) const;

  char data_[kDataLength];
  std::vector<Turn*> valid_turns_;
  bool forced_capture_;
  int o_count_;
  int x_count_;
};

#endif    // STATE_H_
