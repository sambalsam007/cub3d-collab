#!/bin/bash
all_files=($(find srcs/ -name "*.c"))
all_files+=(include/*)

divider() {
	printf '%*s' "$(tput cols)" '' | tr ' ' '-'
}
update() {
	clear;
	date
	divider
	# gcc "$script" -L../minilibx-linux -lmlx -lXext -lX11 -lm -o cub3d
	make fclean 
	make
	./cub3d maps/fun_1.cub
	# [[ $? != 0 ]] && { echo 'fail compile'; return 1; } \
	divider
}


om=0
for file in "${all_files[@]}"; do
	nm=$(stat -c %Y "$file")
	(( $nm > $om )) && om=$nm
done

update

while true; do
	for file in "${all_files[@]}"; do
		nm=$(stat -c %Y "$file")
		if (( $nm > $om )); then
			om=$nm
			update
		fi
	done
	read -t 1 && exit
done


