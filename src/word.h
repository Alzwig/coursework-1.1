#pragma once
#include <stdlib.h>

typedef struct {
    char* chars;
    char* sep;
    size_t len;
} Word;

Word read_word(int* end, int* error);
void free_word(Word* w);
