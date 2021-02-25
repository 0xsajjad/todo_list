#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileoperations.h"

/*
 * create_file : Create file
 *
 * @path : path where to create file
 *
 * return : SUCCESS, FAIL
 */
STATUS create_file (char* path)
{
	FILE *fptr;

	if ((fptr = fopen(path, "w")))
	{
		fclose(fptr);
		return SUCCESS;
	}

	return  FAIL;
}

/*
 * file_exist: check if the file exists or not
 *
 * @path : path where to check file
 */

bool file_exist(char* path)
{
	FILE *fptr;

	if ((fptr = fopen(path, "r")))
	{
		fclose(fptr);
		return true;
	}

	return false;
}

/*
 * get_value : get value of variable from text file
 *
 * @path : path of the text file
 * @variable : variable who's value need to be searched
 */
char* get_value (char* path, const char* variable)
{
	FILE *fptr;
	const int max_str_len = 100;
	char *str, *temp;

	if (!(fptr = fopen(path, "r")))
		return NULL;

	str = malloc(max_str_len);
	temp = malloc(max_str_len);

	while (fgets(str, max_str_len, fptr) != NULL)
	{
		if (strcmp(str, variable) > 0)
		{
			strcpy(temp, &str[strlen(variable)]);
			break;
		}
	}

	bzero(str, strlen(str));
	strncpy(str, temp, strlen(temp) - 1);

	free(temp);
	fclose(fptr);

	return str;

}

/*
 * print_text_file : Read text file
 *
 * @path : path to file which need to be print
 *
 */
void print_file (char* path)
{
	char c;
	FILE *fptr;

	if ((fptr = fopen(path, "r")))
	{
		while (!feof(fptr))
		{
			c = fgetc(fptr);
			fprintf(stdout, "%c", c);
		}
	}

	else
	{
		fprintf(stderr, "can't open file to read, path: %s\n", path);
		return;
	}

	fclose(fptr);
}
