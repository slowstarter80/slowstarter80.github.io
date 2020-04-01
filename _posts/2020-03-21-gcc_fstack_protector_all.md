---
layout: single
title: gcc fstack-protector-all
date : 2020-02-23 01:33:04 +0900
last_modified_at: 2020-04-01 23:03:43 +0900
categories: [gcc]
tags: [gcc]
comments: true
public : true
parent : vim
permalink : /wiki/gcc_fstack_protector_all/
---


---
# reference
<br />

# fstack-protector-all

## source code
```c 
#include <stdio.h>

int testFunc1()
{
	int i = 3;
	int buf[2] = {0,};
	int j = 4;

	printf("Input number: ");
	scanf("%d",  &i);

	for (j = 0; j < i; j++) {
		buf[j] = j;
		printf("%s, %d\n", __func__, buf[j]);
	}

	return 0;
}
int main(void)
{
	testFunc1();

	return 0;
}
```
## compile(generate executable file)
```bash
$ arm-none-linux-gnueabihf-gcc -o stack_smashing_protector -static stack_smashing_protector.c -fstack-protector-all
```

## compile(generate assembly code)
```bash
$ arm-none-linux-gnueabihf-gcc -S -o stack_smashing_protector.s -static stack_smashing_protector.c -fstack-protector-all
```
## output(with enabling -fstack-protector-all)
```bash 
$ qemu-arm stack_smashing_protector
Input number: 3
testFunc1, 0
testFunc1, 1
testFunc1, 2
*** stack smashing detected ***: <unknown> terminated
qemu: uncaught target signal 6 (Aborted) - core dumped
Aborted 
```
## generated assembly code
```c 
	.arch armv7-a
	.eabi_attribute 28, 1
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.file	"stack_smashing_protector.c"
	.text
	.section	.rodata
	.align	2
.LC0:
	.ascii	"Input number: \000"
	.align	2
.LC1:
	.ascii	"%d\000"
	.align	2
.LC2:
	.ascii	"%s, %d\012\000"
	.align	2
.LC3:
	.word	__stack_chk_guard
	.text
	.align	1
	.global	testFunc1
	.arch armv7-a
	.syntax unified
	.thumb
	.thumb_func
	.fpu neon
	.type	testFunc1, %function
testFunc1:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #24
	add	r7, sp, #0
	movw	r3, #:lower16:.LC3
	movt	r3, #:upper16:.LC3
	ldr	r3, [r3]
	str	r3, [r7, #20]
	mov	r3,#0
	movs	r3, #3
	str	r3, [r7, #4]
	add	r3, r7, #12
	vmov.i32	d16, #0  @ v8qi
	vstr	d16, [r3]
	movs	r3, #4
	str	r3, [r7, #8]
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	bl	printf
	adds	r3, r7, #4
	mov	r1, r3
	movw	r0, #:lower16:.LC1
	movt	r0, #:upper16:.LC1
	bl	__isoc99_scanf
	movs	r3, #0
	str	r3, [r7, #8]
	b	.L2
.L3:
	ldr	r3, [r7, #8]
	lsls	r3, r3, #2
	add	r2, r7, #24
	add	r3, r3, r2
	ldr	r2, [r7, #8]
	str	r2, [r3, #-12]
	ldr	r3, [r7, #8]
	lsls	r3, r3, #2
	add	r2, r7, #24
	add	r3, r3, r2
	ldr	r3, [r3, #-12]
	mov	r2, r3
	movw	r1, #:lower16:__func__.5966
	movt	r1, #:upper16:__func__.5966
	movw	r0, #:lower16:.LC2
	movt	r0, #:upper16:.LC2
	bl	printf
	ldr	r3, [r7, #8]
	adds	r3, r3, #1
	str	r3, [r7, #8]
.L2:
	ldr	r3, [r7, #4]
	ldr	r2, [r7, #8]
	cmp	r2, r3
	blt	.L3
	movs	r3, #0
	movw	r2, #:lower16:.LC3
	movt	r2, #:upper16:.LC3
	ldr	r1, [r2]
	ldr	r2, [r7, #20]
	eors	r1, r2, r1
	beq	.L5
	bl	__stack_chk_fail
.L5:
	mov	r0, r3
	adds	r7, r7, #24
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	testFunc1, .-testFunc1
	.section	.rodata
	.align	2
.LC4:
	.word	__stack_chk_guard
	.text
	.align	1
	.global	main
	.syntax unified
	.thumb
	.thumb_func
	.fpu neon
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #8
	add	r7, sp, #0
	movw	r3, #:lower16:.LC4
	movt	r3, #:upper16:.LC4
	ldr	r3, [r3]
	str	r3, [r7, #4]
	mov	r3,#0
	bl	testFunc1
	movs	r3, #0
	movw	r2, #:lower16:.LC4
	movt	r2, #:upper16:.LC4
	ldr	r1, [r2]
	ldr	r2, [r7, #4]
	eors	r1, r2, r1
	beq	.L8
	bl	__stack_chk_fail
.L8:
	mov	r0, r3
	adds	r7, r7, #8
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
	.size	main, .-main
	.section	.rodata
	.align	2
	.type	__func__.5966, %object
	.size	__func__.5966, 10
__func__.5966:
	.ascii	"testFunc1\000"
	.ident	"GCC: (GNU Toolchain for the A-profile Architecture 9.2-2019.12 (arm-9.10)) 9.2.1 20191025"
	.section	.note.GNU-stack,"",%progbits
```

