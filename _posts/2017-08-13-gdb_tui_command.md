---
layout: post
title: GDB debugging시 TUI mode 사용 방법
category: gdb
tag: [gdb]
comments: true
---
# reference
  * [https://sourceware.org/gdb/onlinedocs/gdb/TUI.html](https://sourceware.org/gdb/onlinedocs/gdb/TUI.html)
<br />
<br />

# TUI 
 GDB의 TUI(Text user Interface)는  curses library를 사용하여 source file,
 assembly, register info, gdb command등을 분할된 text window에 보여주는 terminal iterface 이다. TUI mode를 사용하면, 
 GDB를 조금 더 편리하게 사용할 수 있다. TUI는 아래와 같은 방법으로 사용 할 수 있다. 
 ```bash
 $ gdb -tui
 ```
 또는, gdb를 실행 한 후에 tui command를 실행한다.  
 아래는 주요 tui command 리스트이다. 

* tui enable
  * Activate TUI mode. 
* tui disable
  * Disable TUI mode.
* info win 
  * 현재 디스플레이 된 윈도우와 그 윈도우의 사이즈를 보여준다.
* layout name
  * name에 보기를 원하는 윈도우명을 지정한다.(ex. layout src,  layout next) 
    * next
      * 다음 레이아웃을 보여준다.
    * prev 
      * 이전 레이아웃을 보여준다.
    * src 
      * 소스 윈도우와 커맨드 윈도우를 보여준다.
    * asm 
      * 어셈블리 윈도우와 커맨드 윈도우를 보여준다.
    * split 
      * 소스 윈도우, 어셈블리 윈도우, 커맨드 윈도우를 보여준다.
    * regs
      * 레지스터 윈도우를 보여준다.
* focus name
  * 포커스를 가지는 윈도우를 지정한다.(ex. focus regs,  layout regs)  
    name에는 아래와 같은 윈도우 명을 사용할 수 있다.
    * next
    * prev
    * src
    * asm
    * regs
    * cmd
* refresh
  * 현재 screen을 refresh 한다. Ctrl + L 과 동일한 기능을 한다. 
* tui reg group
  * register group별로 디스플레이 한다. 
    * next
      * 반복적으로 next register group을 보여준다. 
    * prev
      * 반복적으로 prev register group을 보여준다.
    * general 
      * general register groups을 보여준다. 
    * float 
      * floating point register group을보여준다.
    * system
      * system register group을 보여준다. 
    * vector
      * vector register groupt을 보여준다. Display the vector registers. 
    * all
      * 모든 register 들을 보여준다. 

* update 
  * 소스 윈도우와 현재 실행위치를 업데이트 한다.
* winheight name +count
  name 윈도우의 height를 count 만큼 증가한다.
* winheight name -count
  name 윈도우의 height를 count 만큼 감소한다.

* tabset nchars 
  * tab stops의 넓이를 지정한다. 

<br />
* [screenshot 1(source & assembly)](/assets/images/gdb_tui_1.jpg)  
* [screenshot 2(registers & sources)](/assets/images/gdb_tui_2.jpg)
