---
layout: single
title: vim command
date : 2020-01-15 01:33:04 +0900
last_modified_at: 2020-06-08 18:06:52 +0900
category: vim
tag: vim
comments: true
public : true
parent : vim
---

Here I summarized vim commands that are used frequently for development.
* How to move cursor to the location in history

    | command | Description |
    | ------- | ----------- |
    | CTRL + o | move to cursor to previous location in history |
    | CTRL + I | move to cursor to next location in history |
    {:.mbtablestyle}

<br />
* How to use system's clipboard
  * \"* and "+ registers are for the system's clipboard
      * ex) "+yy, "+3yy, "+p, "*p
  * [http://vim.wikia.com/wiki/Copy,_cut_and_paste](http://vim.wikia.com/wiki/Copy,_cut_and_paste)

<br />
* How to use vim registers
  * ex) "ayy, "ap, :reg

<br />
* bookmark
  * in one file : m+[a~z]
  * move to bookmark : '  + [a~z]
  * in multiple files : m+[A~Z]
  * move to bookmark : '+[A~Z]
  *  [http://vim.wikia.com/wiki/Using_marks](http://vim.wikia.com/wiki/Using_marks)

<br />
* How to search for "a or b" in the current file. '\c' means ignore case.
```
   :vimgrep /\ca\|b/ <CTRL-R><SHIFT-%>
```

<br />
* How to show each buffer in a tab on gvim.
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
* how to delete ^M in a file(^M is Ctrl + v + m)
```
   :set ffs=unix
   :e!                   // reload
   :%s/^M//g             // ^M = ctrl + v + m
```

<br />
* how to delete ^M for multiple files(^M is Ctrl + v + m)
 ```bash
    $ find ./ -iname * -exec dos2unix {} \;
 ```

<br />
* how to delete trailing whitespaces for multiple files
 ```bash
    $ find . -type f -name '*.txt' -exec sed --in-place 's/[[:space:]]\+$//' {} \;
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
