#include <iostream>
#include <cstdlib>
#include "asio.hpp"

#include "state.h"
#include "turn.h"

using asio::ip::tcp;


int main(int argc, char* argv[]) {
  try {
    if (argc != 2) {
      // <port>: port number
      std::cerr << "Usage: checkers_server <port>" << std::endl;
      // <port>: port number
      // <human/ai>: hh, ha, ah, aa
      //if (argc != 3) {
      //  std::cerr << "Usage: checkers_server <port> <human/ai>" << std::endl;
      return 3;
    }

    asio::io_service io_service;

    tcp::endpoint endpoint(tcp::v4(), std::atoi(argv[1]));
    tcp::acceptor acceptor(io_service, endpoint);

    tcp::socket socket_o(io_service);
    tcp::socket socket_x(io_service);

    // first player connected is player o
    std::cout << "-- waiting for player o\n" << std::endl;
    acceptor.accept(socket_o);
    // notify client player id
    socket_o.write_some(asio::buffer("o"));

    // second player connected is player x
    std::cout << "-- waiting for player x" << std::endl;
    acceptor.accept(socket_x);
    // notify client player id
    socket_x.write_some(asio::buffer("x"));

    State* state = new State();
    Turn* turn = new Turn();

    while (true) {
      // build list of valid turns
      state->BuildListValidTurns();

      // push state to both players
      socket_o.write_some(asio::buffer(state->data(), State::kDataLength));
      socket_x.write_some(asio::buffer(state->data(), State::kDataLength));

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
      size_t tSize;
      if (player == 'o') {
        tSize = socket_o.read_some(
          asio::buffer(turn->data(), Turn::kDataLength));
        // push the received input to another player
        socket_x.write_some(asio::buffer(turn->data(), tSize));
      }
      else {
        tSize = socket_x.read_some(
          asio::buffer(turn->data(), Turn::kDataLength));
        // push the received input to another player
        socket_o.write_some(asio::buffer(turn->data(), tSize));
      }
      // reset turn
      turn->CloseBuffer(tSize);
      // show the received input on server side as well
      std::cout << turn->data() << std::endl;

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
        std::cout << "-- invalid turn" << std::endl;
        state->SetInvalidTurn();
      }
    }
  }
  catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
