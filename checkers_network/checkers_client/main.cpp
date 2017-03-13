#include <iostream>
#include <cstring>
#include "asio.hpp"

#include "state.h"

using asio::ip::tcp;

const int kTurnLength = 30;


int main(int argc, char* argv[]) {
  try {
    if (argc != 3) {
      // <host>: host name
      // <port>: port number
      std::cerr << "Usage: checkers_client <host> <port>" << std::endl;
      return 3;
    }

    asio::io_service io_service;

    tcp::resolver resolver(io_service);
    tcp::resolver::query query(argv[1], argv[2]);
    tcp::resolver::iterator iterator = resolver.resolve(query);

    tcp::socket socket(io_service);
    asio::connect(socket, iterator);

    // learn who i am
    char player_message[2];
    socket.read_some(asio::buffer(player_message));
    char player_id = player_message[0];
    std::cout << "-- I am player " << player_id << "\n" << std::endl;

    State* state = new State();

    while (true) {
      // current state
      socket.read_some(asio::buffer(state->data(), State::kDataLength));

      // show board
      state->Print();

      // current player
      char current_player = state->get_player();

      // check if game is over
      int winner_code = state->get_winner_code();
      if (winner_code > 0) {
        std::cout << "\n-- player " << current_player << " wins\n" << std::endl;
        return winner_code;
      }

      // check if last turn is valid
      if (!state->is_valid_turn()) {
        std::cout << "\n-- invalid turn" << std::endl;
      }

      char turn[kTurnLength];
      std::cout << "\nplayer '" << current_player << "'> ";
      if (current_player == player_id) {      // my turn
        std::cin.getline(turn, kTurnLength);
        socket.write_some(asio::buffer(turn, std::strlen(turn)));
      }
      else {                                  // opponent's turn
        size_t read_length = socket.read_some(asio::buffer(turn));
        std::cout.write(turn, read_length);
        std::cout << "\n";
      }
      std::cout << std::endl;
    }
  }
  catch (std::exception& e) {
    std::cerr << "Exception: " << e.what() << std::endl;
  }

  return 0;
}
