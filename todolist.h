#ifndef TODOLIST_H
#define TODOLIST_H

#define TODO_PATH_IDENTIFIER "TODO_LIST_PATH="

int create_todo_file();
int show_tasks (char* path);
int get_todo_file_path (char* config_path, char* todo_path);

#endif
