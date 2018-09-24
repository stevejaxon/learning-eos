#include "simpleMessageReceiver.hpp"

/// @abi action
void simpleMessageReceiver::receive(string msg) {
  print("Received the message ", msg);
}

EOSIO_ABI(simpleMessageReceiver, (receive))