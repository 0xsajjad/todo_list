#ifndef FILEOPERATIONS_H_
#define FILEOPERATIONS_H_

#include <stdbool.h>

#include "types.h"

STATUS create_file (char*);
bool file_exist(char* path);
void print_file (char* path);

// Get value for a variable from a file
char* get_value (char* path, const char* variable);

#endif /* FILEOPERATIONS_H_ */
