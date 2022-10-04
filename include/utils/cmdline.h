#ifndef CMDLINE_H
#define CMDLINE_H

struct options_tst{
    char* src_file;
    char* dest_file;
};

typedef struct options_tst options_tst;

extern const char* program_version;
extern char doc[];

#endif //CMDLINE_H
