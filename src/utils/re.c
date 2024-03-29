#include "utils/logger.h"
#include "utils/re.h"

/*
 * From
 * https://pubs.opengroup.org/onlinepubs/009695399/functions/regcomp.html
 *
 */

#define ARRAY_SIZE(arr) (sizeof(arr)/sizeof(arr[0]))

#ifdef USE_REGEX_LIB
int match_archived(const char* string, char* pattern, int flag){
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
#endif

/**
 * @param string : (char*) string to be searched
 * @param pattern : (char*) pattern to be searched in string
 * @ret int : 0 if matched else 1
 */
int match(const char* string, const char* pattern){
    while (*string != '\0' && *pattern != '\0'){
        if(*string!=*pattern){
            break;
        }
        string++;
        pattern++;
    }

    if((*string == *pattern ) || (*string=='\n' && *pattern == '\0') || (*string == '\0' && *pattern == '\n')){
        return 0;
    }
    return 1;
}
