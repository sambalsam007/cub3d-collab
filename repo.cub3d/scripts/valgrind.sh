#!/bin/bash
c_green="\033[1;32m"
c_red="\033[1;31m"
c_reset="\033[0m"
echo test valgrind
tempdoc=/tmp/cubed.valgrind.testdoc.txt
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

valgrind_ok=()
valgrind_fail=()
invalid_free=()
flagged_maps=()
test_maps=($(find test-maps))
for map in "${test_maps[@]}"; do
	div
	echo -e "current map : $map"
	valgrind ./cub3D "$map" >"$tempdoc" 2>&1
	no_leaks=0
	if grep -q "FLAGGED" "$tempdoc"; then
		flagged_maps+=($map)
	fi
	if grep -q "Invalid free" "$tempdoc"; then
		invalid_free+=($map)
	fi
	if grep -q "no leaks" "$tempdoc"; then
		valgrind_ok+=($map)
		no_leaks=1
		div; printf ${c_green}; 
		echo -e "✅ valgrind : OK : $map"; div
		awk '{if ($0 ~ /no leaks/) print "\033[1;32m" $0 "\033[0m"; else print $0}' "$tempdoc"
	else
		valgrind_fail+=($map)
		div; printf ${c_red};
		echo -e "🕱valgrind : NOPE : $map"; div
		printf ${c_reset}
		cat "$tempdoc"
	fi
	echo "no_leaks flag: $no_leaks"
done

div

echo -e "${c_green}✅valgrind OK : "
for v_map in "${valgrind_ok[@]}"; do
	echo "$v_map"
done

div
echo -e "${c_red}🕱valgrind FAIL : "
for v_map in "${valgrind_fail[@]}"; do
	echo "$v_map"
done

div
echo -e "${c_red}🕱invalid free / etc : "
for v_map in "${invalid_free[@]}"; do
	echo "$v_map"
done

div
echo -e "${c_red}🕱FLAGGED MAPS : "
for v_map in "${flagged_maps[@]}"; do
	echo "$v_map"
done

printf "${c_reset}"


make fclean
