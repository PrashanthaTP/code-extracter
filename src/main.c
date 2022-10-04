#include <stdio.h>
#include <stdlib.h> // exit


#include "utils/cmdline.h"
void parse_options(int argc,char **argv,options_tst*options_st);

int main(int argc,char **argv){
    options_tst options_st= {"",""};
    parse_options(argc,argv,&options_st);
    printf("src file :%s\n",options_st.src_file);
    printf("dest file :%s\n",options_st.dest_file);
    return 0;
}


