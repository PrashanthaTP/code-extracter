#ifndef RE_H
#define RE_H


#ifdef USE_REGEX_LIB
#include "std/regex.h"
int match_archived(const char* string, char* pattern, int flag);
#endif

int match(const char* string, const char* pattern);

#endif //RE_H
