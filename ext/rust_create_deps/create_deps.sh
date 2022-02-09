#!/bin/bash

cargo build --release > /dev/null 2>&1

echo "Add these two flags to compile rust:"
echo

echo "--extern 'noprelude:compiler_builtins="`pwd`"/"`find * -name libcompiler*.rlib`"'"
echo "--extern 'noprelude:compiler_builtins="`pwd`"/"`find * -name libcore*.rlib`"'"
