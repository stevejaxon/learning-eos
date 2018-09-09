#include <eosiolib/eosio.hpp>

using namespace eosio;
using std::string;

class simpleMessageSender : public contract {
  public:
    using contract::contract;

    /// @abi action
    void send() {

    } 
};

EOSIO_ABI(simpleMessageSender, (send))