#include <getopt.h> //getopt_long
#include <stdarg.h> //v a_*
#include <stdlib.h> //exit
#include <stdio.h>  //printf
                    //
#include "utils/cmdline.h"//
#include "utils/logger.h" //

const char* program_version = "md2code 0.1.0";
char doc[] = "Tool to extract code blocks from markdown (Literate Programming)";

static void print_help();

void parse_options(int argc,char **argv,options_tst* res_options){
    const struct option longopts[]={
        //*name,has_arg,*flag,val
        {"input",required_argument,NULL,'i'},
        {"output",required_argument,NULL,'o'},
        {"lang",required_argument,NULL,'l'},
        {"help",no_argument,NULL,'h'},
        {NULL,0,NULL,0}
    };

    int longindex = 0;
    opterr = 0;
    while(1){
        int opt = getopt_long(argc,argv,":i:o:",longopts,&longindex);
        if(opt==-1){
            break;
        }
        switch(opt){
            case 0:
                //getopt_long sets flag variable
                break;
            //src file
            case 'i'://printf("Input %s\n",optarg);
                    (*res_options).src_file =  optarg;
                     break;
            //dest file
            case 'o':printf("Output %s\n",optarg);
                     res_options->dest_file = optarg;
                      break;
            //language
            case 'l':printf("Language %s\n",optarg);
                     res_options->lang = optarg;
                     break;
            //help
            case 'h':print_help();
                     break;
            case '?':warning("Unknown option : %c\n",optopt);
                     break;
            case ':':error("Value not passed for the option %c\n",optopt);
                     exit(EXIT_FAILURE);
            default:
                      printf("Default case\n");
                      break;

        }
    }
}

static void print_help(){
    printf("%s\n\n",program_version);
    printf("%s\n",doc);
    printf("Arguments : \n");
    printf("\t --input  : %s\n","input markdown file path");
    printf("\t --output : %s\n","output markdown file path");
    printf("\t --output : %s\n","language of code blocks to be extracted");
    printf("\t          : %s\n","if `lang` option not provided only '```' block will be extracted.");
    printf("\t          : %s\n","otherwise '```lang' blocks will be extracted");
    exit(EXIT_SUCCESS);
}
