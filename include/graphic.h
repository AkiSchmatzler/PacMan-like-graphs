#ifndef __GRAPHIC_H
#define __GRAPHIC_H

/**
 * \file graphic.h
 * \brief header for functions to manipulate bidimensional arrays of the graph and make a .pgm image out of it
 * \author Aki Schmatzler
 * \version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "graphe.h"


#define N 3					///< numbers of pixels that represents a meter
#define M 1					///< number of pixels for the width of a path
#define ARC_VERTICAL 1		///< flag for vertical paths
#define ARC_HORIZONTAL 2	///< flag for horizontal paths
#define NOEUD 3				///< flag for nodes

/**
 * \typedef byte, to not use to much memory for the big arrays
 */
typedef unsigned char byte;


/**
 * \brief create a 2D array representation of a graph
 * vertical paths are marked with a 1,
 * horizontal paths are parked with a 2,
 * nodes are marked with a 3
 * the rest is zeros
 * \param x_size the horizontal lentgh of the graph
 * \param y_size the vertical height of the graph
 * \param node a pointer on node data structure s_node
 * \returns a 2 array of bytes that represent the graph
 */
byte** create_int_array (int x_size, int y_size, noeud node);

/**
 * \brief takes the 2D array of the graph and maps it out to the dimension N*x_size, N*y_size
 * it's used to then after be written in a .pgm file
 * is called by write_to_file function
 * \param pgm_int_array the 2 array that represents the graph
 * \param x_size the x_size of the pgm_int_array parameter
 * \param y_size the y_size of the pgm_int_array parameter
 * \returns the resized array, ready to be written in a .pgm file
 */
byte ** adapt_size (byte** pgm_int_array, int x_size, int y_size);


/**
 * \brief creates a .pgm image file in image/ directory
 * \param pgm_int_array the 2 array that represents the graph
 * \param x_size the x_size of the pgm_int_array parameter
 * \param y_size the y_size of the pgm_int_array parameter
 */
void write_to_file (byte ** pgm_int_array, int x_size, int y_size);

#endif