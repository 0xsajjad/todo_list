#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "fileoperations.h"
#include "config.h"
#include "todolist.h"
#include "shell.h"

/*
 * Program Description:
 * 			A utility that creates list of tasks
 *
 * Implementation:
 * 			There must be a configuration file that stores the state of the application/program
 * 			Configuration file:
 * 				- The default configuration file path is ~/todo.cfg
 * 				- This config file contains path of to do list, we could have more than one to do list files but one for now
 */

const int max_str_len = 100;
struct config_file config;

int main(int argc, char **argv) {
	int ret;

	init_config(&config, CFG_FILE);

	if (! config.config_exist(CFG_FILE))
		if(! config.config_create(CFG_FILE))
		{
			fprintf(stderr, "Unable to create configuration file\n");
			return -EBADF;
		}

	ret = init_todo_list();

    if (ret)
    {
    	fprintf(stderr, "Unable to initialize todo list\n");
        return ret;
    }

	ret = shell();
	return ret;
}
