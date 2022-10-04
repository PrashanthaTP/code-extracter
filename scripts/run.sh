#!/bin/env bash

curr_dir=$(dirname ${BASH_SOURCE[0]})
# project_dir/scripts

mingw32-make.exe -s --file ${curr_dir}/../Makefile run
