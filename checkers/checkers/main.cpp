#include <iostream>
#include <cstring>

#include "state.h"
#include "turn.h"


int main(int argc, char* argv[]) {
  State* state = new State();
  Turn* turn = new Turn();

  while (true) {
    // build list of valid turns
    state->BuildListValidTurns();

    // print board
    state->Print();

    // get current player
    char player = state->get_player();

    // check if game over
    int winner_code = state->get_winner_code();
    if (winner_code > 0) {
      std::cout << "\n-- player " << player << " wins\n" << std::endl;
      return winner_code;
    }

    // wait for player input
    std::cout << "\nplayer '" << player << "'> ";
    std::cin.clear();
    std::cin.getline(turn->data(), Turn::kDataLength);
    std::cout << std::endl;

    // check if matching one valid turn
    if (state->CheckMatchingVaildTurn(turn)) {
      // decode player input into a list of coordinates
      turn->Decode();

      // operate the turn
      state->Move(turn);

      // player takes turn
      state->SetNextPlayer();
    }
    else {
      // invalid input
      std::cout << "-- invalid turn\n" << std::endl;
      state->SetInvalidTurn();
    }
  }

  return 0;
}
