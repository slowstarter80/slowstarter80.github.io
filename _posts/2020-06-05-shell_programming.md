---
layout: single
title: shell programming
date : 2020-06-05 01:23:45 +0900
last_modified_at: 2020-06-05 02:26:12 +0900
categories: [shell]
tags: [programming,shell]
comments: true
public : true
permalink : /wiki/bash_programming/
---

# while loop in shell file
## while_loop.sh
```bash
#!/bin/bash

num=0
while [ $num -le 5 ]
do
	echo "num : ${num}"
	((num++))
done
```

## output
```bash
$ ./while_loop.sh 
num : 0
num : 1
num : 2
num : 3
num : 4
num : 5
```
<br/>
# while loop in single-line
To do this, use the end-of-line delimiter(;). 
## example
```bash
$ num=0; while [ $num -le 5 ]; do echo "num : ${num}"; ((num++)); done
```

## output
```bash
$ num=0; while [ $num -le 5 ]; do echo "num : ${num}"; ((num++)); done
num : 0
num : 1
num : 2
num : 3
num : 4
num : 5
```
<br/>
# infinite while loop
## example
```bash
$ num=0; while ((1)); do echo "num : ${num}"; ((num++)); sleep 1; done
```

## output
```bash
$ num=0; while ((1)); do echo "num : ${num}"; ((num++)); sleep 1; done
num : 0
num : 1
num : 2
num : 3
num : 4
num : 5
...
...
```
