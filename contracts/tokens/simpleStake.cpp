#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/print.hpp>

using namespace eosio;
using eosio::asset;

class simpleStake : public contract {
    public:
        simpleStake(account_name self):contract(self), _staked(self, self){}
        
        /// @abi action
        void stake(const account_name user, const asset& quantity) {
            require_auth(user);
            eosio_assert( quantity.is_valid(), "invalid quantity" );
            eosio_assert( quantity.amount > 0, "must deposit positive quantity" );

            if (! has_acc_in_index(user)) {
                create_acc_in_index(user);
            }

            action(
                permission_level{ user, N(active) },
                N(eosio.token), N(transfer),
                std::make_tuple(user, _self, quantity, std::string("staked"))
            ).send();

            auto itr = _staked.find(user);
            _staked.modify( itr, 0, [&]( auto& acnt ) {
                acnt.eos_balance += quantity;
            });
        }

        /// @abi action
        void unstake(account_name user, const asset& quantity) {
            require_auth(user);
            eosio_assert( quantity.is_valid(), "invalid quantity" );
            eosio_assert( quantity.amount > 0, "must deposit positive quantity" );
            eosio_assert(has_acc_in_index(user), "unknown account");

            auto itr = _staked.find(user);
            _staked.modify( itr, 0, [&]( auto& acnt ) {
                eosio_assert( acnt.eos_balance >= quantity, "insufficient balance" );
                acnt.eos_balance -= quantity;
            });

            action(
                permission_level{ _self, N(active) },
                N(eosio.token), N(transfer),
                std::make_tuple(_self, user, quantity, std::string("unstaked"))
            ).send();

            if( itr->has_no_tokens_staked() ) {
                _staked.erase(itr);
            }
        }

        /// @abi action
        void amount(const account_name user) {
            if (has_acc_in_index(user)) {
                auto itr = _staked.find( user );
                print(itr->amount_staked());
            } else {
                print(0);
            }
        }

    private:
        /// @abi table
        struct staked {
            staked( account_name o = account_name() ):owner(o){}

            account_name owner;
            asset        eos_balance;

            bool has_no_tokens_staked()const { return !eos_balance.amount; }
            int64_t amount_staked()const { return eos_balance.amount; }
            uint64_t primary_key()const { return owner; } // getter for primary key - mandatory
            EOSLIB_SERIALIZE(staked, (owner)(eos_balance))  
        };

        typedef eosio::multi_index< N(staked), staked> staked_index;
        staked_index     _staked;

        bool has_acc_in_index(const account_name user) {    
            return _staked.find( user ) == _staked.end();
        }

        eosio::multi_index< N(staked), staked>::const_iterator create_acc_in_index(const account_name user) {
            return _staked.emplace(_self, [&](auto& acnt){
               acnt.owner = user;
            });
        }
};

EOSIO_ABI(simpleStake, (stake)(unstake)(amount))