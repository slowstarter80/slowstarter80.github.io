---
layout: single
title: arm gcc assembly in C
date : 2020-01-15 01:33:04 +0900
last_modified_at: 2020-01-28 01:23:58 +0900
category: gcc
tag: [arm, assembly]
comments: true
public : true
parent : gcc
permalink : /wiki/arm_gcc_assembly_in_c/
--- 


# arm gcc assembly in C
  * General form of an inline assembler
   ```c
asm(code : output operand list : input operand list : clobber list);
   ```
  * Rotating bits example
   ```c
asm("mov %[result], %[value], ror #1" : [result] "=r" (y) : [value] "r" (x));
   ```
  * ex2) space, newlines and C comments can be used to increase readability
   ```c
asm("mov    %[result], %[value], ror #1"

        : [result]"=r" (y) /* Rotation result. */
        : [value]"r"   (x) /* Rotated value. */
        : /* No clobbers */
);
   ```
  * ex3) old form
   ```c 
asm("mov %0, %1, ror #1" : "=r" (result) : "r" (value));
   ```
  * ex4) you can write more than one assembler instruction in a single inline asm statement. To make it more readable, you can put each instruction on a separate line.
   ```c
asm volatile(
"mov     r0, r0\n\t"
"mov     r0, r0\n\t"
"mov     r0, r0\n\t"
"mov     r0, r0"
);
   ```
  * To prevent code opmization by compiler, you need to use 'volatie' keyword.
  * Constraint characters may be prepended by a single constraint modifier. Constraints without a modifier specify read-only operands. Modifiers are: 

    | Modifier  | Specifies  |
    |:---------:|:-----------:|
    | = 	| Write-only operand, usually used for all output operands |
    | + 	| Read-write operand, must be listed as an output operand  |
    | & 	| A register that should be used for output only           |
    {:.mbtablestyle}



  * clobber list. asm code에 의해서 변경되는 것을 표시(?)
   ```c
   asm volatile("mrs r12, cpsr\n\t"
       "orr r12, r12, #0xC0\n\t"
       "msr cpsr_c, r12\n\t" :: : "r12", "cc", "memory");
   c *= b; /* This is safe. */
   asm volatile("mrs r12, cpsr\n"
       "bic r12, r12, #0xC0\n"
       "msr cpsr_c, r12" ::: "r12", "cc", "memory");
   ```
  * ex5) mov.c


    ```c
    #include <stdio.h>
    
    int asm_mov_ex(int x, int y);
    
    __asm__ (".global asm_mov_ex	\n\
    		asm_mov_ex:	\n\
    		mov r0, r1	\n\
    		mov pc, lr	\n\
    		");
    
    int main(void)
    {
    	int mov;
    	printf("\n+-------------------+\n");
    	printf("|ARM Instruction MOV|\n");
    	printf("\n+-------------------+\n");
    
    	mov = asm_mov_ex(3, 4);
    	printf("mov = %d\n\n", mov);
    
    	return 0;
    }
    ```


  * ex6) lsl.c

    ```c
    #include <stdio.h>
    
    int asm_lsl_ex(int x, int y)
    {
    	int a;
    
    __asm__ volatile( "lsl	%[param1], %[param2], %[param3]	\n\t"
    	:[param1] "=r" (a): [param2] "r" (x), [param3] "r"(y):
    	);
    
    	return a;
    
    } 
    
    int main(void)
    {
    	int mov;
    	printf("\n+-------------------+\n");
    	printf("|ARM Instruction LSL|\n");
    	printf("\n+-------------------+\n");
    
    	mov = asm_lsl_ex(2, 3);
    	printf("mov = %d\n\n", mov);
    
    	return 0;
    }
    ```

  * Reference
      * [http://www.ethernut.de/en/documents/arm-inline-asm.html](http://www.ethernut.de/en/documents/arm-inline-asm.html)

