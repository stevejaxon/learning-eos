#include <eosiolib/eosio.hpp>

using namespace eosio;
using std::string;

class simpleMessageSender : public contract {
  public:
    using contract::contract;

    /*
     * Note: requires the following command to be called in order to give the function permission to msg.sender to execute the inline code.
     * <code>
     * cleos set account permission msg.sender active '{"threshold": 1, "keys":[{"key":"EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV", "weight":1}], "accounts":[{"permission":{"actor":"msg.sender","permission":"eosio.code"},"weight":1}], "waits":[] }' owner -p msg.sender
     * </code>
     * Issuing the following command:
     * <code>
     * cleos push action msg.sender send '["msg.sender"]' -p msg.sender
     * </code>
     * Results in the following output:
     * <code>
     * executed transaction: aa6386bef110952f0f8122d1c3f8cc8c75015b42655460f47a28c33c6c4971e2  104 bytes  508 us
     * #    msg.sender <= msg.sender::send             {"from":"msg.sender"}
     * #  msg.receiver <= msg.receiver::receive        {"msg":"Hello Receiver!"}
     * >> Received the message Hello Receiver!
     * </code>
     */
    /// @abi action
    void send(const account_name from) {
      action(
        permission_level{ from, N(active) },
        N(msg.receiver), N(receive),
        std::make_tuple(std::string("Hello Receiver!"))
      ).send();
    } 
};

EOSIO_ABI(simpleMessageSender, (send))