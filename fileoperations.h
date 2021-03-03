#ifndef FILEOPERATIONS_H_
#define FILEOPERATIONS_H_

#include <stdbool.h>

int  create_file (char* path);
bool file_exist(char* path);
int print_file (char* path);
int get_value (char* file_path, const char* search, char* output);

#endif /* FILEOPERATIONS_H_ */
