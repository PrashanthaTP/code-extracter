#ifndef LOGGER_H
#define LOGGER_H

#include "utils/logger.h"

#define OPT_INPUT "opt_input"
#define OPT_OUTPUT "opt_output"

#define RED "\033[31m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"


char* colorize(char** res,const char* color,const char *msg);
char* colorize_experiment(char* res,const char* color,const char* format,...);

char* surround_with_char(char** res,const char* msg);

void warning(const char *format,...);
void error(const char *format,...);

#endif //LOGGER_H
