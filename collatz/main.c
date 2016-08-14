//
//  main.c
//  collatz
//
//  Created by Jens Kanschik on 13.08.16.
//  Copyright © 2016 Jens Kanschik. All rights reserved.
//

#include <stdio.h>
#include <time.h>

void runUsingAsm(long long startValue, long long maxValue) {
    __asm {
        mov rbx, startValue
    START:
        mov rax, rbx
    LOOP:
        // rax = rax + (rax+1) / 2
        mov rcx, rax
        inc rcx
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

void runUsingAsmWithMul(long long startValue, long long maxValue) {
    __asm {
        mov rbx, startValue
        mov rcx, 3 // used for multiplication with 3
    START:
        mov rax, rbx
    LOOP:
        // rax = (3*rax + 1) / 2
        mul rcx
        add rax, 1
        sar rax, 1
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

void runWithSimpleC(long long startValue, long long maxValue) {
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

void runWithShift(long long startValue, long long maxValue) {
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
    long long startValue = 3;
    long long maxValue = (1ll) << 30;
    clock_t startClock;
    
    startClock = clock();
    runUsingAsm(startValue, maxValue);
    printf("Method runUsingAsm took %ld ms.\n", 1000*(clock() - startClock) / CLOCKS_PER_SEC);
    
    startClock = clock();
    runUsingAsmWithMul(startValue, maxValue);
    printf("Method runUsingAsmWithMul took %ld ms.\n", 1000*(clock() - startClock) / CLOCKS_PER_SEC);
    
    startClock = clock();
    runWithShift(startValue, maxValue);
    printf("Method runWithShift took %ld ms.\n", 1000*(clock() - startClock) / CLOCKS_PER_SEC);
    
    startClock = clock();
    runWithSimpleC(startValue, maxValue);
    printf("Method runWithSimpleC took %ld ms.\n", 1000*(clock() - startClock) / CLOCKS_PER_SEC);
    
    return 0;
}
