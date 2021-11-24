Minimal project that uses autoconf and automake to demonstrate an
issue with android ndk r23, see
https://github.com/android/ndk/issues/1614.

To test:

```
git clone https://github.com/grimler91/minimal-ndk-r23-issue-example
cd minimal-ndk-r23-issue-example

aclocal
libtoolize --copy
autoconf
automake --add-missing --foreign

# Adjust for path to your ndk
TOOLCHAINROOT=/opt/android-ndk/toolchains/llvm/prebuilt/linux-x86_64
CCPREFIX=$TOOLCHAINROOT/bin/aarch64-linux-android28-

# Optimization level seem to make a difference
CXXFLAGS=-O0 CXX=${CCPREFIX}clang++ CC=${CCPREFIX}clang ./configure --host=aarch64-linux-android --prefix=$(pwd)

make
make install

# Push compiled program, library and libc++_shared to device
adb push bin/main lib/libtest.so $TOOLCHAINROOT/sysroot/usr/lib/aarch64-linux-android/libc++_shared.so /data/local/tmp/

# Try to run the program on device:
adb shell
$ cd /data/local/tmp
$ LD_PRELOAD=./libtest.so:./libc++_shared.so ./main
```

You should get something like:

```
WARNING: linker: Warning: "/data/local/tmp/libc++_shared.so" unused DT entry: unknown processor-specific (type 0x70000001 arg 0x0) (ignoring)
CANNOT LINK EXECUTABLE "./main": cannot locate symbol "__extenddftf2" referenced by "/data/local/tmp/libtest.so"...
```

Where the missing `__extenddftf2` symbol comes from the use of
`static_cast<long double>` in test.cpp.
