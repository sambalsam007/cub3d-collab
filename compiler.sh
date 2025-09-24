#!/bin/bash

script="srcs/program/process_main.c"
divider() {
	printf '%*s' "$(tput cols)" '' | tr ' ' '-'
}
update() {
	clear
	date
	divider
	# gcc "$script" -L../minilibx-linux -lmlx -lXext -lX11 -lm -o cub3d
	make
	[[ $? != 0 ]] && { echo 'fail compile'; return 1; }
	./cub3d
	divider
}
om=0
while true; do
	nm=$(stat -c %Y "$script")
	if [[ $nm > $om ]]; then
		om=$nm
		update
	fi
	read -t 2 && exit
done
