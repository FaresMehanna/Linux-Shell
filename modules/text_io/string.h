/** 
 * File: string.h
 * ---------------
 * Defines the interface for the string.
 *
 * This module handles strings.
 */
#ifndef text_io_string_h
#define text_io_string_h

//Modules Libraries
#include "text_io.h"

/** 
 * struct string
 * ---------------
 * string in c.
 *
 * data => actual address where the data starts.
 * actLength => actual length of the string.
 * memlength => memory size reserved for the string.
 */
struct String {
    char *data;
    int actual_length;
    int memory_length;
};

/** 
 * Function: createString
 * ---------------
 * create string and return SUCC in case of malloced.
 *
 * str => struct malloced/smalloced by the user.
 */
TextIOState create_string(struct String *str);
TextIOState create_string_from_char_array(struct String *str, const char *char_array);

char *clone_string(char *x);

/** 
 * Function: freeString
 * ---------------
 * Free string and return SUCC in case of freed.
 *
 * str => struct defined by the user.
 */
TextIOState free_string(struct String *str);

/** 
 * Function: addCharToString
 * ---------------
 * add char to the end of the string.
 *
 * str => struct defined by the user.
 * ch => the char which will be added to the end of the string.
 */
TextIOState add_char_to_string(struct String *str, char ch);

/** 
 * Function: trimToActSize
 * ---------------
 * remove any unused memory malloced by the string.
 *
 * str => struct defined by the user.
 */
TextIOState trim_to_actual_size(struct String *str);

/** 
 * Function: getCharPointer
 * ---------------
 * get the pointer of the string.
 *
 * str => struct defined by the user.
 * destination => destination to write the address.
 */
TextIOState get_char_pointer(struct String *str, char **destination);


int string_equal(const char *str1, const char *str2);

#endif
