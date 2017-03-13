#include "state.h"

#include <iostream>


void State::Print() const {
  const char kHRuler[] = "  a b c d e f g h";
  std::cout << kHRuler << "\n";
  int index = kBoardSize * kBoardSize - kBoardSize;
  for (int y = kBoardSize; y > 0; --y) {
    std::cout << y << " ";
    for (int x = 0; x < kBoardSize; ++x) {
      std::cout << data_[index++] << " ";
    }
    std::cout << y << "\n";
    index -= (kBoardSize << 1);
  }
  std::cout << kHRuler << std::endl;
}

char State::get_player() const {
  if (data_[kIdIndex] == kValidPlayerO
    || data_[kIdIndex] == kInvalidPlayerO
    || data_[kIdIndex] == kWinningPlayerO) {
    return kValidPlayerO;
  }
  else {
    return kValidPlayerX;
  }
}

int State::get_winner_code() const {
  if (data_[kIdIndex] == kWinningPlayerO) {
    return 1;
  }
  if (data_[kIdIndex] == kWinningPlayerX) {
    return 2;
  }
  return 0;
}

bool State::is_valid_turn() const {
  return (data_[kIdIndex] != kInvalidPlayerO
    && data_[kIdIndex] != kInvalidPlayerX);
}
