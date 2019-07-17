---
layout: post
title: vim command
category: vim
tag: vim
comments: true
---

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
* how to view man page in vim 
  * [view man page in vim](http://daeny2.tistory.com/entry/vim-%ED%8E%B8%EC%A7%91%EA%B8%B0%EC%97%90%EC%84%9C-man-page-%EB%B3%B4%EA%B8%B0) 
  
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

