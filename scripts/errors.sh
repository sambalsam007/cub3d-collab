#!/bin/bash
c_green="\033[1;32m"
c_red="\033[1;31m"
c_reset="\033[0m"
echo test errors
tempdoc=/tmp/cubed.errors.testdoc.txt
:>"$tempdoc"
map="test-maps/valid/valid-basic.cub"

make fclean
make

div()
{
	printf "${c_reset}"
	printf '%*s\n' "$(tput cols)" '' | tr ' ' '_'
	printf '\n'
}

test_result_0_ok=()
test_result_1_ok=()
test_result_0_nope=()
test_result_1_nope=()
flagged_maps=()
test_maps=($(find test-maps))
for map in "${test_maps[@]}"; do
	div
	echo -e "current map : $map"
	./cub3D "$map" >"$tempdoc" 2>&1
	_return=$?
	cat "$tempdoc"
	if grep -q "FLAGGED" "$tempdoc"; then
		flagged_maps+=($map)
	fi
	if grep -q "ok" <<< "$map" ; then
		if (( $_return == 0 )); then
			echo -e "expected (0)\nreturn($_return)"
			test_result_0_ok+=($map)
		else
			echo -e "expected (0)\nreturn($_return)"
			test_result_0_nope+=($map)
		fi
	fi
	if grep -q "err" <<< "$map" ; then
		if (( $_return != 0 )); then
			echo -e "expected (non-zero)\nreturn($_return)"
			test_result_1_ok+=($map)
		else
			echo -e "expected (non-zero)\nreturn($_return)"
			test_result_1_nope+=($map)
		fi
	fi
done

div; echo -e "${c_green}✅ expected return 0, got return 0\n"; 
for v_map in "${test_result_0_ok[@]}"; do echo "$v_map"; done

div; echo -e "${c_green}✅ expected return non-zero, got return non-zero\n"
for v_map in "${test_result_1_ok[@]}"; do echo "$v_map"; done

div; echo -e "${c_red}✖ expected return 0, got return non-zero\n"
for v_map in "${test_result_0_nope[@]}"; do echo "$v_map"; done

div; echo -e "${c_red}✖ expected return non-zero, got return 0\n"
for v_map in "${test_result_1_nope[@]}"; do echo "$v_map"; done

printf "${c_reset}"


