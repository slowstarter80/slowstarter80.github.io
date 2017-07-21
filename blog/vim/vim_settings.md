---
laybout: page
title: vim settings
---

# vim settings

* vim 
[vim plugins]( https://github.com/slowstarter80/my_wiki/raw/master/vim_settings/vim_plugin.tar.gz "vim plugin files")
  * contains some plugins for syntax and colors.
  * extract this file to your home directory.  
    The changed code is below in c.vim.
    ```vim
    " Highlight Class and Function names 
    syn match    cCustomParen    "(" contains=cParen contains=cCppParen 
    syn match    cCustomFunc     "\w\+\s*(\@=" contains=cCustomParen 
    syn match    cCustomScope    "::" 
    syn match    cCustomClass    "\w\+\s*::" contains=cCustomScope 
 
    hi def link cCustomFunc  Function 
    hi def link cCustomClass Function 
    ```

* vimrc [vim setting file(.vimrc)](https://github.com/slowstarter80/my_wiki/raw/master/vim_settings/vimrc.tar.gz)
  * contains optional runtime configuration settings to initialize vim when it starts.
  * extract this file to your home directory.
  * below are major settings.
  * Below are major settings
    ```vim
    hi Identifier cterm=underline ctermfg=146
    hi Comment cterm=none ctermfg=247
    hi CursorLine cterm=none ctermbg=236
    hi cCustomFunc cterm=bold ctermfg=111
    hi cCustomClass cterm=bold ctermfg=183
    ...
    let mapleader=","
    ...
    map <F2> :TlistToggle<CR>
    map <F6> :cn<CR>
    map <F5> :cp<CR>
    map <F8> :cnewer<CR>
    map <F7> :colder<CR>
    map <Leader><F7> :cope<CR>
    map <Leader><F8> :ccl<CR>
    map <F9> :bnext<CR>
    map <F10> :bprevious<CR>
    nmap <Leader><F12> :TrinityToggleSourceExplorer<CR>
    nmap <C-c> :!mkcscope.sh<CR>:cs kill -l<CR>:cs add $PWD/cscope.out<CR>
     
    "=============gnu global keymap=============
     
    nmap <Leader>gd :Gtags <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>gr :Gtags -r <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>gs :Gtags -s <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>gg :Gtags -go <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>gp :Gtags -Po <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>ge :Gtags -ge <C-R>=expand("<cword>")<CR><CR>
     
    nmap <Leader>igd :Gtags -i <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>igr :Gtags -ir <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>igs :Gtags -is <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>igg :Gtags -igo <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>igp :Gtags -iPo <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>ige :Gtags -ige <C-R>=expand("<cword>")<CR><CR>
     
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
    ```


# Use GNU Global in vim

* GNU Global package in ubuntu repository is a little old. So it'd better get source code form web-site and install with source code.
* Get latest source code from below site.
  * https://www.gnu.org/software/global/download.html
* Build and install GNU global like below
    ```bash
    $ sh reconf.sh
    $ ./configure --prefix=$HOME/bin
    $ make
    $ make install
    $ cp ~/bin/share/gtags/gtags.vim $HOME/.vim/plugin/
    $ cp ~/bin/share/gtags/gtags.conf $HOME/.globalrc
    $ vim $/HOME/.globalrc
    and add ",/out/" at the end of "skip" configuration varible.
    ```

* mkglobal_xxxxxxxx.sh [mkglobal_xxxxxxxx.sh]( https://github.com/slowstarter80/my_wiki/raw/master/vim_settings/mkglobal.sh.tar.gz "mkglobal.tar.gz")
  * makes a GNU Global DB file
  * run this script at your source root directory. Then, “GTAGS”, “GRTAGS” and “GPATH” will be generated.
* usage in vim
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

# Other Useful vim command
* CTRL + o : move to cursor to previous location in history
* CTRL + I : move to cursor to next location in history
* mark
  * http://vim.wikia.com/wiki/Using_marks
* copy,cut and paste
  * http://vim.wikia.com/wiki/Copy,_cut_and_paste
* how to view man page in vim
  * http://daeny2.tistory.com/entry/vim-%ED%8E%B8%EC%A7%91%EA%B8%B0%EC%97%90%EC%84%9C-man-page-%EB%B3%B4%EA%B8%B0

