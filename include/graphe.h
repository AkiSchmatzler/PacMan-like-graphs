#ifndef __GRAPHE_H
#define __GRAPHE_H


/**
 * \file graphe.h
 * \brief header for all the functions for node structure and graphs
 * \author Aki Schmatzler
 * \version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "listeArc.h"
#include "listeNoeuds.h"

#define NDIR 4		///< Number of direction (north east south west)


/**
 * \struct enum 
 * \brief is used to pass on arguments of new type Dir and give the code some lisibility
 */
typedef enum {
	NORD=0, EST, SUD, OUEST } Dir;

/**
 * \struct s_noeud 
 * \brief structure for the nodes of the graph
 * each node contains a pointer on their 4 neighbors (== NULL means theres no neighbor in this direction)
 * each node contains the distance to each neighbor (==0 means no neighbor in this direction)
 * each node contains a pointer to an array of float that represent the treasures
 * "noeud" is used as a pointer on a s_noeud structure
 */
typedef struct s_noeud {
	struct s_noeud 	*voisins[NDIR];
	int 			distances[NDIR];
	float 			*tresors[NDIR];
} *noeud;

typedef struct s_listeArc* listeArc;
typedef struct s_listeNoeuds* listeNoeuds;

/**
 * \struct s_coord
 * \brief structure to handle coordinates in some functions
 */
typedef struct s_coord {
	int xTmp;
	int yTmp;
	int xMin;
	int xMax;
	int yMin;
	int yMax;
}*coord;





////////////////////////////////////////////////////////////////////////////////////////////////
////////////////	OPERATION ON s_noeud STRUCTURE //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * \brief creates a new node
 * \return a pointer on the memory that was allocated for the node
 */
noeud nouvnoeud ();


/**
 * \brief frees the memory allocated to a node
 * also frees all the memory of it's neighbor nodes concerning him (if they exist)
 * \param n a pointer on node structure s_noeud
 * \return a pointer on the memory that was allocated for the node
 */
void destroynoeud (noeud n);
/**
 * \brief creates a path beween two notes
 * by adding the nodes as neighbors in the good direction, giving them the right distance to each other and an array of floats to map out the value of the treasures on the path
 * \param n1 pointer on s_noeud stucture
 * \param n2 pointer on s_noeud structure
 * \param d the direction in which the path between n1 and n2 is
 * \param dist the distance between the two nodes
 * \param tr an array of floats that represents the value of the treasures laying on the path
 * \pre size of tr is equal to dist
 * \pre n1 and n2 are not NULL
 */
void passage (noeud n1, noeud n2, Dir d, int dist, float tr[]);


/**
 * \brief recursive function to figure out coordinates about a node
 * \param n a pointer on node structure s_noeud
 * \param arcParcourues a pointer on a list of arcs that represents the arcs that have already been visited
 * \param co a pointer on coord structure that evolves through the recursive calls
 * \return the list of paths in the graph
 */
listeArc tailleRec (noeud n, listeArc arcParcourues, coord co);


/**
 * \brief a function to give the total X and Y axis size of the graph 
 * calls the recursive function tailleRec and gets the data it needs in the co structure
 * \param n a pointer on node structure s_noeud
 * \param X a pointer on integer that is going to contain the horizontal size of the graph
 * \param Y a pointer on integer that is going to contain the vertical size of the graph
 */
void taille (noeud n, int *X, int *Y);

/**
 * \brief a function to the X and Y position of a node in the graph
 * calls the recursive function tailleRec and gets the data it needs in the co structure
 * the top left corner counts as position (0,0)
 * \param n a pointer on node structure s_noeud
 * \param X a pointer on integer that is going to contain the horizontal of the graph
 * \param Y a pointer on integer that is going to contain the Y vertical of the graph
 */
void position (noeud n, int *X, int *Y);

/**
 * \brief a recursive function that returns all the different paths between two nodes there are in the graph 
 * \param n a pointer on a node structure s_noeud
 * \param arcParcourues a pointer on list of path structure
 * \return a pointer on a list of all the different paths between two separate nodes in the graph
 */
listeArc allVertices (noeud n, listeArc arcParcourues);


/** 
 * \brief returns the cumulated length of all the distance between two separate nodes in the graph
 * \param n a pointer on node structure s_noeud
 * \return cumulated length of all the distance between two separate nodes in the graph
 */
int longueur (noeud n);

/**
 * \brief intermediate function to sum the floats of a float array
 * \param ar array of floats
 * \param size size of the array
 */
float sum_float_array (float *ar, int beginning, int end);


/**
 * \brief gets the total value of the treasures in the graph
 * calls longueurRec to get all the paths in the graph
 * calls sum_float array
 * \param n a pointer on node structure s_node
 * \returns the sum of the value of the treasures in the graph
 */
float valeurTotalTresors(noeud n);


/**
 * \brief finds the value of the closest treasure
 * \param n pointer on node structure s_noeud
 * \return the value of the closest treasure to the node
 */
float valeurPlusProcheTresors(noeud n);

#endif