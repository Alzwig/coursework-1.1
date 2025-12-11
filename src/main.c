#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "config.h"
#include "utils.h"
#include "text.h"
#include "primary_processing.h"
#include "print_text.h"
#include "option_1.h"
#include "option_2.h"
#include "option_3.h"
#include "option_4.h"


int main(void) {
    print_project_info();
    int error = NO_ERROR;

    int option = read_option(&error);
    Text text;

    switch (option) {
        case PRINT_TEXT:
            text = read_text(&error);
            remove_duplicate_sentences(&text, &error);
            print_text(&text);
            free_text(&text);
            break;
        case PRINT_WORDS:{
            text = read_text(&error);
            remove_duplicate_sentences(&text, &error);
            size_t total_words = 0;
            WordCount* entries = count_words(&text, &error, &total_words);
            if (!error && entries) {
                print_word_entries(entries, total_words, &error);
            }
            for (size_t i = 0; i < total_words; i++) {
                free(entries[i].word);
            }
            free(entries);
            free_text(&text);
            break;
        }
        case REVERSE_SYM:
            text = read_text(&error);
            remove_duplicate_sentences(&text, &error);
            reverse_text_words(&text);
            print_text(&text);
            free_text(&text);
            break;
        case DELETE_SENTENCES:
            text = read_text(&error);
            remove_duplicate_sentences(&text, &error);
            delete_sentences_with_comma(&text);
            print_text(&text);
            free_text(&text);
            break;
        case SORT_SENTENCES: 
            text = read_text(&error);
            remove_duplicate_sentences(&text, &error);
            sort_text(&text);
            print_text(&text);
            free_text(&text);
            break;
        case HELP: 
            print_help();
            break;
    }

    return 0;
}
