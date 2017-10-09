#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>

/// spec_size(spec)
///    Return the size of the C struct specified by the type specification `spec`,
///    as compiled on an x86-64 machine. A type specification is a string of
///    characters where each character corresponds to a struct member of some
///    fundamental type:
///
///         `c`    char (or signed char, unsigned char)
///         `s`    short (or unsigned short)
///         `i`    int (or unsigned int)
///         `l`    long (or unsigned long)
///         `z`    size_t
///         `f`    float
///         `d`    double
///         `p`    pointer
///
///    See `README.md` or the Section 1 wiki page for hints and advanced features.

size_t spec_size(const char* spec) {
    (void) spec;
    size_t total_size = 0;
    size_t max_alignment = 1;
    size_t temp_size = 0;
    for (int i = 0; spec[i] != '\0'; i++) {
        //printf("%c\n", spec[i]);
        char temp_char = spec[i];
        if (temp_char == 'c') {
            temp_size = 1;
        } else if (temp_char == 's') {
            temp_size = 2;
        } else if (temp_char == 'i' | temp_char == 'f') {
            temp_size = 4;
        } else if (temp_char == 'l' | temp_char == 'z' | temp_char == 'd' | temp_char == 'p') {
            temp_size = 8;
        } 
        if (temp_size > max_alignment) 
            max_alignment = temp_size;
        total_size += temp_size;
    }
    size_t final_alignment = total_size;
    while (final_alignment % max_alignment != 0) {
       final_alignment += 1;
    }  
    //printf("%zu\n",final_alignment);
    return final_alignment;
}




/// spec_print(spec, ptr)
///    Print the contents of the memory located at `ptr` as interpreted
///    by type specification `spec`. For example:
///
///        int i = 10;
///        spec_print("i", &i);
///
///    might print something like
///
///        7fffffabc int 10
///
///    (assuming `i` is located at address 0x7fffffabc), and
///
///        struct { char c; int d; } x = { 'A', 24 };
///        spec_print("ci", &x);
///
///    might print something like
///
///        7ffffffabc char A
///        7ffffffac0 int 24
///
///    You'll need to add your own tests of `spec_print`.

void spec_print(const char* spec, const void* data) {
    (void) spec, (void) data;
    
    for (int i = 0; spec[i] != '\0'; i++) {
        //printf("%c\n", spec[i]);
        size_t temp_size = 0;
        char temp_char = spec[i];
        char* temp_address = (char*) data;
        if (temp_char == 'c') {
            temp_size = 1;
            printf("%p char %c\n", temp_address, *temp_address);
            temp_address += temp_size;
            
        } else if (temp_char == 's') {
            temp_size = 2;
            printf("%p char %hd\n", temp_address, *(const short*) temp_address);
            temp_address += temp_size;
            
        } else if (temp_char == 'i') {
            temp_size = 4;
            printf("%p int %d\n", temp_address, *(const int*) temp_address);
            temp_address += temp_size;
            
        } else if (temp_char == 'f') {
            temp_size = 4;
            printf("%p float %g\n", temp_address, *(const float*) temp_address);
            temp_address += temp_size;
            
        } else if (temp_char == 'l') {
            temp_size = 8;
            printf("%p long %ld\n", temp_address, *(const long*) temp_address);
            temp_address += temp_size;
            
        } else if (temp_char == 'z') {
            temp_size = 8;
            printf("%p size_t %zu\n", temp_address, *(const size_t*) temp_address);
            temp_address += temp_size;
            
        } else if (temp_char == 'd') {
            temp_size = 8;
            printf("%p double %g\n", temp_address, *(const double*) temp_address);
            temp_address += temp_size;
            
        } else if (temp_char == 'p') {
            temp_size = 8;
            printf("%p ptr %p\n", temp_address, *(const void**) temp_address); 
            //temp_address = (char*) data + temp_size;
            temp_address += temp_size; 
        } 
    }
}


int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; ++i) {
        printf("%8zu %s\n", spec_size(argv[i]), argv[i]);
    }
    
    // test spec_print
    
    struct {
        char c;
        int d;
    } x = {'A',24};
    
    //struct x = 
    spec_print("ci",&x);
    
     /*   {
        struct { char c; int d; } x = { 'A', 24 };
        spec_print("ci", &x);

        int a[4] = { 0, 1, 2, 3 };
        spec_print("iiii", &a);
        spec_print("ffff", &a); // !!
        spec_print("pp", &a); // !!
    }*/
}
