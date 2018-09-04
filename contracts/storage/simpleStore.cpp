#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <eosiolib/dispatcher.hpp>
#include <eosiolib/multi_index.hpp>
#include <string>

using namespace eosio;
using std::string;

class simpleStore : public contract {  
  public:
    using contract::contract;    

    simpleStore(account_name self):contract(self), _dataStore(self, self){}

    /// @abi action
    void setglobal(string& value) {
      // We'll use the uint64 representation of the contract's account_name as the global key
      auto keyValue = N(_self);
      // Make a lookup call to see if anything has been stored already in the global variable
      auto itr = _dataStore.find(keyValue);
      // If a value has already been set then we need to call the modify function on the data store
      if (itr != _dataStore.end()) {
        _dataStore.modify(
          itr, get_self(), 
          [&]( auto& d ) {
            d.key = keyValue;
            d.data = value;
            }
        );
      } else {
        _dataStore.emplace(
          get_self(), 
          [&]( auto& d ) {
            d.key = keyValue;
            d.data = value;
          }
        );
      }      
    }

  private:
    /// @abi table
    struct storage {
      uint64_t  key;
      string    data;

      uint64_t primary_key() const { return key; } // getter for primary key - mandatory
      EOSLIB_SERIALIZE(storage, (key)(data))  
    };

    typedef eosio::multi_index<N(storage), storage> datastore;
    datastore _dataStore;
};

EOSIO_ABI(simpleStore, (setglobal))