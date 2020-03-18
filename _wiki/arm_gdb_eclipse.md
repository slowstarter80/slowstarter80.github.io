---
layout: single
title: How to use eclipse cdt as front end of arm gdb
date : 2020-01-15 01:33:04 +0900
last_modified_at: 2020-03-19 01:45:35 +0900
categories: [gdb]
tags: [qemu, eclipse cdt, gdb]
comments: true
public : true
parent : vim
permalink : /wiki/arm_gdb_eclipse/

---
# reference
  * [https://wiki.eclipse.org/CDT/StandaloneDebugger](https://wiki.eclipse.org/CDT/StandaloneDebugger)
<br />
<br />

# Using elipse cdt(C/C++ development Tooling) as the front end of arm gdb
 gdb has a lot of features, but it is a command line interface, so it takes time to become proficient. Using TUI mode is a little more convenient, but it is still inconvenient than GUI interface. Here I will explain how to use eclipse cdt as the front end of arm gdb.
## Install eclipse cdt
  eclipse standalone debugger can be installed with a "Full eclipse" or "standalone", and you can choose either way.
* Install "Full eclipse"
  1. Downloads "eclipse C/C++ IDE" and decompress it.
    * [https://www.eclipse.org/downloads/](https://www.eclipse.org/downloads/)
  2. After decompression, move to the path below.
    ```bash
    $ cd eclipse/plugins/org.eclipse.cdt.debug.application_*/scripts
    ```
  3. The following command creates cdtdebug.sh in $HOME/cdtdebugger directory.
    ```bash
    $ /bin/sh .install.sh
    ```
  4. Run the command below.
    ```bash
    $ $HOME/cdtdebugger/cdtdebug.sh
    ```

* Install "standalone" 
  1. Download "standalone debugger" and decompress it.
    * [ https://eclipse.org/cdt/downloads.php](https://eclipse.org/cdt/downloads.php)
  2. After decompression, run the command below.
    ```bash
    $ ./cdtdebug
    ```

<br />
## Debugging helloworld with cdt
 After installing as above, run qemu and start debugging after setting eclipse debug configuration. Here, I will explain how to debug by running helloworld program with qemu and cdtdebug. Write helloworld.c file as below and compile it with gcc arm compiler.
* helloworld.c
```c
#include <stdio.h>
int main(void)
{
	printf("HelloWorld!\n");
	return 0;
}
```

* Compile with gcc arm toolchaing
```bash
$ arm-none-linux-gnueabihf-gcc -o helloworld helloworld.c -g -static
```

* Run qemu
```bash
$ qemu-arm -g 1234 helloworld
```

* eclipse debug configuration
  1. In eclipse menu, click **Run -> Debug Configurations**
  2. Choose **C/C++ Remote Application**, click the right mouse button, choose **New Configuration** menu
  ![title](/assets/images/cdt_new_configuration.png)
  3. Input name at **Name:** field 
  4. In **Project:** field, click **Browse...** button, and then choose Executables
  5. In **C/C++ Application:**, specify the elf file to use for debugging
  ![title](/assets/images/cdt_configuration_main.png)
  6. Choose **Debugger** tab
  7. Select the checkbox before **Stop on startup at:**, then input **main** or desired breakpoint in the field
  8. In **GDB debugger:**, Input the absolute path of arm-eabi-gdb
  ![title](/assets/images/cdt_configuration_debug.png)
  9. In **Debugger** tab, choose **Connection** tab
  10. Input **Type : TCP**, **Host name or IP address : localhost**, **Port number : 1234**
  ![title](/assets/images/cdt_configuration_debug_connection.png)
  11. Choose **Source** tab
  12. Click **Add...** button, choose **File System Directory**, set the source file path
  ![title](/assets/images/cdt_configuration_source.png)
  13. Click **Apply** button, click **Debug** button, then the screen which stopped at the breakpoint(ex.main) appears.
  14. In this state, debug by clicking "Step Into" and "Step Over" buttons.
  ![title](/assets/images/cdt_helloworld_debug.png)
  15. "HelloWorld!" is printed in terminal window
  ```bash
  $ qemu-arm -g 1234 helloworld
  HelloWorld!
  $
  ```

## Debugging uboot with cdt
```bash
$ qemu-system-arm --machine vexpress-a9 -m 1G -nographic -kernel u-boot -s -S
```

<br />
* [screenshot 1(Debug Configurations - Main)](/assets/images/debug_configurations_main.jpg)
* [screenshot 2(Debug Configurations - Debugger_Main)](/assets/images/debug_configurations_debugger_main.jpg)
* [screenshot 3(Debug Configurations - Debugger_Connection)](/assets/images/debug_configurations_debugger_connection.jpg)
* [screenshot 4(Debug Configurations - Source)](/assets/images/debug_configurations_source.jpg)
* [screenshot 5(Eclipse CDT Debugging)](/assets/images/eclipse_cdt_debugging.png)




