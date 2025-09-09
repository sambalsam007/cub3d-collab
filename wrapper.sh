#!/bin/bash
flags="$1"
if [[ $flags == *"o"* ]]; then
	echo open
	nvim $(find srcs -name "*.c") $(find . -maxdepth 1 -name "*.sh")
	exit
fi
while true; do
	./compiler.sh "$flags"
done
