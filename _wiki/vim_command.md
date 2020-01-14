---
layout: wiki
title: vim command
date : 2020-01-15 01:33:04 +0900
updated : 2020-01-15 01:36:39 +0900
category: vim
tag: vim
comments: true
public : true
parent : vim
--- 
* TOC
{:toc} 


adb

# vim command
* vim command중에서 알아두면 유용하게 사용할 수 있는 command들에 대하여 정리하였다.


    | command | Description |
    | ------- | ----------- |
    | CTRL + o | move to cursor to previous location in history |
    | CTRL + I | move to cursor to next location in history |
    {:.mbtablestyle}

<br />
* system's clipboard 사용하기
  * \"* and "+ registers are for the system's clipboard
      * ex) "+yy, "+3yy, "+p, "*p
  * [http://vim.wikia.com/wiki/Copy,_cut_and_paste](http://vim.wikia.com/wiki/Copy,_cut_and_paste)

<br />
* vim registers 사용하기
  * ex) "ayy, "ap, :reg

<br />
* bookmark
  * in one file : m+[a~z]
  * move to bookmark : '  + [a~z]
  * in multiple files : m+[A~Z]
  * move to bookmark : '+[A~Z]
  *  [http://vim.wikia.com/wiki/Using_marks](http://vim.wikia.com/wiki/Using_marks)

<br />
* vim에서 a or b 검색하는 방법.
```
   :vimgrep /\ca\|b/ <CTRL-R><SHIFT-%>
```

<br />
* gvim에서 buffer를 tab으로 보는 방법
```
   :tab ball
```

<br />
* how to delete any trailing whitespace at the end of each line.
```
  :%s/\s\+$//g
```
  * reference
    * https://vim.fandom.com/wiki/Remove_unwanted_spaces

<br />
* how to delete ^M in the file
```
   :set ffs=unix
   :e!                   // reload
   :%s/^M//g             // ^M = ctrl + v + m
```

<br />
* how to compare 2 directories in vim
```
   :DirDiff folder_1 folder_2
```

<br />
* how to compare 2 directory lists with vimdiff
```
   $ vimdiff <(cd android-4.0.1_r1; find . | sort) <(cd android-4.0.2_r1; find . | sort)
```
