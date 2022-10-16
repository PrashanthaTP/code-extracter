#!/bin/env bash
#download std library files from gnulib

reg_files=(
regex-quote.c
regex-quote.h
regex.c
regex.h
regex_internal.c
regex_internal.h
regexec.c
libc-config.h #needed by regex.c
cdefs.h       #needed by libc-config.h
langinfo.h
)

yellow='\033[32m'
blue='\033[34m'
resetc='\033[0m'

root_dir=$(git rev-parse --show-toplevel 2>/dev/null)
[ -z "${root_dir}" ] && root_dir="../"
cd ${root_dir}/lib/regex
for file in ${reg_files[@]};do
    echo -e "${yellow}[curl]${reset} gnulib ${file}"
    echo -en "${blue}"
    curl --remote-name https://raw.githubusercontent.com/coreutils/gnulib/master/lib/${file}
    echo -en "${reset}"
done
cd -
