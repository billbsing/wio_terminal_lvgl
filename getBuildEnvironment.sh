#!/bin/bash

BUILD_FOLDER=buildEnvironment
rm -rf $BUILD_FOLDER
mkdir $BUILD_FOLDER
cd $BUILD_FOLDER
git clone https://github.com/sudar/Arduino-Makefile.git
