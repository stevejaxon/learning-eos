#include "simpleStake.hpp"

/// @abi action
void stake() {
    print("Hello, I'm the contract ");
}

/// @abi action
void unstake(account_name user) {
    require_auth(user);
    print("Verified as being ", name{user});
}

/// @abi action
void amount(const account_name user) {
    print("Hello, I'm the contract ");
}

bool has_acc_in_index(const account_name user) {
    // staked_index stakes( self, user );
    // return stakes.find( user ) == stakes.end();
}