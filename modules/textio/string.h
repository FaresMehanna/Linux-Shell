/** 
 * File: string.h
 * ---------------
 * Defines the interface for the string.
 *
 * This module handles strings.
 */
#ifndef _TEXTIO_MODULE_STRING_
#define _TEXTIO_MODULE_STRING_

/** 
 * struct string
 * ---------------
 * string in c.
 *
 * data => actual address where the data starts.
 * actLength => actual length of the string.
 * memlength => memory size reserved for the string.
 */
struct string {
    char *data;
    int actLength;
    int memLength;
};

/** 
 * Function: createString
 * ---------------
 * create string and return SUCC in case of malloced.
 *
 * str => struct defined by the user.
 */
_text_io_state createString(struct string *str);

_text_io_state createStringFromCharArr(struct string *str, const char *oStr);

char *cloneStr(char *x);

/** 
 * Function: freeString
 * ---------------
 * Free string and return SUCC in case of freed.
 *
 * str => struct defined by the user.
 */
_text_io_state freeString(struct string *str);

/** 
 * Function: addCharToString
 * ---------------
 * add char to the end of the string.
 *
 * str => struct defined by the user.
 * ch => the char which will be added to the end of the string.
 */
_text_io_state addCharToString(struct string *str, char ch);

/** 
 * Function: trimToActSize
 * ---------------
 * remove any unused memory malloced by the string.
 *
 * str => struct defined by the user.
 */
_text_io_state trimToActSize(struct string *str);

/** 
 * Function: getCharPointer
 * ---------------
 * get the pointer of the string.
 *
 * str => struct defined by the user.
 * destination => destination to write the address.
 */
_text_io_state getCharPointer(struct string *str, char **destination);


int streq(const char *str1, const char *str2);

#endif
