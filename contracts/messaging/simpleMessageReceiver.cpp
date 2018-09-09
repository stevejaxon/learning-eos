#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;
using std::string;

class simpleMessageReceiver : public contract { 
  public:
    using contract::contract;

    /// @abi action
    void receive(string msg) {
      print("Received the message ", msg);
    }
};

EOSIO_ABI(simpleMessageReceiver, (receive))