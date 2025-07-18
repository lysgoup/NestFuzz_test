#!/bin/bash

apt-get update
apt-get install -y xz-utils cmake ninja-build gcc g++ python3 doxygen python3-distutils
wget https://github.com/llvm/llvm-project/releases/download/llvmorg-10.0.0/llvm-project-10.0.0.tar.xz
tar xf llvm-project-10.0.0.tar.xz
mkdir llvm-10.0.0-install
cd llvm-project-10.0.0
mkdir build
cd build
CC=gcc CXX=g++ cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DLLVM_TARGETS_TO_BUILD=X86 -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra;libcxx;libcxxabi;lldb;compiler-rt" -DCMAKE_INSTALL_PREFIX=/path/to/llvm-10.0.0-install -DCMAKE_EXE_LINKER_FLAGS="-lstdc++" ../llvm
ninja install