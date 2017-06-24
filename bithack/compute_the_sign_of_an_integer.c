// http://graphics.stanford.edu/~seander/bithacks.html
#include <stdio.h>
int main() {
    int v;      // we want to find the sign of v
    int sign;   // the result goes here 
    int CHAR_BIT = 8;
    // CHAR_BIT is the number of bits per byte (normally 8).
    sign = -(v < 0);  // if v < 0 then -1, else 0. 
    // or, to avoid branching on CPUs with flag registers (IA32):
    sign = -(int)((unsigned int)((int)v) >> (sizeof(int) * CHAR_BIT - 1));
    // or, for one less instruction (but not portable):
    sign = v >> (sizeof(int) * CHAR_BIT - 1); 
    sign = +1 | (v >> (sizeof(int) * CHAR_BIT - 1));  // if v < 0 then -1, else +1
    sign = (v != 0) | -(int)((unsigned int)((int)v) >> (sizeof(int) * CHAR_BIT - 1));
    // Or, for more speed but less portability:
    sign = (v != 0) | (v >> (sizeof(int) * CHAR_BIT - 1));  // -1, 0, or +1
    // Or, for portability, brevity, and (perhaps) speed:
    sign = (v > 0) - (v < 0); // -1, 0, or +1
    sign = 1 ^ ((unsigned int)v >> (sizeof(int) * CHAR_BIT - 1)); // if v < 0 then 0, else 1
    printf("%d\n", sign);
    return 0;
}
