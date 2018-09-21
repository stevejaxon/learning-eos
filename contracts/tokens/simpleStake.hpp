#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;
using eosio::asset;

class simpleStake : public contract {
    public:
        simpleStake(account_name self):contract(self), _staked(self, self){}
        
        /// @abi action
        void stake(const account_name user, const asset& quantity);

        /// @abi action
        void unstake(const account_name user, const asset& quantity);

        /// @abi action
        void amount(const account_name user);

    private:
        /// @abi table
        struct staked {
            staked( account_name o = account_name() ):owner(o){}

            account_name owner;
            asset        eos_balance;

            bool has_tokens_staked()const { return !eos_balance.amount; }
            uint64_t primary_key()const { return owner; } // getter for primary key - mandatory
            EOSLIB_SERIALIZE(staked, (owner)(eos_balance))  
        };

        typedef eosio::multi_index< N(staked), staked> staked_index;
        staked_index     _staked;
};

EOSIO_ABI(simpleStake, (stake)(unstake))