---
layout: single
title: How to create files with random data
date : 2021-03-01 01:23:45 +0900
last_modified_at: 2021-03-01 19:29:13 +0900
categories: [linux]
tags: [linux]
comments: true
public : true
use_math : true
---

# Using "head" command to generate files
## create a 100M file filled with all 0's.
```bash
$ head -c 100M /dev/zero > 100M_filled_with_zeros
```
## create a 100M file filled with random data.
```bash
$ head -c 100M /dev/urandom > 100M_filled_with_random_data 
```

<br/>

# Using "dd" command to generate files
## create a 100M file filled with all 0's.
```bash
$ dd if=/dev/zero of=100M_filled_with_zeros bs=100M count=1
```
## create a 100M file filled with random data.
```bash
$ dd if=/dev/urandom of=100M_filled_with_random_data bs=1M count=100
```

## Caution : When using the "dd" command, if the size of "bs" is larger than 32MB, a 33554431(32MB-1)bytes file is created.
```bash
$ dd if=/dev/urandom of=100M_filled_with_random_data bs=100M count=1
0+1 records in
0+1 records out
33554431 bytes (34 MB, 32 MiB) copied, 0.553194 s, 60.7 MB/s

$ ls -alh
total 33M
drwxr-xr-x  2 chuljeon39a chuljeon39a 4.0K Mar  1 18:53 .
drwxr-xr-x 30 chuljeon39a chuljeon39a 4.0K Mar  1 14:52 ..
-rw-r--r--  1 chuljeon39a chuljeon39a  32M Mar  1 18:53 100M_filled_with_random_data
$ 
```
It was expected a 100MB file to be created, but a 32MB file was actually created.
That's because it reads only 33554431 bytes from "/dev/urandom" at a time.
```c
...
#define ENTROPY_SHIFT 3
...
urandom_read(struct file *file, char __user *buf, size_t nbytes, loff_t *ppos)
{
    ...
	nbytes = min_t(size_t, nbytes, INT_MAX >> (ENTROPY_SHIFT + 3));
	...
}
```
So, the maximum bytes read from /dev/urandom at a time is (INT_MAX >> 6) in this example.
