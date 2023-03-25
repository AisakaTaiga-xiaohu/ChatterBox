# File Name:autobuild.sh
# Author: Xiaohu
# Create Time: 2023年03月25日 星期日 15:42:36
#!/bin/bash

set -x

rm -rf `pwd`/build/*
cd `pwd`/build &&
   cmake .. &&
   make

