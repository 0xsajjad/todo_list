#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileoperations.h"
#include "config.h"
#include "todolist.h"

/*
 * Description:
 * 			A utility that creates list of tasks
 *
 * Implementation:
 * 			There must be a configuration file that stores the state of the program
 * 			Configuration file:
 * 				- There is default configuration file path in the program that ~/todo.cfg
 * 				- This config file contains path of to do list, we could have more than one to do list files but one for now
 *
 * Input:
 * 			argc -> number of arguments
 * 			argv -> pointer to string for each argument
 */
int main(int argc, char **argv) {

	char* path;
	struct config_file *config;

	config = init_config(CFG_FILE);

	if (!config)
		return 1;

	if (! config->config_exist(config->path))
	{
		config->config_create(config->path);
	}

	path = get_todo_list_path(config->path);

	show_tasks(path);

	free(path);
	close_config(config);

	return 0;
}
