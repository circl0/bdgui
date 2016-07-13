#! /bin/sh

export PATH="$PATH:/home/circl0/mini2440/toolschain/4.4.3/bin"
cd $1
cd build
rm * -rf
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/Toolchain_arm-linux.cmake -DSYSROOT=/home/circl0/mini2440/toolschain/4.4.3/arm-none-linux-gnueabi/sys-root/usr ..
make