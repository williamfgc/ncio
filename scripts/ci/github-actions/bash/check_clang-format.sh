#!/bin/bash

# Checks for clang-format version 10 in Ubuntu GitHub Action runner
sudo apt-get install clang-format-10 -y
wget https://raw.githubusercontent.com/Sarcasm/run-clang-format/master/run-clang-format.py
python3 run-clang-format.py \
        -r bindings/CXX17 source testing \
        --clang-format-executable /usr/bin/clang-format-10 \
        --extensions "h,tcc,cpp"
                