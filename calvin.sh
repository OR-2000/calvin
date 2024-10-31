#!/bin/bash

# 引数の処理
if [ "$1" == "m" ]; then
    ARGUMENT="m"
elif [ "$1" == "t" ]; then
    ARGUMENT="t"
else
    ARGUMENT="m"  # デフォルト値を"m"とする
fi

# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/calvin/ext/protobuf/src/.libs
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/calvin/ext/zookeeper/.libs
# export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:~/calvin/ext/zeromq/src/.libs

rm -rf src obj
cp -r src_calvin/ src
cp definitions.hh src/common/definitions.hh
cd src
make clean
make -j
cd ../
bin/deployment/db 0 "$ARGUMENT" 0