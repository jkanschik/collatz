# Implementations of the collatz algorithm

This is a simple c programme to check the collatz conjecture https://en.wikipedia.org/wiki/Collatz_conjecture.

Needless to say, this is not meant to be a contribution to the research - according to the wikipedia page, the conjecture has been confirmed up to roughly 2^60, this programm is able to test up to 2^40 in reasonable time (few hours or so) on a normal computer.

The programme implements different implementations, which differ significantly in performance:

1. A naive implementation using C and normal addition and multiplication (e.g. n = 3*n+1; n = n/2 for the main steps).
2. An improved C implementation using shifts and avoiding the multiplication by three (i.e. n = (3*n + 1)/2 is computed in one step: n = n + (n+1)>>2; n = n/2 is replaced with n = n >> 2).
3. An assembler version using multiplication with 3 ( n = (3*n+1) >> 2).
4. An assembler version using addition an shift instead of multiplication with 3 (n = n + (n+1)>>2 as in version 2).

A naive (yes, I know it's naive) benchmark on my current MacBook shows the following times to check all number less than 1,000,000,000:

| Implementation | Time |
|----------------|------|
| Naive C implementation | 64,549 ms |
| Improved C implementation | 14,561 ms |
| Assembler with multiplication with 3 | 8,177 ms |
| Assembler without multiplication with 3 | 7,192 ms |

Actually I was surprised to see the size of the effect of using shift / avoiding multiplication by 3 in the normal c code as well as in assembler. I expected to see a difference, but not this size.
