/*
 * config.h
 *
 *  Created on: Feb 23, 2021
 *      Author: sajjad
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdbool.h>

#include "types.h"

#define CFG_FILE "/var/sajjad/todo.cfg"

struct config_file
{
	char* path;

    bool (*config_exist) (char*);
    STATUS (*config_create) (char*);
    void (*config_read) (char*);
};

struct config_file* init_config(char *);
void close_config(struct config_file* config_file);

#endif /* CONFIG_H_ */
