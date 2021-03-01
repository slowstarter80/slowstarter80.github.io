---
layout: single
title: Split compression / decompression
date : 2021-02-28 01:23:45 +0900
last_modified_at: 2021-03-02 00:19:08 +0900
categories: [linux]
tags: [linux]
comments: true
public : true
use_math : true
---

 There are several ways to do split compression/decompression. Here I will introduce some methods.\
 In this example, a 100MB file is divided and compressed into a 20MB file size
# Using "tar", "split" and "cat" command
## Compression
1. Files to compress
```bash
$ ls -alh
total 101M
drwxr-xr-x  2 chuljeon39a chuljeon39a 4.0K Mar  1 22:25 .
drwxr-xr-x 30 chuljeon39a chuljeon39a 4.0K Mar  1 14:52 ..
-rw-r--r--  1 chuljeon39a chuljeon39a 100M Mar  1 22:19 100M_filled_with_random_data
```
2. Compression
 In this command, we don't need to specify archive name. Instead, we use "-" sign.
```bash
$ tar zcvf - 100M_filled_with_random_data | split -b 20M - compressed.tar.gz
100M_filled_with_random_data
```
3. Result
```bash
$ ls -alh
total 201M
drwxr-xr-x  2 chuljeon39a chuljeon39a 4.0K Mar  1 22:27 .
drwxr-xr-x 30 chuljeon39a chuljeon39a 4.0K Mar  1 14:52 ..
-rw-r--r--  1 chuljeon39a chuljeon39a 100M Mar  1 22:19 100M_filled_with_random_data
-rw-r--r--  1 chuljeon39a chuljeon39a  20M Mar  1 22:27 compressed.tar.gzaa
-rw-r--r--  1 chuljeon39a chuljeon39a  20M Mar  1 22:27 compressed.tar.gzab
-rw-r--r--  1 chuljeon39a chuljeon39a  20M Mar  1 22:27 compressed.tar.gzac
-rw-r--r--  1 chuljeon39a chuljeon39a  20M Mar  1 22:27 compressed.tar.gzad
-rw-r--r--  1 chuljeon39a chuljeon39a  20M Mar  1 22:27 compressed.tar.gzae
-rw-r--r--  1 chuljeon39a chuljeon39a  17K Mar  1 22:27 compressed.tar.gzaf
```

## Decompression 
1. Files to decompress
```bash
$ ls -alh
total 101M
drwxr-xr-x 2 chuljeon39a chuljeon39a 4.0K Mar  1 22:43 .
drwxr-xr-x 3 chuljeon39a chuljeon39a 4.0K Mar  1 22:43 ..
-rw-r--r-- 1 chuljeon39a chuljeon39a  20M Mar  1 22:43 compressed.tar.gzaa
-rw-r--r-- 1 chuljeon39a chuljeon39a  20M Mar  1 22:43 compressed.tar.gzab
-rw-r--r-- 1 chuljeon39a chuljeon39a  20M Mar  1 22:43 compressed.tar.gzac
-rw-r--r-- 1 chuljeon39a chuljeon39a  20M Mar  1 22:43 compressed.tar.gzad
-rw-r--r-- 1 chuljeon39a chuljeon39a  20M Mar  1 22:43 compressed.tar.gzae
-rw-r--r-- 1 chuljeon39a chuljeon39a  17K Mar  1 22:43 compressed.tar.gzaf
```
2. Decompression
```bash
$ cat compressed.tar.gza* | tar zxvf -
100M_filled_with_random_data
```
3. Result
```bash
$ ls -alh
total 201M
drwxr-xr-x 2 chuljeon39a chuljeon39a 4.0K Mar  1 22:46 .
drwxr-xr-x 3 chuljeon39a chuljeon39a 4.0K Mar  1 22:43 ..
-rw-r--r-- 1 chuljeon39a chuljeon39a 100M Mar  1 22:19 100M_filled_with_random_data
-rw-r--r-- 1 chuljeon39a chuljeon39a  20M Mar  1 22:43 compressed.tar.gzaa
-rw-r--r-- 1 chuljeon39a chuljeon39a  20M Mar  1 22:43 compressed.tar.gzab
-rw-r--r-- 1 chuljeon39a chuljeon39a  20M Mar  1 22:43 compressed.tar.gzac
-rw-r--r-- 1 chuljeon39a chuljeon39a  20M Mar  1 22:43 compressed.tar.gzad
-rw-r--r-- 1 chuljeon39a chuljeon39a  20M Mar  1 22:43 compressed.tar.gzae
-rw-r--r-- 1 chuljeon39a chuljeon39a  17K Mar  1 22:43 compressed.tar.gzaf
```
<br/>

# Using "7z"
## Compression
1. Files to compress
```bash
$ ls -alh
total 101M
drwxr-xr-x  2 chuljeon39a chuljeon39a 4.0K Mar  1 23:36 .
drwxr-xr-x 30 chuljeon39a chuljeon39a 4.0K Mar  1 14:52 ..
-rw-r--r--  1 chuljeon39a chuljeon39a 100M Mar  1 22:19 100M_filled_with_random_data
```
2. Compression
```bash
$ 7z a compressed.7z 100M_filled_with_random_data -v20m
```
3. Result
```bash
$ ls -alh
total 201M
drwxr-xr-x  2 chuljeon39a chuljeon39a 4.0K Mar  1 23:37 .
drwxr-xr-x 30 chuljeon39a chuljeon39a 4.0K Mar  1 14:52 ..
-rw-r--r--  1 chuljeon39a chuljeon39a 100M Mar  1 22:19 100M_filled_with_random_data
-rw-r--r--  1 chuljeon39a chuljeon39a  20M Mar  1 23:37 compressed.7z.001
-rw-r--r--  1 chuljeon39a chuljeon39a  20M Mar  1 23:37 compressed.7z.002
-rw-r--r--  1 chuljeon39a chuljeon39a  20M Mar  1 23:37 compressed.7z.003
-rw-r--r--  1 chuljeon39a chuljeon39a  20M Mar  1 23:37 compressed.7z.004
-rw-r--r--  1 chuljeon39a chuljeon39a  20M Mar  1 23:37 compressed.7z.005
-rw-r--r--  1 chuljeon39a chuljeon39a 5.6K Mar  1 23:37 compressed.7z.006
```

## Decompression
1. Files to decompress
```bash
$ ls -alh
total 101M
drwxr-xr-x 2 chuljeon39a chuljeon39a 4.0K Mar  2 00:11 .
drwxr-xr-x 3 chuljeon39a chuljeon39a 4.0K Mar  2 00:11 ..
-rw-r--r-- 1 chuljeon39a chuljeon39a  20M Mar  1 23:47 compressed.7z.001
-rw-r--r-- 1 chuljeon39a chuljeon39a  20M Mar  1 23:47 compressed.7z.002
-rw-r--r-- 1 chuljeon39a chuljeon39a  20M Mar  1 23:47 compressed.7z.003
-rw-r--r-- 1 chuljeon39a chuljeon39a  20M Mar  1 23:47 compressed.7z.004
-rw-r--r-- 1 chuljeon39a chuljeon39a  20M Mar  1 23:47 compressed.7z.005
-rw-r--r-- 1 chuljeon39a chuljeon39a 5.6K Mar  1 23:47 compressed.7z.006
$ 
```
2. Decompression
 "-aoa" means to overwrite all existing files without prompt. Run the "7z --help" command to get more information.
```bash
$ 7z x compressed.7z.001 -aoa
```
3. Result
```bash
$ ls -alh
total 201M
drwxr-xr-x 2 chuljeon39a chuljeon39a 4.0K Mar  2 00:12 .
drwxr-xr-x 3 chuljeon39a chuljeon39a 4.0K Mar  2 00:11 ..
-rw-r--r-- 1 chuljeon39a chuljeon39a 100M Mar  1 22:19 100M_filled_with_random_data
-rw-r--r-- 1 chuljeon39a chuljeon39a  20M Mar  1 23:47 compressed.7z.001
-rw-r--r-- 1 chuljeon39a chuljeon39a  20M Mar  1 23:47 compressed.7z.002
-rw-r--r-- 1 chuljeon39a chuljeon39a  20M Mar  1 23:47 compressed.7z.003
-rw-r--r-- 1 chuljeon39a chuljeon39a  20M Mar  1 23:47 compressed.7z.004
-rw-r--r-- 1 chuljeon39a chuljeon39a  20M Mar  1 23:47 compressed.7z.005
-rw-r--r-- 1 chuljeon39a chuljeon39a 5.6K Mar  1 23:47 compressed.7z.006
```
