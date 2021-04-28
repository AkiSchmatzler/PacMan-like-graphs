#ifndef __GRAPHE_H
#define __GRAPHE_H


/**
 * \file graphe.h
 * \brief header for all the functions for list of path structure and node structure 
 * This file specifies functions to manipulate both data structures
 * \author Aki Schmatzler
 * \version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

/**
 * \struct s_coord
 * \brief list for treasures in a graph
 * weight represents the distance of a given node to that treasure
 */
typedef struct s_weightTreasure {
	int weight;
	float treasure;
	struct s_weightTreasure *next;
}*weightTreasure;

/**
 * \struct s_listeArc
 * \brief  list structure to handle paths between two nodes in some functions
 * contains two pointer on a s_node structure
 * and a pointer on the next element of the list
 */
typedef struct s_listeArc {
	noeud n1;
	noeud n2;
	struct s_listeArc *next;
} *listeArc;


/**
 * \struct s_listeNoeuds
 * \brief  list structure for my implementation of a variant of the Dijkstra algorithm
 * contains one pointer on a s_node structure
 * the value to get to that node, meaning the distance to that node
 * and a pointer on the next element of the list
 */
typedef struct s_listeNoeuds {
	noeud n;
	int poids;
	struct s_listeNoeuds *next;
} *listeNoeuds;

/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////	OPERATION ON s_listeArcs STRUCTURE //////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * \brief creates a new liste of paths
 * \return a pointer on the new list (which is NULL)
 */
listeArc nvListeArc ();

/**
 * \brief adds a path to a list of paths
 * the new path is added at the beginning of the list
 * \param l a pointer on a list ofPaths
 * \param n1 a node
 * \param n2 another node
 * \return a pointer on the new list
 */
listeArc ajtlisteArc (listeArc l, noeud n1, noeud n2);

/**
 * \brief check if a path exists in a given list of paths
 * checks both ways (if l->n1 == n1 and l->n2 == n2 or the other way)
 * both of these cases return true
 * recursive functuion
 * \param l a pointer on a list of paths
 * \param n1 a node
 * \param n2 another node
 * \return if the node exists true, if not then false
 */
bool existeArc (listeArc l, noeud n1, noeud n2);


/**
 * \brief frees the memory allocated to a list of paths
 * \param l a list of paths
 */
void destroylisteArc (listeArc l);


/**
 * \brief counts the number of elements in a list of paths
 * recursive functions
 * \param l a list of paths
 * \return the length of the list
 */
int longueur_liste (listeArc l);



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
listeArc longueurRec (noeud n, listeArc arcParcourues);


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