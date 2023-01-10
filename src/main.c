#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "huffman.h"

int main()
{
     FILE *in;
     FILE *out1;

     in = fopen("test", "rb");
     out1 = fopen("output_huffman","wb")
     huffman_encode_file(in, out1);
     fclose(in);
     fclose(out1);

     return 0;
}