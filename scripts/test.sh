#!/bin/env bash
seperator(){
    printf "\n----------------------------\n"
}

root_dir=$(git rev-parse --show-toplevel)
cd "${root_dir}/bin"


seperator
echo "[#1] ./main a"
./main -a
seperator

echo "[#2] ./main --aytala"
./main --aytala
seperator

echo "[#3] ./main -i"
./main -i
seperator

echo "[#4] ./main --input input_file/path"
./main -i input_file/path
seperator
echo "[#4] ./main -i input_file/path"
./main -i input_file/path
seperator

echo "[#5] ./main -o"
./main -o
seperator

echo "[#6] ./main --output output_file/path"
./main -o output_file/path
seperator
echo "[#6] ./main -o output_file/path"
./main -o output_file/path
seperator

echo "[#7] ./main -u"
    ./main -u

seperator

input_file=${root_dir}/temp/src.md
output_file=${root_dir}/temp/output.md
lang=python
echo "[#8] ./main --input ${input_file} --output ${output_file} --lang ${lang}"
./main --input ${input_file} --output ${output_file} --lang ${lang}

seperator

input_file=${root_dir}/temp/src.md
output_file=${root_dir}/temp/dest.md
echo "[#8] ./main --input ${input_file} --output ${output_file}"
./main --input ${input_file} --output ${output_file}
