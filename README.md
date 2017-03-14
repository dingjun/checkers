# checkers

Two versions of a classic board game implemented as C++ console application.

### checkers

Original version which two players play and take turns on the same side. All the rules and game mechanics are fully supported, such as crowning and forced capture. Invalid input will be rejected and player will be requested to input again.

### checkers_network

Network version which includes two applications for both server-side and client-side. Server accepts input from client and sends the updated board state to both players, and client prints the current board state from server and allows player to submit input. Network functionality is implemented with the help of the stand-alone [asio C++ library](http://think-async.com/).
