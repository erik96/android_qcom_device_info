ariesve_device_info
===================

Simple C++ binary for various kernel and ROM related informations


An ARM g++ toolchain will be needed to build. I recommend arm-gnueabi-g++ from here: https://github.com/Christopher83/toolchains
Once the path is exported (export CC={PATH_TO_TOOLCHAIN}) run "make all".
The output binary is named "dinfo" and can be used on any armv5+ device.
