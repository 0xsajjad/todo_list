/*
 * config.c
 *
 *  Created on: Feb 23, 2021
 *      Author: Sajjad
 *
 *  This file provides mechanism to hand configuration files
 */

#include <stdio.h>
#include <stdlib.h>

#include "config.h"
#include "fileoperations.h"

/*
 * init_config: Initialize a configuration file instance
 *              that instance will contain all the properties of a config file
 *              Properties of config file:
 *                  - path
 *                  - config_read()
 *                  - config_exist()
 *                  - config_create()
 *
 * @path : path where config file is located
 */
struct config_file * init_config(char* path)
{
	struct config_file *desc ;

	desc = malloc(sizeof(struct config_file));

	if (!desc)
		return NULL;

	desc->path 			= path;
	desc->config_exist 	= &file_exist;
	desc->config_create = &create_file;
	desc->config_read 	= &print_file;

	return desc;
}

/*
 * close_config : de-allocate all the resources for config_file structure
 *
 * @ desc : descriptor pointer
 */

void close_config(struct config_file* desc)
{
	if (desc)
		free(desc);
}
