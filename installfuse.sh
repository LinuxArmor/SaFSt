#!/usr/bin/env bash
sudo apt-get install -y git meson
git clone https://github.com/libfuse/libfuse
cd libfuse
mkdir build
cd build
meson ..
ninja
sudo ninja install
cd ../..
rm -r libfuse
echo "done!"
