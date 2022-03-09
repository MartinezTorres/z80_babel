#!/bin/bash

cargo build --release > /dev/null 2>&1

echo "-L dependency="`pwd`"/target/avr-unknown-gnu-atmega328/release/deps"
echo "--extern noprelude:compiler_builtins="`pwd`"/"`find * -name libcompiler*.rlib`
echo "--extern noprelude:core="`pwd`"/"`find * -name libcore*.rlib`
