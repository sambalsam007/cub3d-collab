#!/bin/bash
other_files=(
srcs/program/utils.c
srcs/program/_s_minimap.c
srcs/program/_s_player.c
srcs/program/_s_render.c
srcs/program/_s2_render.c
srcs/program/_s_rays.c
srcs/program/draw.c
srcs/program/keys.c
srcs/program/player.c
	)
files=(
include/cubed.h
srcs/program/process_main.c
	)
nvim ${files[*]}
