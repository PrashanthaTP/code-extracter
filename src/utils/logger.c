#include <stdarg.h> //v a_*
#include <stdio.h>

#include "utils/logger.h"

char* colorize_experiment(char *res,const char* color,const char* format,...){
    va_list args;
    va_start(args,format);//second arg is the last named arg
    sprintf(res,format,args);
    va_end(args);
    return res;

}

//Manual page sprintf(3) line 339/385
void format_msg(int *(*format_func)(char *r,char* format,...),char *res,...){
    
}

char* colorize(char** res,const char* color,const char *msg){
    sprintf(*res,"%s%s%s",color,msg,RESET);
    return *res;
}

char* surround_with_char(char **res,const char *msg){
    sprintf(*res,"[ %s ]",msg);
    return *res;
}

void warning(const char *format,...){
    va_list args;
    fprintf(stdout,"[ "YELLOW"warning"RESET" ] ");
    //char *res=NULL;
    //printf("warning");
    //printf("%s",colorize(&res,YELLOW,"warning\n"));
    //fprintf(stdout,surround_with_char(&res,colorize(&res,YELLOW,"warning")));
    va_start(args,format);//if args is changing in runtime va_ fns required
    vfprintf(stdout,format,args);
    va_end(args);
    //fprintf(stdout,"\n");
}

void error(const char *format,...){
    va_list args;
    fprintf(stderr,"[ "RED"error"RESET" ] ");
    va_start(args,format);//second arg is the last named arg
    vfprintf(stderr,format,args);
    va_end(args);
    //fprintf(stderr,"\n");
}

