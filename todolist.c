#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <error.h>
#include <errno.h>
#include <err.h>

#include "todolist.h"
#include "config.h"
#include "fileoperations.h"

/*
 * implement to handle following to do list operations:
 *
 * read complete to do list
 * show tasks from to do list
 * remove task from to do list
 *
 * create task groups
 * search from tasks
 *
 */

extern const int max_str_len;
extern struct config_file config;

//static const char* tasks_start = "#TASKS_START";
static const char* tasks_end = "#TASKS_END\n";

static char* get_task(FILE *fptr, char* string);
//static int memorize_task(char* str);
//static int init_task_list();
//static inline int add_task_node();

enum task_status {open, resolved, inprogress};

//static struct task_list *task_list = NULL;
//static struct task_list *task_list_head = NULL;

struct task{
	char *task; 				// task string
	enum task_status status;    // task's status (open, resolved, in-progress)
	struct task *next;
};

#define MAX_PATH_LEN 30
struct todo_list {
	struct task task;
	char path[MAX_PATH_LEN];
};

struct todo_list todo_list;

/*
 * init_todo_list : all operations will be done on -> struct todo_list todo_list
 *                  we need to fetch all the tasks from the file and load it to todo_list
 */
int init_todo_list()
{
	int ret = 0;
	char input;

	ret = get_todo_file_path(config.path, todo_list.path);

	if (ret)
	{
		printf("Can't find any todo list\n");
		printf("Want to create a new todo list? [Y/N] ");
		scanf("%c", &input);

        if (input == 'y' || input == 'Y')
        {
			ret = create_todo_file();
        }
    }

	return ret;
}

/*
 * get_todo_list_path : get the path of to do file
 *
 * @path : configuration file path
 *
 * Output : char * string -> path
 * 			NULL -> fail
 */

int get_todo_file_path (char* config_path, char* todo_path)
{
	int ret;

	ret = get_value(config_path, TODO_PATH_IDENTIFIER, todo_path);

	return ret;
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
	// tasks starts with "-"
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
 *
 * return 0 on success
 */
int show_tasks (char* path)
{
	int ret = 0;
	FILE *fptr;
	char *string;

	string = malloc(max_str_len);
	if (!string)
		return -ENOMEM;

	if ((fptr = fopen(path, "r")))
	{
		while(1)
		{
			get_task(fptr, string);
			if (string == NULL || !(strcmp(string, tasks_end)))
			{
				break;
			}

			fprintf(stdout, "%s\n", string);
		}
	}

	else
		ret = -EPERM;

	free(string);
	fclose(fptr);

	return ret;
}

/*
 * init_task : initialize the task structure
 */
//static int init_task_list()
//{
//	task_list_head = malloc(sizeof(struct task_list));
//	if (task_list_head)
//		task_list = task_list_head;
//	else
//		return -ENOMEM;
//
//	return 0;
//}

/*
 * add_task_node : add a new node to the task_lisk
 */
//static inline int add_task_node()
//{
//	task_list->next = malloc(sizeof(struct task_list));
//
//	if (task_list->next)
//	{
//		task_list = task_list->next;
//		task_list->next = NULL;
//	}
//	else
//		return -ENOMEM;
//
//	return 0;
//}

/*
 * add_to_list : given the task string, add it to the list struct
 * 				 this will allow us to handle individual tasks
 */
//static int memorize_task(char* str)
//{
//	if (!task_list_head)
//		init_task_list();
//	else
//		add_task_node();
//
//	task_list->task = malloc(max_str_len);
//
//	if (!task_list->task)
//		return -ENOMEM;
//
//	strcpy(task_list->task, str);
//
//	return 0;
//}
//

/*
 * create_todo_list : Get path from stdin and create a new file there
 */
int create_todo_file()
{
	int ret = 0;
	char* path = malloc(max_str_len);
    char* real_path = malloc(max_str_len);

	if(!path)
		return -ENOMEM;

	printf("Enter path: ");
	scanf("%s", path);

	if (file_exist(path))
		fprintf(stderr, "File already exist\n");
	else
	{
		ret = create_file(path);
		if (!ret)
		{
            real_path = realpath(path, NULL);
            printf("realpath: %s\n", real_path);
            strcpy(todo_list.path, real_path);
			// TODO: update to do path in configuration and todo_list structure
		}
		else
			fprintf(stderr, "%s", strerror(ret));
	}

	free(path);
	return ret;
}
