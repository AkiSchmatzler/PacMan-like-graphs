#ifndef __GRAPHIC_H
#define __GRAPHIC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "check.h"

char* init_pgm (int x_size, int y_size);

void create_black_image (int x_size, int y_size, char* pathname);

#endif