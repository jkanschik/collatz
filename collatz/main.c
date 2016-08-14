//
//  main.c
//  collatz
//
//  Created by Jens Kanschik on 13.08.16.
//  Copyright © 2016 Jens Kanschik. All rights reserved.
//

#include <stdio.h>
#include <time.h>

void runUsingAsmSkip4n1(long startValue, long maxValue) {
    __asm {
        mov rbx, startValue
    START:
        mov rax, rbx
    LOOP:
        // Shortcut: if rax = 4n+1, we can set rax to n+1 = (3*rax + 1) / 4
        // => rax = (rax - 1) >> 2
    RAX_IS_4n1:
        test rax, 0b10
        jnz RAX_IS_4n3
        sub rax, 1
        sar rax, 2
        jmp SHIFT_IF_EVEN
    RAX_IS_4n3:
        // Otherwise, rax = 4n+3:
        // rax = rax + (rax+1) / 2
        mov rcx, rax
        add rcx, 1
        sar rcx, 1
        add rax, rcx
        // Shift as long as rax is still even
    SHIFT_IF_EVEN:
        test rax, 1
        jnz IS_ODD
        // it is even, so shift and jump back
        sar rax
        jmp SHIFT_IF_EVEN
    IS_ODD:
        // jump back to LOOP if rax is greater than start = rbx
        cmp rax, rbx
        jg LOOP
        // we now know that rax is less than the start value of rbx
        // increase rbx and start again:
        add rbx, 2
        cmp rbx, maxValue
        jl START
    }
}

void runUsingAsm(long startValue, long maxValue) {
    __asm {
        mov rbx, startValue
    START:
        mov rax, rbx
    LOOP:
        // rax = rax + (rax+1) / 2
        mov rcx, rax
        add rcx, 1
        sar rcx, 1
        add rax, rcx
        // cancel if rxa is odd
    SHIFT_IF_EVEN:
        test rax, 1
        jnz IS_ODD
        // it is even, so shift and jump back
        sar rax
        jmp SHIFT_IF_EVEN
    IS_ODD:
        // jump back to LOOP if rax is greater than start = rbx
        cmp rax, rbx
        jg LOOP
        // we now know that rax is less than the start value of rbx
        // increase rbx and start again:
        add rbx, 2
        cmp rbx, maxValue
        jl START
    }
}

void runWithSimpleC(long startValue, long maxValue) {
    for (long long n = startValue; n < maxValue; n += 2) {
        
        long long i = n;
        while (i >= n) {
            i = 3*i+1;
            
            while ((i & 1) == 0) {
                i = i / 2;
            }
        }
    }
}

void runWithShift(long startValue, long maxValue) {
    for (long long n = startValue; n < maxValue; n += 2) {
        long long i = n;
        while (i >= n) {
            i = i + ((i+1) >> 1);
            
            while ((i & 1) == 0) {
                i = i >> 1;
            }
        }
    }
}

int main(int argc, const char * argv[]) {
    long startValue = 3;
    long maxValue = 100000000;
    clock_t startClock;
    
    startClock = clock();
    runUsingAsmSkip4n1(startValue, maxValue);
    printf("Took %ld ms.\n", 1000*(clock() - startClock) / CLOCKS_PER_SEC);
    
    startClock = clock();
    runUsingAsm(startValue, maxValue);
    printf("Took %ld ms.\n", 1000*(clock() - startClock) / CLOCKS_PER_SEC);
    
    startClock = clock();
    runWithShift(startValue, maxValue);
    printf("Took %ld ms.\n", 1000*(clock() - startClock) / CLOCKS_PER_SEC);
    
    startClock = clock();
    runWithSimpleC(startValue, maxValue);
    printf("Took %ld ms.\n", 1000*(clock() - startClock) / CLOCKS_PER_SEC);
    
    return 0;
}
