//
//  main.c
//  collatz
//
//  Created by Jens Kanschik on 13.08.16.
//  Copyright © 2016 Jens Kanschik. All rights reserved.
//

#include <stdio.h>



int main(int argc, const char * argv[]) {
    
    for (long start = 3; start < 2^30; start += 2) {
        long n = start;
        while (n >= start) {
            n = n + ((n+1) >> 1);
            
            while ((n & 1) == 0) {
                n = n >> 1;
            }
        }
        
        if ((start % 10000001) == 0) {
            printf("Starting %d is ok.\n", start);
        }
        
    }
    
    // insert code here...
    printf("Hello, World!\n");
    return 0;
}
