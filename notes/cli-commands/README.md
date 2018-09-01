# 

## Launching a node in Docker
The steps required to run an EOS node (and all of the other necessary components) within Docker are documented (with a reasonable level of correctness) in the official [EOS documentation](https://developers.eos.io/eosio-nodeos/docs/docker-quickstart).

However, [LinusU](https://github.com/LinusU) has created [a useful repository](https://github.com/LinusU/linusu-eos) that covers all of the steps in the documentation (and is correct).

From your directory that contains your EOS Smart Contract code, the following commands can be run.

### Start an EOS instance
```
make create -C <path_to_repository>/linusu-eos/ MOUNT_DIR=<path_to_workspace>
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
alias eosiocpp='docker exec -it eosio /opt/eosio/bin/eosiocpp
```

## Smart Contracts
### Compiling your code
The code can be compiled using the `eosiocpp` component that is part of the Docker container.
```
eosiocpp -o <dest_file>.wast <source_file>.cpp
```
For example to compile the `Hello World` Smart Contract use the following command:
```
eosiocpp -o /work/contracts/helloWorld/helloWorld.wast /work/contracts/helloWorld/helloWorld.cpp
```
*Note: the source files should be referenced relative to the mount point in the Docker image: `/work`*

### Generating the ABI
For example to generate the ABI for the `Hello World` Smart Contract use the following command:
```
eosiocpp -g /work/contracts/helloWorld/helloWorld.abi /work/contracts/helloWorld/helloWorld.cpp
```

### Creating an account for the Smart Contract

Unlock the `default` account:
```
cleos wallet unlock --password "$(docker exec -it eosio cat /default-wallet-password | tr -d '[:space:"]')"
```
Create an account for the Smart Contract that is named similarly to the contract (must be 12 characters or less):
```
PUB_KEY="$(docker exec -it eosio tail -n 1 /default-key | cut -c 13- | tr -d '[:space:]')"
cleos create account eosio <account_name> $PUB_KEY $PUB_KEY
```

### Deploying the Smart Contract

```
cleos set contract helloworld /work/contracts/helloWorld -p helloworld@active
```

### Calling a Smart Contract's functions
Calling the `hi` function:
```
cleos push action helloworld hi '[]' -p user@active
``
Results in the expected output:
```
executed transaction: fced489b6456bbd2113f940e62c64298fbb4adabab54f46e8178b93ab93b7a7c  96 bytes  341 us
#    helloworld <= helloworld::hi               ""
>> Hello, I'm the contract helloworld
```
Calling the `verify` function with the current user's ID: `user`
```
cleos push action helloworld verify '["user"]' -p user@active
```
Results in the expected output:
```
executed transaction: d54772d0d5a6b42609a11284652f47eeb9f92f0583909f7ee95a123028f08dcd  104 bytes  281 us
#    helloworld <= helloworld::verify           {"user":"user"}
>> Verified as being user
```
Calling the `verify` function with the wrong user name:
```
cleos push action helloworld verify '["user2"]' -p user@active
```
Results in the expected failure
```
Error 3090004: Missing required authority
Ensure that you have the related authority inside your transaction!;
If you are currently using 'cleos push action' command, try to add the relevant authority using -p option.
```