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
    int (*config_create) (char*);
    void (*config_read) (char*);
};

void init_config(struct config_file *, char *);

#endif /* CONFIG_H_ */
