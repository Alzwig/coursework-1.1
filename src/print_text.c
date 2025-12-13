#include <stdio.h>
#include "../includes/print_text.h"
#include "../includes/text.h"

void print_sentence_line(Sentence* s) {
    size_t i = 0;

    if (s) {
        while (i < s->len) {
            Word* word = &s->words[i];
            if (word->chars) {
                printf("%s", word->chars);
            }
            if (word->sep) {
                printf("%s", word->sep);
            }
            i++;
        }
        if (s->sep) {
            printf("%s", s->sep);
        }
        printf("\n");
    }
}

void print_text(Text* text) {
    size_t i = 0;

    if (text && text->sentences) {
        while (i < text->len) {
            print_sentence_line(&text->sentences[i]);
            i++;
        }
    }
}
