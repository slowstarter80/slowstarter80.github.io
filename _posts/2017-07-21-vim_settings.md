---
layout: post
title: 코드 분석을 위한 vim 설정하기(gnu global,  vim plugin)
category: vim
tag: [vim, gnu global]
comments: true
---
# reference
  * [https://www.gnu.org/software/global](https://www.gnu.org/software/global)
<br />
<br />
  
# gnu global 설정하기
 gnu global 은 source code tagging system으로 코드 검색을 빠르게 할 수 있는
 기능을 제공하는 도구이다. bash terminal등에서 커맨드를 입력하여 사용하거나 또는 
 vim, emacs등의 editor와 연동하여 사용 할 수도 있다. 여기에서는 vim과
 연동하여 사용하는 방법을 소개한다.

* 리눅스 각 배포판에서도 GNU Global 을 설치 할 수 있도록 package를 제공하지만 약간 버전 업데이트가 느린 편이다. 최종 버전을 사용하기 위해서는 gnu global home page에서 직접 다운로드 받아야 한다.아래 링크에서 최종 버전을 다운로드 한다. 
  * [https://www.gnu.org/software/global/download.html](https://www.gnu.org/software/global/download.html)
* 다운로드 한 파일을 압축해제 한 후, 아래와 같이 빌드 및 설치를 한다. 
    ```bash
    $ sh reconf.sh
    $ ./configure --prefix=$HOME/bin
    $ make
    $ make install
    $ cp ~/bin/share/gtags/gtags.vim $HOME/.vim/plugin/
    $ cp ~/bin/share/gtags/gtags.conf $HOME/.globalrc
    $ vim $/HOME/.globalrc
    ## 여기에서 tag 생성시 제외할  폴더를 "skip" 설정 변수에 지정한다. 
    ```

* 코드의 root directory에서 아래 명령을 실행하면 "GTAGS", "GRTAGS" 그리고
"GPATH" 파일이 생성된다. 
    ```bash
    $ gtags
    ```
* vim에서 gnu global 사용하기(referred from gnu global web-site)
  * 아래처럼 vim의 ex mode에서 command 입력으로 사용할 수 있다.  .vimrc 에서
  단축키를 설정하는 방법은 아래에서 추가로 설명한다. 
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

* [vim setting file(.vimrc)](/assets/files/vimrc.tar.gz ".vimrc file")
  * vim 시작시 설정되는 사항들을 포함하는 파일이다.
  * 개인 계정의 home directory 에 압축을 풀고 사용하면 되며, 주요 설정 사항은
  다음과 같다.
    ```vim
    "c language syntax color 관련 설정
    hi Identifier cterm=underline ctermfg=146
    hi Comment cterm=none ctermfg=247
    hi CursorLine cterm=none ctermbg=236
    hi cCustomFunc cterm=bold ctermfg=111
    hi cCustomClass cterm=bold ctermfg=183
    ...
    "mapleader 설정. 이 항목의 아래의 <Leader> 에 해당하는 key이며 여기서는 ","로 설정하였다.
    let mapleader=","
    ...
    "<F2> key를 누르면, :TlistToggle<CR> 이 입력됨.
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
     
    ",gd 입력. 현재 cursor가 위치한 string을 tag에서 검색(definition등)
    nmap <Leader>gd :Gtags <C-R>=expand("<cword>")<CR><CR> 
    ",gr 입력. 현재 cursor가 위치한 string으로 reference검색.사용하는 곳의 위치를 보여줌.
    nmap <Leader>gr :Gtags -r <C-R>=expand("<cword>")<CR><CR>
    ",gs 입력. 현재 cursor가 위치한 string으로 symbol 검색.(variable등)
    nmap <Leader>gs :Gtags -s <C-R>=expand("<cword>")<CR><CR>
    ",gg 입력, --grep pattern 검색, 모든 파일에서 검색, (h, c, txt 등)
    nmap <Leader>gg :Gtags -go <C-R>=expand("<cword>")<CR><CR>
    ",gp 입력, 파일명 검색 
    nmap <Leader>gp :Gtags -Po <C-R>=expand("<cword>")<CR><CR>
    ",ge 입력, --regexp 검색. 
    nmap <Leader>ge :Gtags -ge <C-R>=expand("<cword>")<CR><CR>
     
    " 위의 사용법과 동일하며, case sensitivity를 ignore
    nmap <Leader>igd :Gtags -i <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>igr :Gtags -ir <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>igs :Gtags -is <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>igg :Gtags -igo <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>igp :Gtags -iPo <C-R>=expand("<cword>")<CR><CR>
    nmap <Leader>ige :Gtags -ige <C-R>=expand("<cword>")<CR><CR>
     
    "위의 사용법과 동일하며, 한가지 차이점은 위의 명령은 현재 커서 위치의 string으로 검색
    "아래 명령은 검색하려는 string을 직접 입력함
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

    ",nt 입력. NERDTreeToggle<CR>
    map <Leader>nt :NERDTreeToggle<CR>

    " vim window 이동 키
    nmap <C-H> <C-W>h
    nmap <C-J> <C-W>j
    nmap <C-K> <C-W>k
    nmap <C-L> <C-W>l
    ```
  * vim 에서 gtags를 이용하여 검색 한 후에 auto jump 하는 기능 disable 하기
    * .vimrc 파일에 아래 코드 추가
        ```vim
        let g:Gtags_No_Auto_Jump=1
	```
