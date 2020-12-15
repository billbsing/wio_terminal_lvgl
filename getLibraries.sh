#!/bin/bash

LIBRARY_FOLDER=libraries
rm -rf $LIBRARY_FOLDER
mkdir $LIBRARY_FOLDER
cd $LIBRARY_FOLDER
# git clone https://github.com/Seeed-Studio/Seeed_Arduino_LvGL.git
git clone https://github.com/lvgl/lvgl.git
cp ../lvgl_include/lv_conf.h .
