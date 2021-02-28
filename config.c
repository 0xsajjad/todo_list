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
void init_config(struct config_file *config, char* path)
{
	config->path 			= path;
	config->config_exist 	= &file_exist;
	config->config_create 	= &create_file;
	config->config_read 	= &print_file;
}
