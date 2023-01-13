#include "file_size.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>


long long calculate_words(FILE* in)
{
    long long size=0;
    fseek(in, 0, SEEK_END);
    size = ftell(in);
    return size;
}