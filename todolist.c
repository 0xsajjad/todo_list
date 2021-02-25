#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "todolist.h"
#include "fileoperations.h"

static const int max_str_len = 100;

static const char* tasks_end = "#TASKS_END\n";

/*
 * implement to handle to do list operations, as following
 *
 * read complete to do list
 * show tasks from to do list
 * remove task from to do list
 *
 * create task groups
 * search from tasks
 *
 */
static char* get_task(FILE *fptr, char* string);

enum task_status {open, resolved, inprogress};

static struct _task_list{
	char *task; 				// task string
	enum task_status status;    // task's status (open, resolved, in-progress)
	struct task_list *next;
} task_list;

/*
 * get_todo_list_path : get the path of to do file
 *
 * @path : configuration file path
 *
 * Output : char * string -> path
 * 			NULL -> fail
 */

char* get_todo_list_path (char* path)
{
	return get_value(path, TODO_PATH_IDENTIFIER);
}

/*
 * get_task : get the a task and move the pointer to the next
 *
 * @fptr : file pointer
 * @string : to return the task string
 *
 * returns NULL if the file cursor reach EOF
 */
static char* get_task(FILE *fptr, char* string)
{

	// task starts with "-"
	while ((fgets(string, max_str_len, fptr)) != NULL)
	{
		if (string[0] == '-' || !(strcmp(string, tasks_end)))
		{
			return string;
		}
	}

	return NULL;
}

/*
 * show_task : show all the tasks from the to do file
 *
 * @path : to do list path
 */
STATUS show_tasks (char* path)
{
	FILE *fptr;
	char *string;

	string = malloc(max_str_len);
	if (!string)
		return FAIL;

	if ((fptr = fopen(path, "r")))
	{
		while(1)
		{
			get_task(fptr, string);
			if (string == NULL || !(strcmp(string, tasks_end)))
			{
				break;
			}
			printf("%s\n", string);

		}
	}
	else
		return FAIL;

	free(string);
	fclose(fptr);

	return SUCCESS;
}

/*
 * add_to_list : add the task from list and add them to the link list
 */
static void add_to_list(char* str)
{

}
