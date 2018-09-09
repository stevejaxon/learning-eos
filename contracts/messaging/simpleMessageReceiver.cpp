#include <eosiolib/eosio.hpp>

using namespace eosio;
using std::string;

class simpleMessageReceiver : public contract { 
  public:
    using contract::contract;

    /// @abi action
    void receive() {

    }
};

EOSIO_ABI(simpleMessageReceiver, (receive))