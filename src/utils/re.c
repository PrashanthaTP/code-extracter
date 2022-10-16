#include "utils/re.h"

/*
 * From
 * https://pubs.opengroup.org/onlinepubs/009695399/functions/regcomp.html
 *
 */

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))
int match(const char* string, char* pattern, int flag){
    int status;
    regex_t re;
    regmatch_t pmatch[1];//see man regexec
    if(regcomp(&re, pattern, REG_EXTENDED | REG_NOSUB | flag)!=0){
        return 0;
    }
    status = regexec(&re, string, ARRAY_SIZE(pmatch), pmatch, 0);
    regfree(&re);
    if(status!=0){
        return 0;
    }
    return 1;
        
}
