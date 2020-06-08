---
layout: single
title: Debugging with gdb tui mode
date : 2020-01-15 01:33:04 +0900
last_modified_at: 2020-06-08 18:06:43 +0900
category: gdb
tag: [gdb]
comments: true
public : true
parent : vim
---

# reference
  * [https://sourceware.org/gdb/onlinedocs/gdb/TUI.html](https://sourceware.org/gdb/onlinedocs/gdb/TUI.html)
<br />
<br />

# TUI
 Text User Interface(TUI) mode of GDB a terminal interface showing source code/assembly/register information/gdb commands in adevidec text window.
 It provides more convenient debugging  environment to users.
 TUI mode can be used in the following ways.

 ```bash
 $ gdb -tui
 ```
 Or after running GDB, execute the tui command.
 The following are main tui commands.

* tui enable
  * Activates TUI mode.
* tui disable
  * Disables TUI mode.
* info win
  * Shows the currently displayed window and its size..
* layout \<name\>
  * Shows the window corresponding to \<name\>.(ex. layout src,  layout next)
    * next
      * Shows next layout.
    * prev
      * Shows previous layout.
    * src
      * Shows source code window and command window.
    * asm
      * Shows assembly code window and command window.
    * split
      * Shows source code window, assembly code window and command window.
    * regs
      * Shows register window.
* focus \<name\>
  * Sets the window corresponding to \<name\> have focus.(ex. focus regs,  layout regs)
    * next
    * prev
    * src
    * asm
    * regs
    * cmd
* refresh
  * Refreshes current screen. Same with \<Ctrl + L\> .
* tui reg group
  * Shows by register group.
    * next
      * Shows next register group.
    * prev
      * Shows previous register group.
    * general
      * Shows general register groups.
    * float
      * Shows floating point register group.
    * system
      * Shows system register group.
    * vector
      * Shows vector register groupt.
    * all
      * Shows all registers.

* update
  * Updates source code window and current execution point.
* winheight \<name\> +count
  * Increases the window's height corresponding to \<name\>
* winheight \<name\> -count
  * Decrease the window's height corresponding to \<name\>

* tabset nchars
  * set the width of tab stops

<br />
* [screenshot 1(source & assembly)](/assets/images/gdb_tui_1.jpg)
* [screenshot 2(registers & sources)](/assets/images/gdb_tui_2.jpg)
