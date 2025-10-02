#!/bin/bash
all_files=($(find srcs/program -name "*.c"))
all_files+=(include/*)

divider() {
	printf '%*s' "$(tput cols)" '' | tr ' ' '-'
}
update() {
	clear
	date
	divider
	# gcc "$script" -L../minilibx-linux -lmlx -lXext -lX11 -lm -o cub3d
	make fclean 
	sleep 1
	make && ./cub3d maps/fun_1.cub
	# [[ $? != 0 ]] && { echo 'fail compile'; return 1; } \
	divider
}
om=0
while true; do
	for script in "${all_files[@]}"; do
		[[ "$(uname -s)" == "Darwin" ]] \
			&& nm=$(stat -f %m "$script") \
			|| nm=$(stat -c %Y "$script")
		if [[ $nm > $om ]]; then
			om=$nm
			update
		fi
	done
	read -t 2 && exit
done
