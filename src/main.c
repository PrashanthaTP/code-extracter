#include <getopt.h>
#include <stdarg.h> //v a_*
#include <stdio.h>
#include <stdlib.h> // exit
#include <string.h>

const char* program_version = "md2code 0.1.0";
static char doc[] = "Tool to extract code blocks from markdown (Literate Programming)";



#define OPT_INPUT "opt_input"
#define OPT_OUTPUT "opt_output"

#define RED "\033[31m"
#define YELLOW "\x1b[33m"
#define RESET "\x1b[0m"


char* colorize(char** res,const char* color,const char *msg);
char* colorize_experiment(char* res,const char* color,const char* format,...);

char* surround_with_char(char** res,const char* msg);

struct options_tst{
    char* src_file;
    char* dest_file;
};

typedef struct options_tst options_tst;

void print_help(){
    printf("%s\n\n",program_version);
    printf("%s\n",doc);
}


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

void parse_options(int argc,char **argv,options_tst* res_options){
    const struct option longopts[]={
        //*name,has_arg,*flag,val
        {"input",required_argument,NULL,'i'},
        {"output",required_argument,NULL,'o'},
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
            case 'i':printf("Input %s\n",optarg);
                    (*res_options).src_file =  optarg;
                     break;
            //dest file
            case 'o':printf("Output %s\n",optarg);
                    res_options->dest_file = optarg;
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

int main(int argc,char **argv){
    options_tst options_st= {"",""};
    parse_options(argc,argv,&options_st);
    printf("src file :%s\n",options_st.src_file);
    printf("dest file :%s\n",options_st.dest_file);
    return 0;
}


