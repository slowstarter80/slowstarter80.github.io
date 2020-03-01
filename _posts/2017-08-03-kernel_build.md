---
layout: single
title: kernel build
categories: [linux, kernel ]
tags: [linux, kernel]
comments: true
date : 2020-01-15 01:33:04 +0900
last_modified_at: 2020-03-01 23:46:01 +0900
---

# kernel build

## kernel module build

  * Loadable module goals - obj-m
    * $(obj-m) specify object files which are built as loadable kernel modules.
    * A moudle may be built from one source file or several source files.
    * ex) built from one source file
          In Makefile
        ```make
obj-S(CONFIG_ISDN_PPP_BSDCOMP) += isdn_bsdcomp.o
#Note : In this example $(CONFIG_ISDN_PPP_BSDCOMP) evaluates to 'm'
        ```
    * ex) built from several source files.a $(<module_name>-y) variable have to be set.
          In Makefile
        ```make
#drivers/isdn/i4l/Makefile
obj-$(CONFIG_ISDN_I4L) += isdn.o
isdn-y := isdn_net_lib.o isdn_v110.o isdn_common.o
        ```
    * Is below also available???
      In Makefile
        ```make
#drivers/isdn/i4l/Makefile
obj-$(CONFIG_ISDN) += isdn.o
isdn-objs := isdn_net_lib.o isdn_v110.o isdn_common.o
        ```

  * How to build loadable module
    * Pre-condition
      * Need full kernel source code
      * Kernel image need to be built before module build(some files which are compiled during kernel build are used when module build)
    * make -C <path-to-kernel> M=`pwd` modules
      * <path-to-kernel> means kernel output directory which is generated during kernel build
      * '-C' means to change to directory <path-to-kernel> before reading the makefiles or doing anything else.
      * 'M' means the path of source files that will be used at module build.\\ Output files of module build will be generated at this path
    * ex) In Makefile
        ```make
obj-m += mm_struct.o
        ```

    * ex) mm_struct.c
      ```c
      #include <linux/kernel.h>
      #include <linux/module.h>
      #include <linux/init.h>
      #include <linux/sched.h>

      int __init module_start(void)
      {
              struct task_struct *task;

              for_each_process(task){
                      printk("task_id = %d, task_comm = %s\n", task->pid, task->comm);
              }
              printk("\n");

              for(task = current; task != &init_task; task = task->parent){
                      printk("task_id = %d, task_comm = %s\n", task->pid, task->comm);
              }

              return 0;
      }

      void __exit module_end(void)
      {
              printk("mm_struct exit!!!\n");
      }

      module_init(module_start);
      module_exit(module_end);

      MODULE_LICENSE("GPL");
      ```

    * After build completed, run this command and check 'dmesg'
        ```bash
$ insmod mm_struct.ko</code>
        ```
    * Run this command to remove the inserted module
        ```bash
$ rmmod mm_struct
        ```
