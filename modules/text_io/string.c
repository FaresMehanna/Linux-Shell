//Modules Libraries
#include "text_io.h"
#include "string.h"
#include <string.h>
#include "../memory_manager/memory_manager.h"

TextIOState create_string(struct String *str) {

    str->data = smalloc(sizeof(char) * 4);
    if (!str->data) {
        return text_io_memory_error;
    }

    str->data[0] = '\0';
    str->actual_length = 1;
    str->memory_length = 4;

    return text_io_success;
}

TextIOState create_string_from_char_array(struct String *str, const char *char_array) {

    int len = strlen(char_array) + 1;    //original str size
    str->data = smalloc(sizeof(char) * len);

    if (!str->data) {
        return text_io_memory_error;
    }

    strcpy(str->data, char_array);
    str->actual_length = len;
    str->memory_length = len;

    return text_io_success;
}

char *clone_string(char *string) {
    if (!string) {
        return NULL;
    }

    char *to_return = smalloc(sizeof(char) * (strlen(string + 1)));
    if (!to_return) {
        return NULL;
    }

    strcpy(to_return, string);
    return to_return;
}

TextIOState free_string(struct String *str) {
    sfree(str->data);
    return text_io_success;
}

static inline TextIOState grow_string(struct String *str) {

    if (str->actual_length != str->memory_length) {
        return text_io_success;
    }

    char* new_string = srealloc(str->data, str->memory_length * 2);
    if (!new_string) {
        return text_io_memory_error;
    }

    str->memory_length = str->memory_length * 2;
    str->data = new_string;

    return text_io_success;
}

TextIOState add_char_to_string(struct String *str, char ch) {

    if (grow_string(str) != text_io_success) {
        return text_io_memory_error;
    }

    str->data[str->actual_length - 1] = ch;
    str->data[str->actual_length] = '\0';
    str->actual_length++;

    return text_io_success;
}

TextIOState trim_to_actual_size(struct String *str) {

    if (str->actual_length == str->memory_length) {
        return text_io_success;
    }

    char* new_string = srealloc(str->data, str->actual_length);
    if (!new_string) {
        return text_io_memory_error;
    }

    str->memory_length = str->actual_length;
    str->data = new_string;

    return text_io_success;
}

static inline char sml(char x) {
    if (x >= 'A' && x <= 'Z') {
        return x - 'A' + 'a';
    }
    return x;
}

uint8_t string_equal(const char *str1, const char *str2) {
    uint64_t i = 0;
    while (str1[i] != '\0' && str2[i] != '\0') {
        if (sml(str1[i]) != sml(str2[i])) {
            return 0;
        }
        i++;
    }
    return str1[i] == str2[i];
}

TextIOState get_char_pointer(struct String *str, char **destination) {
    *destination = str->data;
    return text_io_success;
}