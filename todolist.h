#ifndef TODOLIST_H
#define TODOLIST_H

#include "types.h"

#define TODO_PATH_IDENTIFIER "TODO_LIST_PATH="

char* get_todo_list_path (char*);

STATUS show_tasks (char* path);

#endif
