#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "config.h"

void print_project_info(void) {
    printf("Course work for option 4.6, created by Ivanov Egor.\n");
}

int read_option(int* error) {
    int option = -1;
    int scanf_len = scanf("%d", &option);

    if (scanf_len != 1) {
        print_error(INVALID_OPTION, error);
        option = -1;
    }
    else if (option < 0 || option > 5) {
        print_error(INVALID_OPTION, error);
        option = -1;
    }

    return option;
}

void print_help(void) {
    printf("0 - Вывод текста после первичной обязательной обработки\n");
    printf("1 - Распечатать каждое слово и количество его повторений\n");
    printf("2 - Развернуть буквы каждого слова в обратном порядке\n");
    printf("3 - Удалить предложения, в которых встречается запятая\n");
    printf("4 - Отсортировать предложения по уменьшению значения кода 5 символа предложения\n");
    printf("5 - Справка о функциях\n");
}

void print_error(int error_code, int* error) {
    switch (error_code) {
        case MALLOC_FAULT:
            printf("Error: Malloc fault\n");
            *error = MALLOC_FAULT;
            break;
        case REALLOC_FAULT:
            printf("Error: Realloc fault\n");
            *error = REALLOC_FAULT;
            break;
        case UNGETC_FAULT:
            printf("Error: Ungetc fault\n");
            *error = UNGETC_FAULT;
            break;
        case INVALID_OPTION:
            printf("Error: Invalid option\n");
            *error = INVALID_OPTION;
            break;
        default:
            break;
    }
}

void overflow_check(void** buff, size_t* len, size_t* capacity, size_t elem_size, int* error) {
    if (!*error && (*len + 1 >= *capacity)) {
        size_t new_capacity = (*capacity) * 2;
        void* tmp = realloc(*buff, new_capacity * elem_size);
        if (!tmp) {
            print_error(REALLOC_FAULT, error);
        } else {
            *buff = tmp;
            *capacity = new_capacity;
        }
    }
}
