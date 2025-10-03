#!/bin/bash
all_files=($(find srcs/program -name "*.c"))
all_files+=(include/*)

divider() {
	printf '%*s' "$(tput cols)" '' | tr ' ' '-'
}
update() {
	date
	divider
	# gcc "$script" -L../minilibx-linux -lmlx -lXext -lX11 -lm -o cub3d
	make fclean 
	make && clear && ./cub3d maps/fun_1.cub
	# [[ $? != 0 ]] && { echo 'fail compile'; return 1; } \
	divider
}


om=0
while true; do
	for file in "${all_files[@]}"; do
		nm=$(stat -c %Y "$file")
		if (( $nm > $om )); then
			om=$nm
			update
			sleep 1
		fi
	done
	read -t 2 && exit
done


