#pragma once
#include <stdlib.h>
#include "word.h"

typedef struct {
    Word* words;
    size_t len;
    char* sep;
    int number;
} Sentence;

Sentence read_sentence(int* end_of_text, int* error);
void free_sentence(Sentence* s);
