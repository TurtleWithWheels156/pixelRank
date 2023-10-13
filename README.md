Problem: 
- Given a grayscale image from an image sensor in memory with each 16-bit word equating to a pixel value, write a program to find the 50 pixels (including their location) with the highest pixel values. This program should be written in C. It should compile and run correctly. Please also provide any assumptions made in solving the problem.

Solution: 
- After doing some research, I determined that I would use a C/C++ library called libtiff, whose primary purpose is to allow for an easy interface with TIFF files and their data.  I chose my program input to process .tif files since most cameras support this type of file type and is preferred by photographers and artists alike.  Furthermore, it is one of the few image file types that allows for 16-bit depth for coloring (grayscale images in this case).
- The implentation is as follows: Prompt the user to input a valid filepath to a .tif file that adheres to the 16-bit depth grayscale image criteria.  I created some bundled test examples in ImageJ that can be referenced when using the program.  After putting a valid filepath in, libtiff opens the file and uses TIFFGetField to return relevant fields needed for processing, such as image dimensions and number of samples per pixel (which should be 1 for grayscale).
- After confirming it is a grayscale image, the program uses TIFFReadScanline to read the image row by row and loads the data into a supplied data buffer. The data from the buffer is then processed and put into an array of running top ranks of values (where the range is from 0 - 65535), where incoming data from the updated buffer is either stored and sorted into its rightful priority or tossed if smaller than the smallest value.  The final step is displaying the rankings as well as the pixel position associated as well as freeing up any memory and closing the .tif file.

Usage:
- Install the libtiff library to local environment
    - e.g. My env is on Mac so I installed with `brew install libtiff`
    - For debian, use `sudo apt-get install libtiff5-dev` 
- The program is compiled with the following command: `gcc --ansi --pedantic main.c pixel.c -ltiff`
- Run ./a.out and follow the user prompts
- Download ImageJ to create custom grayscale images or use the ones bundled with the code.


Links
- http://www.libtiff.org/man/
- https://imagej.nih.gov/ij/download.html

Misc. Notes
- GCC Config for Mac Test
Configured with: --prefix=/Library/Developer/CommandLineTools/usr --with-gxx-include-dir=/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk/usr/include/c++/4.2.1
Apple clang version 13.0.0 (clang-1300.0.29.3)
Target: arm64-apple-darwin21.1.0
Thread model: posix
InstalledDir: /Library/Developer/CommandLineTools/usr/bin

- GCC Config for Debian Test
Using built-in specs.
COLLECT_GCC=gcc
COLLECT_LTO_WRAPPER=/usr/lib/gcc/x86_64-linux-gnu/8/lto-wrapper
OFFLOAD_TARGET_NAMES=nvptx-none
OFFLOAD_TARGET_DEFAULT=1
Target: x86_64-linux-gnu
Configured with: ../src/configure -v --with-pkgversion='Ubuntu 8.4.0-1ubuntu1~18.04' --with-bugurl=file:///usr/share/doc/gcc-8/README.Bugs --enable-languages=c,ada,c++,go,brig,d,fortran,objc,obj-c++ --prefix=/usr --with-gcc-major-version-only --program-suffix=-8 --program-prefix=x86_64-linux-gnu- --enable-shared --enable-linker-build-id --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --libdir=/usr/lib --enable-nls --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --with-default-libstdcxx-abi=new --enable-gnu-unique-object --disable-vtable-verify --enable-libmpx --enable-plugin --enable-default-pie --with-system-zlib --with-target-system-zlib=auto --enable-objc-gc=auto --enable-multiarch --disable-werror --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --enable-multilib --with-tune=generic --enable-offload-targets=nvptx-none --without-cuda-driver --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu
Thread model: posix
gcc version 8.4.0 (Ubuntu 8.4.0-1ubuntu1~18.04)
