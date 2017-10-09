#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hijacker(void) {
    int x = random();
    printf("HIJACKED! %d\n", x);
    exit(0);
}

int factorial(int n) {
    // YOUR CODE HERE (1): Change this code so it actually prints the
    // return address. Use `gdb`, `x`, etc. to figure out where the
    // return address is located on the stack. You'll use pointer
    // arithmetic on `buf` to find the location of the return address.
    // NB: Undefined behavior is OK for this section.
    char buf[BUFSIZ];
    void* retaddr;
    // NB: The `24` constant depends on compiler version!
    memcpy(&retaddr, &buf[BUFSIZ + 24], sizeof(void*));
    sprintf(buf, "Calling %d!, return address %p", n, retaddr);
    puts(buf);

    int x;
    if (n == 0) {
        x = 1;
    } else {
        x = factorial(n - 1) * n;
    }

    // YOUR CODE HERE (2): Add code here that *modifies the return
    // address* -- and that is all; no other changes to memory or
    // other functions! -- in such a way that running the program
    // prints `HIJACKED! 24` instead of `5! == 120`.
    // You may want to use gdb and `objdump -S factorial`, as well
    // as trial and error.

    if (n == 4) {
        retaddr = hijacker;
        retaddr = memchr(hijacker, 0xe8, 100);
        retaddr = (const char*) retaddr + 5;
        memcpy(&buf[BUFSIZ + 24], &retaddr, sizeof(retaddr));
    }

    return x;
}

int main() {
    // Print out some useful facts about code layout: the addresses of
    // `main` and `factorial`, and the boundaries of the code segment.
    printf("main == %p, factorial == %p\n", main, factorial);

    extern char _start[], _fini[];
    printf("code segment boundaries: %p, %p\n", _start, _fini);

    // Call factorial(5) and print the result
    printf("%d! == %d\n", 5, factorial(5));
}
