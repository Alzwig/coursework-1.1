#pragma once
#include <stddef.h>
#include "sentence.h"

typedef struct {
    Sentence* sentences;
    size_t len;
} Text;

Text read_text(int* error);
void free_text(Text* text);
