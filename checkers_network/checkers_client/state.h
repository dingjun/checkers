//
// Expressing board state and current player.
//
// For Client.
// 

#ifndef STATE_H_
#define STATE_H_


class State {
public:
  const static int kBoardSize = 8;
  const static int kIdIndex = kBoardSize * kBoardSize;
  const static int kDataLength = kIdIndex + 1 + 1;

  State() {}
  ~State() {}

  void Print() const;

  char get_player() const;
  int get_winner_code() const;
  bool is_valid_turn() const;

  char* data() { return data_; }

private:
  const static char kValidPlayerO = 'o';
  const static char kValidPlayerX = 'x';
  const static char kInvalidPlayerO = 'p';
  const static char kInvalidPlayerX = 'y';
  const static char kWinningPlayerO = 'O';
  const static char kWinningPlayerX = 'X';

  char data_[kDataLength];
};

#endif    // STATE_H_
