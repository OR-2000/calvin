#!/bin/bash

# 引数の処理
if [ "$1" == "m" ]; then
    ARGUMENT="m"
elif [ "$1" == "t" ]; then
    ARGUMENT="t"
else
    ARGUMENT="m"  # デフォルト値を"m"とする
fi

rm -rf src obj
cp -r src_calvin_opt_opt/ src
cp definitions.hh src/common/definitions.hh
cd src
make clean
make -j
cd ../
bin/deployment/db 0 "$ARGUMENT" 0