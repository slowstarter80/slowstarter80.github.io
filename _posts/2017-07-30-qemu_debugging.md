---
layout: post
title: qemu를 이용한 kernel booting process debugging
categories: [linux, kernel, debugging]
tags: [linux, kernel, debugging, gdb]
comments: true
--- 

# qemu 
## qemu-system-arm
  * run ARM virtual machine 
  * kernel build
    * ex)
        ```bash
        $ cd linux
        $ make ARCH=arm vexpress_defconfig O=out
        $ make ARCH=arm menuconfig O=out
        $ make -j4 ARCH=arm CROSS_COMPILE=armv7a-hardfloat-linux-gnueabi- all O=out
    	```
  * init process
    * ex) init.c
      ```c 
      #include <stdio.h>

      int main(int argc, char* argv[])
      {
		printf("\n");
      		printf("My Gentoo ARM Init!!!\n");
         
        	for (int i = 0; i < 100; i++)
		{
        		sleep(1);
        	}
         
      		return 0;
      }

      ```
    * compilation
    ```bash
    $ armv7a-hardfloat-linux-gnueabi-gcc -static init.c -o init
    ```
    * making initrd filesystem
    ```bash
    $ echo init | cpio -o --format=newc > initrd
    ```
  * run qemu
    * ex) need to set proper path
    ```bash
    $ qemu-system-arm -M vexpress-a15 -m 1G -kernel out/arch/arm/boot/zImage -initrd init/initrd -append "root=/dev/ram rdinit=init" -dtb out/arch/arm/boot/dts/vexpress-v2p-ca15_a7.dtb -s -S
    ```
  * run arm gdb(armv7a-hardfloat-linux-gnueabi-gdb)
    * debugging kernel decompression code
      * ex) vexpress-a15 will begin in the starting address is 0x80000000 RAM, after initialization of ATAGS(dtb) and processor ID, it will jump to the 0x80010000

         ```c
         (gdb) target remote:1234
         Remote debugging using :1234
         warning: Can not parse XML target description; XML support was disabled at compile time
         0x80000000 in ?? ()
         
         (gdb) b *0x80010000
         Breakpoint 1 at 0x80010000
         
         (gdb) c
         Continuing.
         
         Breakpoint 1, 0x80010000 in ?? ()
         
         (gdb) load out/arch/arm/boot/compressed/vmlinux 0x80010000
         Loading section .text, size 0x38f4 lma 0x80010000
         Loading section .rodata, size 0xcc4 lma 0x800138f4
         Loading section .piggydata, size 0x34e801 lma 0x800145b8
         Loading section .got.plt, size 0xc lma 0x80362dbc
         Loading section .got, size 0x28 lma 0x80362dc8
         Loading section .pad, size 0x8 lma 0x80362df0
         Start address 0x0, load size 3485173
         Transfer rate: 8863 KB/sec, 2026 bytes/write.
         
         (gdb) add-symbol-file out/arch/arm/boot/compressed/vmlinux 0x80010000
         add symbol table from file "out/arch/arm/boot/compressed/vmlinux" at
         	.text_addr = 0x80010000
         (y or n) y
         Reading symbols from out/arch/arm/boot/compressed/vmlinux...done.
         
         (gdb) set $pc=0x80000000
         
         (gdb) si
         0x80000004 in ?? ()
         (gdb)
         ```
    * debugging kernel code
      * ex) vexpress-a15
        * Physical address is 0x80000000 and virtual address is 0xC0000000. Therefore, “-0x40000000” offset is needed when load vmlinux
        * We can know “.text” address by using “armv7a-hardfloat-linux-gnueabi-readelf -S out/vmlinux”

            ```c 
            (gdb) target remote:1234
            Remote debugging using :1234
            warning: Can not parse XML target description; XML support was disabled at compile time
            0x80000000 in ?? ()
            
            (gdb) b *0x80008000
            Breakpoint 1 at 0x80008000
            
            (gdb) c
            Continuing.
            
            Breakpoint 1, 0x80008000 in ?? ()
            
            (gdb) load out/vmlinux -0x40000000
            Loading section .head.text, size 0x26c lma 0x80008000
            Loading section .text, size 0x49c984 lma 0x80008280
            Loading section .fixup, size 0x28 lma 0x804a4c04
            Loading section .rodata, size 0x12f000 lma 0x804a5000
            Loading section __bug_table, size 0x5c70 lma 0x805d4000
            Loading section __ksymtab, size 0x6cb0 lma 0x805d9c70
            Loading section __ksymtab_gpl, size 0x5920 lma 0x805e0920
            Loading section __ksymtab_strings, size 0x1caa5 lma 0x805e6240
            Loading section __param, size 0xce4 lma 0x80602ce8
            Loading section __modver, size 0x634 lma 0x806039cc
            Loading section __ex_table, size 0xf88 lma 0x80604000
            Loading section .ARM.unwind_idx, size 0x227d8 lma 0x80604f88
            Loading section .ARM.unwind_tab, size 0x2eb0 lma 0x80627760
            Loading section .notes, size 0x24 lma 0x8062a610
            Loading section .vectors, size 0x20 lma 0x8062b000
            Loading section .stubs, size 0x2c0 lma 0x8062b020
            Loading section .init.text, size 0x26368 lma 0x8062b2e0
            Loading section .exit.text, size 0x1254 lma 0x80651648
            Loading section .init.arch.info, size 0xd0 lma 0x8065289c
            Loading section .init.tagtable, size 0x40 lma 0x8065296c
            Loading section .init.smpalt, size 0xae68 lma 0x806529ac
            Loading section .init.pv_table, size 0x728 lma 0x8065d814
            Loading section .init.data, size 0xec54 lma 0x8065e000
            Loading section .data..percpu, size 0x48c0 lma 0x8066d000
            Loading section .data, size 0x275e0 lma 0x80672000
            Loading section .data..page_aligned, size 0x1000 lma 0x8069a000
            Start address 0xc0008000, load size 6884473
            Transfer rate: 9311 KB/sec, 2023 bytes/write.
            
            (gdb) add-symbol-file out/vmlinux 0x80008280            #after enabling MMU, the offset is 0xc0008280
            add symbol table from file "out/vmlinux" at
            	.text_addr = 0x80008280
            (y or n) y
            Reading symbols from out/vmlinux...done.
            
            (gdb) set $pc=0x80008000
            
            (gdb)
            
            ```
  * reference
    * [http://norux.me/38](http://norux.me/38)

## qemu-arm
  * Run arm application programs on x86 or amd64
  * ex)
  ```bash
  $ qemu-arm mov
  ```
  * ex) to debug width gdb, add '-g port' option to command 
  ```bash
  $ qemu-arm -g 5039 mov
  ```
  * ex) run gdb and execute gdb command
   ```c
    $ armv7a-hardfloat-linux-gnueabi-gdb
    GNU gdb (Gentoo 7.11.1 vanilla) 7.11.1
    Copyright (C) 2016 Free Software Foundation, Inc.
    License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
    This is free software: you are free to change and redistribute it.
    There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
    and "show warranty" for details.
    This GDB was configured as "--host=x86_64-pc-linux-gnu --target=armv7a-hardfloat-linux-gnueabi".
    Type "show configuration" for configuration details.
    For bug reporting instructions, please see:
    <https://bugs.gentoo.org/>.
    Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.
    For help, type "help".
    Type "apropos word" to search for commands related to "word".
    
    
    (gdb) file mov
    Reading symbols from mov...done.
    
    
    (gdb) target remote:5039
    Remote debugging using :5039
    warning: Can not parse XML target description; XML support was disabled at compile time
    0x00010414 in _start ()
    
    
    (gdb) b main
    Breakpoint 1 at 0x10590: file mov.c, line 34.
    
    
    (gdb) c
    Continuing.
    
    Breakpoint 1, main () at mov.c:34
    34              printf("\n+-------------------+\n");
    (gdb)
   ```

# gdb
## gdb command
  * file, load, add-symbol-file의 차이가 무엇인가?
    * file
    ```
    Use FILE as program to be debugged.
    It is read for its symbols, for getting the contents of pure memory,
    and it is the program executed when you use the `run' command.
    If FILE cannot be found as specified, your execution directory path
    ($PATH) is searched for a command of that name.
    No arg means to have no executable file and no symbols.
    ```
    * load
    ```
    Dynamically load FILE into the running program, and record its symbols for access from GDB.
    A load OFFSET may also be given.
    ```
    * add-symbol-file
    ```
    Load symbols from FILE, assuming FILE has been dynamically loaded.
    Usage: add-symbol-file FILE ADDR [-s <SECT> <SECT_ADDR> -s <SECT> <SECT_ADDR> ...]
    ADDR is the starting address of the file's text.
    The optional arguments are section-name section-address pairs and
    should be specified if the data and bss segments are not contiguous
    with the text.  SECT is a section name to be loaded at SECT_ADDR.
    ```

