---
layout: single
title: qemu 사용시, eclipse cdt를 arm gdb의 front end로 사용하는 방법
date : 2020-01-15 01:33:04 +0900
last_modified_at: 2020-02-22 02:44:08 +0900
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

# elipse cdt(C/C++ development Tooling)를 arm gdb의 fronti end로 사용하기 
 gdb는 아주 많은 기능을 가지고 있지만 CLI 방식이어서 어느정도 능숙해지기까지는 시간이 필요하다. TUI 모드를 사용하면 조금 더 편리하지만 여전히 GUI 방식보다는 불편한 점이 있다. 여기에서는 eclipse cdt를 arm gdb의 front end로 사용하는 방법에 대해서 소개하겠다. 
## eclipse cdt 설치
  eclipse standalone debugger는 Full eclipse를 설치하거나 standalone으로 설치할 수 있으며 어느 방법으로 해도 무방하다.
* Full eclipse 설치
  1. eclipse C/C++ IDE를 아래 링크에서 다운로드 하여 압축해제 한다.
    * [https://www.eclipse.org/downloads/](https://www.eclipse.org/downloads/)
  2. 압축 해제후 아래 경로로 이동한다.
    ```bash
    $ cd eclipse/plugins/org.eclipse.cdt.debug.application_*/scripts
    ```
  3. 아래 명령을 실행하면 $HOME/cdtdebugger 디렉토리에 cdtdebug.sh 파일이 생성된다. 
    ```bash
    $ /bin/sh .install.sh
    ```
  4. 아래 명령으로 실행한다.
    ```bash
    $ $HOME/cdtdebugger/cdtdebug.sh
    ``` 

* standalone 설치
  1. standalone debugger를 아래 링크에서 다운로드 하여 압축해제 한다.
    * [ https://eclipse.org/cdt/downloads.php](https://eclipse.org/cdt/downloads.php)
  2. 아래 명령으로 실행단다.
    ```bash
    $ ./cdtdebug 
    ```

<br />
## Debugging helloworld with cdt
 위와 같이 설치 한 후, 터미널에서 아래 명령으로 qemu를 실행하고, eclipse debug configration 설정 후 디버깅을 시작하면 된다. 여기에서는 qemu로 helloworld를 실행한 후 cdtdebug를 실행하여 디버깅 하는 방법을 설명할 것이다.
* qemu 실행
```bash
$ qemu-arm -g 1234 helloworld
```

* eclipse debug configuration 설정
  1. eclipse menu 에서 **Run -> Debug Configurations** 실행
  2. **C/C++ Remote Application** 선택 후, 마우스 오른쪽 버튼 누르고 **New Configuration** menu 선택  
  ![title](/assets/images/cdt_new_configuration.png)  
  3. **Name:** 란에 적당한 이름 입력
  4. **Project:** 란에는 **Browse...** button을 누르고, Executables 선택  
  5. **C/C++ Application:**란에는 디버깅에 사용할 elf 파일 지정
  ![title](/assets/images/cdt_configuration_main.png)  
  6. **Debugger** tab 선택
  7. **Stop on startup at:** 앞에 체크 박스 선택 후, 입력란에 **main** 또는 원하는 breakpoint 입력
  8. **GDB debugger:**란에 arm-eabi-gdb의 절대 경로 입력
  ![title](/assets/images/cdt_configuration_debug.png)  
  9. **Debugger** tab내에 있는 **Connection** tab 선택
  10. **Type : TCP**, **Host name or IP address : localhost**, **Port number : 1234** 입력  
  ![title](/assets/images/cdt_configuration_debug_connection.png)  
  11. **Source** tab 선택
  12. **Add...** button을 누른 후, **File System Directory**를 선택 하고, source file의 경로 지정  
  ![title](/assets/images/cdt_configuration_source.png)  
  13. **Apply** button을 누르고, **Debug** button을 누르면, main함수에서 break된 상태가 화면에 나타난다.
  14. 이 상태에서 "Step Into", "Step Over"등의 버튼으로 진행하면서 디버깅을 한다.
  ![title](/assets/images/cdt_helloworld_debug.png)  


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




