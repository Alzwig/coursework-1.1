#include <stdio.h>
#include <ctype.h>
#include "word.h"
#include "config.h"
#include "utils.h"

void free_word(Word* w){
    if (!w) return;

    free(w->chars);
    free(w->sep);
    w->chars = NULL;
    w->sep = NULL;
    w->len = 0;
}

int is_char_in_word(char c){
    return isalnum(c) || c == '-';
}


Word read_word(int *end_of_text, int* error) {
    Word w;
    size_t chars_capacity = INIT_WORD_SIZE;
    size_t sep_capacity = INIT_SEP_SIZE;
    size_t sep_len = 0;

    w.len = 0;
    w.chars = malloc(chars_capacity * sizeof(char));
    w.sep = malloc(sep_capacity * sizeof(char));

    if(!w.chars || !w.sep) {
        print_error(MALLOC_FAULT, error);
    }

    int reading_word = READING_WORD; // читаем слово
    int newline_count = INITIAL_NEWLINE_COUNT; // для поимки \n\n
    int stop = CONTINUE; // остановка чтения слова
    int c = 0;

    while (!*error && !stop) {
        c = getchar();

        if (c == EOF) {
            *end_of_text = END_OF_TEXT;
            stop = STOP;
        } else {
            if (reading_word) {
                if (is_char_in_word(c)) {
                    newline_count = INITIAL_NEWLINE_COUNT;
                    overflow_check((void**)&w.chars, &w.len, &chars_capacity, sizeof(char), error);
                    if (!*error) w.chars[w.len++] = c;
                } else reading_word = NOT_READING_WORD;
            }   

            if (!reading_word && !stop) {
                if (c == '\n') {
                    newline_count++;
                    if (newline_count >= END_TEXT_NEWLINE_COUNT) {
                        *end_of_text = END_OF_TEXT;
                        stop = STOP;
                    }
                } else newline_count = INITIAL_NEWLINE_COUNT;

                if (is_char_in_word(c)) {
                    if (ungetc(c, stdin) == EOF) print_error(UNGETC_FAULT, error);
                    stop = STOP;
                } else {
                    overflow_check((void**)&w.sep, &sep_len, &sep_capacity, sizeof(char), error);
                    if (!*error) w.sep[sep_len++] = (char)c;
                    if (c == '.') stop = STOP;
                }
            }
        }
    }


    if (!*error && c == EOF) *end_of_text = END_OF_TEXT;

    if (!*error) {
        w.chars[w.len] = '\0';
        w.sep[sep_len] = '\0';
    } else {
        free_word(&w);
    }

    return w;
}


