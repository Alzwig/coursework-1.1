#pragma once
#include <stddef.h>

void print_project_info(void);
int read_option(int* error);
void print_help(void);
void print_error(int error_code, int* error);
void overflow_check(void** buff, size_t* len, size_t* capacity, size_t elem_size, int* error);
