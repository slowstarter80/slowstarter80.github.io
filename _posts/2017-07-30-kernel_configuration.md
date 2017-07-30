---
layout: post
title: kernel configuration
categories: [linux, kernel]
tags: [linux, kernel ]
comments: true
--- 


# Kernel configuration
## The way to do kernel configuration
  * Run the following command for a full list of make target
    ```bash
    $ make help
    ```
  * 'O' option in command line or 'KBUILD_OUTPUT' variable in Makefile can be used to set output directory.


  1.  Run 'make' command with pre-defined defconfig file(ex. vexpress_defconfig).  
     Then, '.config' and 'include/generated/autoconf.h' files will be generated in output directory.
        ```bash
        $ make ARCH=arm vexpress_defconfig
        ```

  2. Run the following command to update current configuration. it is menu based configuration tool
        ```bash
        $ make ARCH=arm menuconfig
        ```
  3. Run the following command to build kernel binary. Cross compiler need to be installed if you do cross-platform compilation.  
Kernel binary will be generated in output directory
        ```bash
        $ make -j4 ARCH=arm CROSS_COMPILE=armv7a-hardfloat-linux-gnueabi- all
        ```

## The way to do kernel configuration
  * 'O' option in command line or KBUILD_OUTPUT in makefile  
    _**- Makefile at the root of the kernel source**_
    ```make
    # kbuild supports saving output files in a separate directory.
    # To locate output files in a separate directory two syntaxes are supported.
    # In both cases the working directory must be the root of the kernel src.
    # 1) O=
    # Use "make O=dir/to/store/output/files/"
    #
    # 2) Set KBUILD_OUTPUT
    # Set the environment variable KBUILD_OUTPUT to point to the directory
    # where the output files shall be placed.
    # export KBUILD_OUTPUT=dir/to/store/output/files/
    # make
    #
    # The O= assignment takes precedence over the KBUILD_OUTPUT environment
    # variable.
    ```
  * Almost all source files related with kernel configuration are in 'scripts' folder at the root of the kernel source
  * 'config' and 'include/generated/autoconf.h' files are generated after kernel configuration  
    _**- scripts/kconfig/confdata.c**_
    ```c
    int conf_write_autoconf(void);   //autoconf.h
    int conf_write(const char *name);    //.config  
    ```

  * _**- include/linux/kconfig.h**_
    ```c
    #include <generated/autoconf.h>
    ```

  * _**- Makefile at the root of the kernel source**_
    ```make
    # Use USERINCLUDE when you must reference the UAPI directories only.
    USERINCLUDE    := \
                    -I$(srctree)/arch/$(hdr-arch)/include/uapi \
                    -Iarch/$(hdr-arch)/include/generated/uapi \
                    -I$(srctree)/include/uapi \
                    -Iinclude/generated/uapi \
                    -include $(srctree)/include/linux/kconfig.h
     
    # Use LINUXINCLUDE when you must reference the include/ directory.
    # Needed to be compatible with the O= option
    LINUXINCLUDE    := \
                    -I$(srctree)/arch/$(hdr-arch)/include \
                    -Iarch/$(hdr-arch)/include/generated/uapi \
                    -Iarch/$(hdr-arch)/include/generated \
                    $(if $(KBUILD_SRC), -I$(srctree)/include) \
                    -Iinclude \
                    $(USERINCLUDE)
    ```
