#!/bin/bash

# install rust
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
source "$HOME/.cargo/env"

# other dependencies
apt install git zlib1g-dev python-is-python3 -y

# llvm
export LLVM_HOME=/path/to/llvm-10.0.0-install
export PATH=$LLVM_HOME/bin:$PATH
export LD_LIBRARY_PATH=$LLVM_HOME/lib:$LD_LIBRARY_PATH

./build.sh