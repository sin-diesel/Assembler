#include <stdio.h>
#include <stdlib.h>
#include "Onegin.h"
#include "stack_hed.h"
#include "asem.h"

int main(int argc, char** argv) {

    if (argc < 4) {
        return INPUT_ERROR;
    }

    struct input data = acquire_input(argv);

    char* buffer = create_buffer(data.name_in);
    char* buffer_cpy = create_buffer(data.name_in);

    int size = count_file(data.name_in);
    int str_size = count_str(buffer, size);

    struct string* strings = calloc(str_size, sizeof(struct string));
    struct lab* labels = calloc(str_size, sizeof(struct lab));

    get_str(buffer, strings);

    char* bytecode = (char*) calloc(size, sizeof(char));

    int count = compile(strings, labels, str_size, bytecode, 0);

    struct string* strings_cpy = calloc(str_size, sizeof(struct string));
    get_str(buffer_cpy, strings_cpy);

    compile(strings_cpy, labels, str_size, bytecode, 1);

    char* new_place = (char*) realloc(bytecode, count);

    for (int i = 0; i < count; ++i) {
        printf("%d ", bytecode[i]);
    }
    printf("\n");

    FILE* out = fopen(data.name_out, data.type_out);
    fwrite(bytecode, sizeof(char), count, out);
    fclose(out);

    free(new_place);
    free(strings);
    free(labels);
    free(buffer);
    free(buffer_cpy);
    return 0;
}