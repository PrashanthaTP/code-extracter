#include <stdio.h>
#include <stdlib.h> // exit


#include "utils/cmdline.h"
#include "utils/logger.h"
#include "utils/re.h"

void parse_options(int argc,char **argv,options_tst*options_st);

const char *identifier_code_block_start = "```";

void print_options(options_tst options_st){
    printf("src file  :%s\n",options_st.src_file);
    printf("dest file :%s\n",options_st.dest_file);
}

//https://linux.die.net/man/3/getline
//TODO : Track dynamically allocated variables
//Read line by line : https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
//Functions in pointers : https://stackoverflow.com/questions/4222661/functions-in-structure
void scan_file(char *file_path){
    printf("Reading file %s...\n",file_path);

    FILE *file;
    if(!(file=fopen(file_path,"r"))){
        error("[ce] \"%s\" couldn't be read.",file_path);
        exit(EXIT_FAILURE);
    }

    unsigned int n_line = 0;
    const size_t MAX_CHARS = 150;
    //char* line = NULL;
    char *line = (char *)malloc(sizeof(char)*MAX_CHARS); //FREE THIS
    size_t c_line = MAX_CHARS;
    size_t n_read_char;//gets number of characters read;
    while((n_read_char = getline(&line,&c_line,file))!=1){
        printf("%s",line);
        printf("Re lib : %d\n", match(line,"^```\s*$",REG_ICASE));
        return;
    }
    free(line);

}
int main(int argc,char **argv){
    options_tst options_st= {"",""};
    parse_options(argc,argv,&options_st);
    print_options(options_st);
    //scan_file(options_st.src_file);
    return 0;
}


