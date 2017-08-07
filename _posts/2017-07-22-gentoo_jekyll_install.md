---
layout: post
title: gentoo linux 에 Jekyll 설치 하기
category: web
tags: [web, jekyll]
comments: true
---

 gentoo linux에서 Jekyll을 설치하는 방법에 대하여 간단히 포스팅한다.
 Jekyll을 사용하기 위해서는 ruby, bundler, jekyll이 설치되어 있어야 한다.
 Jekyll은 simple, blog-aware, static site generator tool 로 ruby를 기반으로
작성되었고, bundler는 gems 와 version들 간의 의존성 관리를 하기 위해 필요한 도구이다,
 아래처럼 관련 package 를 설치한다.
```bash
$ sudo emerge --ask ruby 
```

  ruby를 설치할 경우, dev-rudy/bundler 와 dev-ruby/rubygems 도 함께 설치된다.
  만약 설치되지 않는 다면, 아래와 같이 추가로 package를 설치한다.
```bash
$ sudo emerge --ask dev-ruby/bundler dev-ruby/rubygems
 ```

  gem 명령으로 jekyll을 설치한다.
 ```bash
$ sudo gem install jekyll
```

아래 명령을 실행하면 local_directory에 기본 파일과 디렉토리를 생성한다.
```bash
$ jekyll new local_directory
```

 다음 명령으로 jekyll을  실행한 후에, web-browser에서 localhost:4000을 입력하면 local_directory 에 디폴트로 생성된 사이트를 볼 수 있다.
```bash
$ bundle exec jekyll serve
```
필요에 따라 수정 및 추가 작업을 한 후, github 에 push를 해준다.
 
 만약 "bundle exec jekyll serve"를 실행했을 때, 아래와 같은 에러가 발생한다면,
 Gemfile에 관련 버전명을 명시해 주어야 한다.
```bash 
$ bundle exec jekyll serve
bundler: failed to load command: jekyll (/usr/local/bin/jekyll)
LoadError: cannot load such file -- sass
  /usr/lib64/ruby/gems/2.2.0/gems/jekyll-sass-converter-1.5.0/lib/jekyll/converters/scss.rb:3:in `require'
  /usr/lib64/ruby/gems/2.2.0/gems/jekyll-sass-converter-1.5.0/lib/jekyll/converters/scss.rb:3:in `<top (required)>'
  /usr/lib64/ruby/gems/2.2.0/gems/jekyll-sass-converter-1.5.0/lib/jekyll-sass-converter.rb:2:in `require'
  /usr/lib64/ruby/gems/2.2.0/gems/jekyll-sass-converter-1.5.0/lib/jekyll-sass-converter.rb:2:in `<top (required)>'
  /usr/local/lib64/ruby/gems/2.2.0/gems/jekyll-3.5.1/lib/jekyll.rb:192:in `require'
  /usr/local/lib64/ruby/gems/2.2.0/gems/jekyll-3.5.1/lib/jekyll.rb:192:in `<top (required)>'
  /usr/local/lib64/ruby/gems/2.2.0/gems/jekyll-3.5.1/exe/jekyll:6:in `require'
  /usr/local/lib64/ruby/gems/2.2.0/gems/jekyll-3.5.1/exe/jekyll:6:in `<top (required)>'
  /usr/local/bin/jekyll:23:in `load'
  /usr/local/bin/jekyll:23:in `<top (required)>' 
$
```

  위 에러의 경우 sass 관련 에러가 발생한 것이다. 터미널에서 "sass --version" 명령으로 버전을 확인 한 후,
```bash
$ sass --version
 Sass 3.4.24 (Selective Steve) 
$
 ```

 Gemfile에  아래와 같이 추가한다.


 ```
gem "sass", "3.4.24"     # add this 
```

