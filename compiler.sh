#!/bin/bash
flags="$1"
# flags
# m	hide makefile output
# o	open *.c src files
program="./cub3d"
args="maps/fun_1.cub"
files_to_track=(srcs/*.c srcs/*/*.c *.sh)
div() {
	printf '%*s\n' "$(tput cols)" '' | tr ' ' '-'
}
update() {
	clear
	div
	date
	if [[ $flags == *"m"* ]]; then
		make >/tmp/cub3d || make re >/tmp/cub3d
	else
		div
		make || make re 
	fi
	div
	[[ $? != 0 ]] && { echo 'error compiling'; return 1; }
	"$program" $args
	div
}
om=0
while true; do
	for file in "${files_to_track[@]}"; do
		nm=$(stat -c %Y "$file")
		if [[ $nm > $om ]]; then
			om=$nm
			update
		fi
		read -t 1 && exit
	done
done
