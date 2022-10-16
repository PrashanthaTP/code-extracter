#!/bin/env bash

root_dir=$(git rev-parse --show-toplevel 2>/dev/null)
[ -z "${root_dir}" ] && root_dir="../"
cd ${root_dir}
mingw32-make.exe --file Makefile_Lib "$@"
