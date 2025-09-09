#!/bin/bash
flags="$1"
list_flags() {
	echo -e '
	flags
	o	open *.c src files
	h	list all flags
	m	hide makefile output
	'
}
open_all_files() {
	nvim $(find srcs -name "*.c") $(find . -maxdepth 1 -name "*.sh")
}

[[ $flags == *"o"* ]] && open_all_files && exit
[[ $flags == *"h"* ]] && list_flags && exit

while true; do
	./compiler.sh "$flags"
done
