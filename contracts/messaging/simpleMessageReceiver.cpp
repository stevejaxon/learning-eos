#include "simpleMessageReceiver.hpp"

/// @abi action
void receive(string msg) {
  print("Received the message ", msg);
}

EOSIO_ABI(simpleMessageReceiver, (receive))