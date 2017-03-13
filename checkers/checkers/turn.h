//
// Expressing coordinates of moving or jumping path
// 

#ifndef TURN_H_
#define TURN_H_

#include <vector>

#include "state.h"
#include "coord.h"

class State;


class Turn {
public:
  const static int kDataLength = 30;

  Turn() {}
  Turn(const std::vector<Coord*> coords, const bool capture)
    : coords_(coords), capture_(capture) {
    Encode();
  }
  ~Turn() {}

  void Decode();

  bool CheckMatching(Turn* turn) const;

  char* data() { return data_; }
  std::vector<Coord*> coords() const { return coords_; }
  bool capture() const { return capture_; }

private:
  const char kXMin = 'a';     // min x coordinate
  const char kYMin = '1';     // min y coordinate

  void Encode();

  char data_[kDataLength];
  std::vector<Coord*> coords_;
  bool capture_;
};

#endif    // TURN_H_
