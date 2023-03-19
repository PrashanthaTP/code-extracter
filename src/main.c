#include <stdio.h>
#include <stdlib.h> // exit

#include "utils/cmdline.h"
#include "utils/containers.h"
#include "utils/logger.h"
#include "utils/re.h"

void parse_options(int argc, char **argv, options_tst *options_st);

const char *identifier_code_block_start = "```";

void print_options(options_tst options_st) {
  printf("src file  :%s\n", options_st.src_file);
  printf("dest file :%s\n", options_st.dest_file);
}

// https://linux.die.net/man/3/getline
// TODO : Track dynamically allocated variables
// Read line by line :
// https://stackoverflow.com/questions/3501338/c-read-file-line-by-line
// Functions in pointers :
// https://stackoverflow.com/questions/4222661/functions-in-structure

void scan_file(char *file_path) {
  printf("Reading file %s...\n", file_path);

  FILE *file; // FREE THIS
  if (!(file = fopen(file_path, "r"))) {
    error("[ce] \"%s\" couldn't be read.", file_path);
    exit(EXIT_FAILURE);
  }

  // unsigned int n_line = 0;
  const size_t MAX_CHARS = 150;
  const char *match_code_block = "```";
  // char* line = NULL;
  char *line = (char *)malloc(sizeof(char) * MAX_CHARS); // FREE THIS
  size_t c_line = MAX_CHARS;
  size_t n_read_char; // gets number of characters read;

  stack_t *stack = make_stack();
  while ((n_read_char = getline(&line, &c_line, file)) != -1) {
    if (match(line, match_code_block) != 0) {
      if (stack->len > 0) {
        pop(stack);
      };
    }
  }
  free(line);
  fclose(file);
  free(stack);
}

void extract_code(char *in_file_path, char *out_file_path) {
  printf("Reading file %s...\n", in_file_path);

  FILE *in_file = NULL;  // FREE THIS
  FILE *out_file = NULL; // FREE THIS

  if (!(in_file = fopen(in_file_path, "r"))) {
    error("[ce] \"%s\" couldn't be read.", in_file_path);
    exit(EXIT_FAILURE);
  }

  if (!(out_file = fopen(out_file_path, "w+"))) {
    error("[ce] \"%s\" couldn't be opened.", out_file_path);
    exit(EXIT_FAILURE);
  }

  // unsigned int n_line = 0;
  const size_t MAX_CHARS = 150;
  const char *match_code_block = "```";
  // char* line = NULL;
  char *line = (char *)malloc(sizeof(char) * MAX_CHARS); // FREE THIS
  size_t c_line = MAX_CHARS;
  size_t n_read_char; // gets number of characters read;

  stack_t *stack = make_stack(); // FREE THIS
  char add_newline = 0;          //
  while ((n_read_char = getline(&line, &c_line, in_file)) != -1) {
    // printf("Stack len %d\n",stack->len);
    if (match(line, match_code_block) != 0) {
      // not matched
      if (stack->len > 0) {
        // already inside code block
        printf("Writing %s\n", line);
        fprintf(out_file, line);
      };
      continue;
    } else {
      // matched
      if (stack->len > 0) {
        // end of code block
        pop(stack);
        continue;
      }
      // code block start
      push(stack);
      if (!add_newline) {
        //atlease 1 code block found
        //so the output file will have some content
        //and new line to be written at the end
        add_newline = 1;
      }
    }
  }
  if (add_newline) {
    fprintf(out_file, "\n");
  }

  free(line);
  fclose(in_file);
  fclose(out_file);
  free(stack);
}
int main(int argc, char **argv) {
  options_tst options_st = {"", ""};
  parse_options(argc, argv, &options_st);
  print_options(options_st);
  extract_code(options_st.src_file, options_st.dest_file);
  return 0;
}
