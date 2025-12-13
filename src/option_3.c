#include <string.h>
#include "../includes/text.h"
#include "../includes/sentence.h"
#include "../includes/word.h"
#include "../includes/utils.h"
#include "../includes/option_3.h"

void delete_sentences_with_comma(Text* text) {

    size_t i = 0; // индекс текущего предложения
    size_t new_len = 0; // индекс для "сжатого" массива без запятых

    while (i < text->len) {
        int has_comma = 0;
        size_t j = 0;

        // проверяем слова текущего предложения на запятую
        while (j < text->sentences[i].len && !has_comma) {
            size_t k = 0;
            while (k < text->sentences[i].words[j].len && !has_comma) {
                char* sep = text->sentences[i].words[j].sep;
                if (sep) {
                    size_t l = 0;
                    while (l < strlen(sep) && !has_comma) {
                        if (sep[l] == ',') {
                            has_comma = 1;
                        }
                        l++;
                    }
                }
                k++;
            }
            j++;
        }

        // если запятой нет, переносим предложение на место new_len
        if (!has_comma) {
            if (new_len != i) {
                text->sentences[new_len] = text->sentences[i];
            }
            new_len++;
        } else {
            // если есть запятая — освобождаем память за предложение
            free_sentence(&text->sentences[i]);
        }

        i++;
    }

    text->len = new_len; // обновляем длину текста
}

