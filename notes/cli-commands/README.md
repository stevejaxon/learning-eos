# 

## Launching a node in Docker
The steps required to run an EOS node (and all of the other necessary components) within Docker are documented (with a reasonable level of correctness) in the official [EOS documentation](https://developers.eos.io/eosio-nodeos/docs/docker-quickstart).

However, [LinusU](https://github.com/LinusU) has created [a useful repository](https://github.com/LinusU/linusu-eos) that covers all of the steps in the documentation (and is correct).

From your directory that contains your EOS Smart Contract code, the following commands can be run.

### Start an EOS instance
```
make create -C <path_to_repository>/linusu-eos/
```

### Unlocking the default account created at startup
```
make unlock -C <path_to_repository>/linusu-eos/
```

### Stopping the EOS instance
```
make destroy -C <path_to_repository>/linusu-eos/
```

## Useful Docker Alias commands
Useful commands aliasing 'components' on EOS.
If you are running an EOS node in a Docker container then it is useful to be able to interact with the different command line utilities by just issuing a command from outside of the container to those services running inside of Docker. 
Here are some useful alias commands to simplify things: 

```
alias cleos='docker exec -it eosio /opt/eosio/bin/cleos -u http://localhost:8888'
alias keosd='docker exec -it eosio /opt/eosio/bin/keosd --wallet-url http://localhost:8888'
alias eosiocpp='docker exec -it eosio /opt/eosio/bin/eosiocpp -u http://localhost:8888'
```
