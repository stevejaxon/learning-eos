#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;

class helloWorld : public contract {
public:
  using contract::contract;

  /// @abi action
  void hi() {
    print("Hello, I'm the contract ", name{_self});
    // print("I'm belong to the account ", name{current_receiver});
    // print("The system time is ", publication_time);
  }

  /// @abi action
  void verify(account_name user) {
    require_auth(user);
    print("Verified as being ", name{user});
  }
};

EOSIO_ABI(helloWorld, (hi)(verify))