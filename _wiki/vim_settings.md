---
layout: single
title: Settings for analyzing code using gnu global in vim
category: vim
tag: [vim, gnu global]
comments: true
public : true
parent : vim
date : 2020-01-15 01:33:04 +0900
last_modified_at : 2020-03-11 03:01:44 +0900
permalink : /wiki/vim_settings/
---

# reference
  * [https://www.gnu.org/software/global](https://www.gnu.org/software/global)
<br />
<br />

# gnu global settings
 gnu global is a source code tagging system that provides quick code search.
 It can be used by entering commands in a shell or in editors such as vim or emacs.
 This section introduces how to use it with vim.

* Each linux distribution provides a package to install gnu global. However, to use the final version as earlier as possible, you need to download it directly from the gnu global home page.
 You can get it here.
  * [https://www.gnu.org/software/global/download.html](https://www.gnu.org/software/global/download.html)
* After extracting the downloaded file, build and install it as follows.
    ```bash
    $ sh reconf.sh
    $ ./configure --prefix=$HOME/bin
    $ make
    $ make install
    $ cp ~/bin/share/gtags/gtags.vim $HOME/.vim/plugin/
    $ cp ~/bin/share/gtags/gtags.conf $HOME/.globalrc
    $ vim $HOME/.globalrc
    ## If you want to exclude specific folders when creating tag files, specify those folders at "skip" varialbe. Or Just quit vim
    ```

* Run the "gtags" command in the root direcotry of the code, then it generates "GTAGS", "GRTAGS" and "GPAHT".
    ```bash
    $ gtags
    ```
* Using gnu global in vim(referred to gnu global web-site)
  * Run gnu global command in vim ex-mode as below. Setting up shortcuts in .vimrc is described later in this article.
    ```vim
    To go to main, you can say
        :Gtags main

    To go to the referenced point of func1, add the ‘-r’ option.
        :Gtags -r func1

    To locate symbols which are not defined in ‘GTAGS’, try this:
        :Gtags -s lbolt

    To locate strings, try this:
        :Gtags -g int argc
        :Gtags -g "root"
        :Gtags -ge -C               <- locate '-C'

    To get a list of tags in specified files, use the ‘-f’ command.
        :Gtags -f main.c            <- locate tags in main.c

    If you are editing ‘main.c’ itself, you can use ‘%’ instead.
        :Gtags -f %                 <- locate tags in main.c

    You can use POSIX regular expressions.
        :Gtags ^put_              <- locate tags starting with 'put_'
        :Gtags -g fseek(.*SEEK_SET) <- locate fseek() using SEEK_SET

    In the command line, press CTRL-D after some typing and Vim will show a list of tag names that start with the string. Press <TAB> and Vim will complete the tag name.
        :Gtags fu<TAB>
        :Gtags func1                <- 'nc1' is appended by vim

    You can browse files whose path includes specified pattern.
        :Gtags -P /vm/              <- under vm/ directory
        :Gtags -P \.h$              <- all include files
        :Gtags -P init              <- path including 'init'

    You can use all options of global(1) except for ‘-c -n -p -q -u -v’ and all long name options. They are sent to global(1) as is. For example:
        :Gtags -gi paTtern        <- matches both 'PATTERN' and 'pattern'
        :Gtags -POi make          <- matches Makefile but not makeit.c
    ```

<!--
* [vim plugins]( /assets/files/vim_plugin.tar.gz "vim plugin files")
  * 첨부 파일에 syntax 및 color 관련 plugin, 기타 개인적으로 사용하는
  plugin(Taglist, NERDTree) 등이 포함되어 있다. 필요한 경우, 첨부 파일을
  다운받아 개인 계정의 home directory에 압축을 풀면 된다.
    ex) 수정 사항 in c.vim.
    ```vim
    " Highlight Class and Function names
    syn match    cCustomParen    "(" contains=cParen contains=cCppParen
    syn match    cCustomFunc     "\w\+\s*(\@=" contains=cCustomParen
    syn match    cCustomScope    "::"
    syn match    cCustomClass    "\w\+\s*::" contains=cCustomScope

    hi def link cCustomFunc  Function
    hi def link cCustomClass Function
    ```
-->

* [vim setting file(.vimrc)](/assets/files/vimrc.tar.gz ".vimrc file")
  * This file contains settings that are set when vim starts.
  * put ".vimrc" file to your home directory, then vim read this file when it starts.
    ```vim
    "c language syntax color settings
    hi Identifier cterm=underline ctermfg=146
    hi Comment cterm=none ctermfg=247
    hi CursorLine cterm=none ctermbg=236
    hi cCustomFunc cterm=bold ctermfg=111
    hi cCustomClass cterm=bold ctermfg=183
    ...
    "mapleader setting. This is the key corresponding to the <Leader>, here I set it to ",".
    let mapleader=","
    ...
    ":TlistToggle<CR> is run if you press <F2> key.
    map <F2> :TlistToggle<CR>
    "quickfix의 next item
    map <F6> :cn<CR>
    map <F5> :cp<CR>
    map <F8> :cnewer<CR>
    map <F7> :colder<CR>
    map <Leader><F7> :cope<CR>
    map <Leader><F8> :ccl<CR>
    map <F9> :bnext<CR>
    map <F10> :bprevious<CR>

    "=============gnu global keymap=============

    "Input ",gd". It searches the string at the current cursor position from tag files.(it's like searching definition)
    nmap <Leader>gd :Gtags <C-R>=expand("<cword>")<CR><CR>
    "Input ",gr". It searches the referenced places of the string where the cursor is located.
    nmap <Leader>gr :Gtags -r <C-R>=expand("<cword>")<CR><CR>
    "Input ",gs". It searches the symbols which are not defined in GTAGS.
    nmap <Leader>gs :Gtags -s <C-R>=expand("<cword>")<CR><CR>
    "Input ",gg". It searches "pattern" from all files.(*.h, *.c, *.txt and etc)
    nmap <Leader>gg :Gtags -go <C-R>=expand("<cword>")<CR><CR>
    "Input ",gp". It searches files.
    nmap <Leader>gp :Gtags -Po <C-R>=expand("<cword>")<CR><CR>
    "Input ",ge". It searches "--regexp" pattern.
    nmap <Leader>ge :Gtags -ge <C-R>=expand("<cword>")<CR><CR>

    "These keymaps are same with above, except "ignore case sensitivity".
    nmap <Leader>igd :Gtags -i <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>igr :Gtags -ir <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>igs :Gtags -is <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>igg :Gtags -igo <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>igp :Gtags -iPo <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>ige :Gtags -ige <C-R>=expand("<cword>")<CR><CR>

    "These keymaps are same with above, except that the above command searches the string at the current cursor position. Meanwhile, the commands below need to enters the string to search for
    nmap <Leader>ld :Gtags
    nmap <Leader>lr :Gtags -r
    nmap <Leader>ls :Gtags -s
    nmap <Leader>lg :Gtags -go
    nmap <Leader>lp :Gtags -Po
    nmap <Leader>le :Gtags -ge

    nmap <Leader>ild :Gtags -i
    nmap <Leader>ilr :Gtags -ir
    nmap <Leader>ils :Gtags -is
    nmap <Leader>ilg :Gtags -igo
    nmap <Leader>ilp :Gtags -iPo
    nmap <Leader>ile :Gtags -ige

    "Input ",nt". NERDTreeToggle<CR>
    map <Leader>nt :NERDTreeToggle<CR>

    " vim window navigation key
    nmap <C-H> <C-W>h
    nmap <C-J> <C-W>j
    nmap <C-K> <C-W>k
    nmap <C-L> <C-W>l
    ```
  * How to disable auto jump function after searching string with gtags in vim.
    * Add the following code to .vimrc file.
        ```vim
        let g:Gtags_No_Auto_Jump=1
	```
