//
//  main.c
//  collatz
//
//  Created by Jens Kanschik on 13.08.16.
//  Copyright © 2016 Jens Kanschik. All rights reserved.
//

#include <stdio.h>
#include <time.h>

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
    IF_EVEN:
        test rax, 1
        jnz IS_ODD
        // it is even, so shift and jump back
        sar rax
        jmp IF_EVEN
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
