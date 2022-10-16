#!/bin/env bash

root_dir=$(git rev-parse --show-toplevel 2>/dev/null)
[ -z "${root_dir}" ] && root_dir="../"

cd ${root_dir}/lib
mkdir -p libsystre
if [ ! -f libsystre/mingw-w64-i686-libsystre-1.0.1-4-any.pkg.tar.xz ];then
    curl https://mirror.msys2.org/mingw/mingw32/mingw-w64-i686-libsystre-1.0.1-4-any.pkg.tar.xz -o libsystre/mingw-w64-i686-libsystre-1.0.1-4-any.pkg.tar.xz
fi


xz --keep --decompress  libsystre/mingw-w64-i686-libsystre-1.0.1-4-any.pkg.tar.xz
tar -xvf libsystre/mingw-w64-i686-libsystre-1.0.1-4-any.pkg.tar -C libsystre
