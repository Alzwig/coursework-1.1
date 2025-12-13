#include <stdio.h>
#include <stdlib.h>
#include "../includes/text.h"
#include "../includes/sentence.h"
#include "../includes/config.h"
#include "../includes/utils.h"

void free_text(Text* t) {
    if (!t) return;

    for (size_t i = 0; i < t->len; i++) {
        free_sentence(&t->sentences[i]);
    }
    free(t->sentences);
    t->sentences = NULL;
    t->len = 0;
}

Text read_text(int* error) {
    Text t;
    size_t sentence_capacity = INIT_TEXT_SIZE;
    int end_of_text = CONTINUE_TEXT; // конец текста
    int sent_num = 1; // номер предложения

    t.len = 0;
    t.sentences = malloc(sentence_capacity * sizeof(Sentence));

    if(!t.sentences) {
        print_error(MALLOC_FAULT, error);
    }

    while (!*error && !end_of_text) {
        Sentence s = read_sentence(&end_of_text, error);
        int add_check = (!*error && s.len > 0);

        if (add_check) {
            overflow_check((void**)&t.sentences, &t.len, &sentence_capacity, sizeof(Sentence), error);
            if (!*error) {
                s.number = sent_num++;
                t.sentences[t.len++] = s;
            } else {
                free_sentence(&s);
            }
        } else free_sentence(&s);
    }

    if (*error) {
        free_text(&t);
    }

    return t;
}
