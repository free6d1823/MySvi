#!/bin/bash
rm -f compile.log
make clean
make >& compile.log
if [ $? -eq 0 ]
then
  echo "Executable successfully made"
else
  echo "Could not compile make status = $? " >&2
  exit 1
fi
# execute the test case
./cinit_main.exe
