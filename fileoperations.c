#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "fileoperations.h"

extern const int max_str_len;

/*
 * create_file : Create file
 *
 * @path : path where to create file
 * return 0 for success
 */
int create_file (char* path)
{
	FILE *fptr;

	fptr = fopen(path, "w");
	if (!fptr)
		return -EFAULT;

	fclose(fptr);
	return EXIT_SUCCESS;
}

/*
 * file_exist: check if the file exists or not
 *
 * @path : path where to check file
 */

bool file_exist(char* path)
{
	FILE *fptr;
    fptr = fopen(path, "r");
    if (!fptr)
		return -EFAULT;

    fclose(fptr);
	return true;
}

/*
 * get_value : get value of variable from text file
 *
 * @path : path of the text file
 * @variable : variable who's value need to be searched
 */
int get_value (char* file_path, const char* search, char* output)
{
	int ret = 0;
	FILE *fptr;
	char *str, *temp;

	fptr = fopen(file_path, "r");
	if (!fptr)
		return -EFAULT;

	str = malloc(max_str_len);
	temp = malloc(max_str_len);

	do
	{
		// if file cursor reach EOF without any match
		if (!(fgets(str, max_str_len, fptr)))
		{
			ret = EOF;
			break;
		}

		else if (strcmp(str, search) > 0)
		{
			strcpy(temp, &str[strlen(search)]);
			break;
		}
	}while (1);

	if (ret != EOF)
	{
		bzero(output, strlen(output));
		strncpy(output, temp, strlen(temp) - 1);
	}

	free(temp);
	free(str);
	fclose(fptr);

	return ret;
}

/*
 * print_text_file : Read text file
 *
 * @path : path to file which need to be print
 *
 */
int print_file (char* path)
{
	char c;
	FILE *fptr;

	fptr = fopen(path, "r");
	if (!fptr)
		return -EFAULT;

	while (!feof(fptr))
		{
			c = fgetc(fptr);
			fprintf(stdout, "%c", c);
		}

	fclose(fptr);
	return EXIT_SUCCESS;
}

/*
 * append_file : add new data at the end of the file
 *
 * @fptr : file pointer
 * @string : data to be added
 */
int append_file (char* file_path, char* string)
{
	int ret = 0;
	FILE* fptr;

	fptr = fopen(file_path, "a");
	if (!fptr)
		return -EFAULT;

	ret = fputs(string, fptr);
	if (ret == EOF)
		return EOF;

	return EXIT_SUCCESS;
}
