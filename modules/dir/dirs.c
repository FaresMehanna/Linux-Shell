#include <unistd.h>
#include <stdio.h>
#include "dirs.h"
#include "../memorymanger/memmange.h"
#include "../textio/string.h"

static inline char* getCurrDir(){
	char* cwd = smalloc(sizeof(char)*1024);
	if (getcwd(cwd, sizeof(char)*1024) != NULL)
       return cwd;
	return NULL;
}