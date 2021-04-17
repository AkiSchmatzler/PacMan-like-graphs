#ifndef __GRAPHIC_H
#define __GRAPHIC_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "graphe.h"

#define N 6
#define M 2

char* itostr(int i);

int** create_int_array (int x_size, int y_size, noeud node);

void write_to_file (int ** pgm_int_array, int x_size, int y_size);

char* init_pgm (int x_size, int y_size);

int create_black_image (int x_size, int y_size, char* pathname);

#endif