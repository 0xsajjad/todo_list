#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "config.h"
#include "todolist.h"

/* Shell operations:
 * 	- get command
 * 	- execute command
 * 	- show help message
 */

static int add_task();
static int show_task();
static int help_msg();
static void get_command();
static int execute_command(char* str);

const int max_cmd_len = 15;

extern struct config_file config;
extern const int max_str_len;

struct cmd {
	const char* cmd;
	int (*call)(void);
};

static struct cmd cmds[] =
{
		{ .cmd = "add_task", .call = &add_task},
		{ .cmd = "show_task", .call = &show_task},
		{ .cmd = "search_task", .call = NULL},
		{ .cmd = "edit_task", .call = NULL},
		{ .cmd = "help", .call = &help_msg},
		{ .cmd = "quit", .call = NULL}
};

static int total_cmds = sizeof(cmds)/sizeof(cmds[0]);

/*
 * shell : shell function
 *
 * exits what execute_command returns
 */
int shell(void)
{
	char* cmd = malloc(max_cmd_len);
	int ret = 0;

	help_msg();

	do
	{
		get_command(cmd);
		ret = execute_command(cmd);
	} while(strcmp(cmd, "quit\n"));

	free(cmd);
	return ret;
}

/*
 * get_command : get a valid command
 * @cmd: command string
 */
static void get_command(char* cmd)
{
	int count;

	do
	{
		count = 0;

		printf("$ ");
		getline(&cmd, (size_t*)&max_cmd_len, stdin);

		do
		{
			if (!strncmp(cmd, cmds[count].cmd, strlen(cmds[count].cmd)))
				return;

			count ++;
		} while (count < total_cmds);

		printf("command not found, use \"help\"\n");

	} while(1);
}

/*
 * execute : get command string, check from register commands
 * 			 once match found, invoke its call function if not NULL
 *
 * @cmd: command string
 *
 * returns the value return by command, or NULL if there is not call function
 */
static int execute_command(char* cmd)
{
	int count = 0;
	int ret = 0;

	do
	{
		if (! strncmp(cmd, cmds[count].cmd, strlen(cmds[count].cmd)))
		{
			if (cmds[count].call != NULL)
			{
				ret = cmds[count].call();
				return ret;
			}

			else
				break;
		}

		count ++;

	} while(count < total_cmds);

	return ret;
}

/*
 * help_msg : Show available commands
 */
static int help_msg()
{
	printf("available commands: \n");

	for (int count = 0; count < total_cmds; count++)
	{
		printf("%s\t", cmds[count].cmd);
	}

	printf("\n");
	return 0;
}

/*
 * add_task : add task wrapper, call the add task function
 */
static int add_task()
{
	// add task to new the to do list
	// get to do list pointer
	return 0;
}

/*
 * show_task : show task from the to do list
 * 			   which to do list?
 */
static int show_task()
{
	int ret = 0;
	char* todo_path = malloc(max_str_len);

	ret = get_todo_file_path(config.path, todo_path);

	if (!ret)
		ret = show_tasks(todo_path);
	else
		if (ret == EOF)
			fprintf(stdout, "No to do list available\n");

	free(todo_path);

	return ret;
}
