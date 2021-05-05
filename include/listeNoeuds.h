#ifndef __LISTENOEUDS_H
#define __LISTENOEUDS_H

/**
 * \file listeNoeuds.h
 * \brief header for function on list of weighted node structure
 * These functions are useful for the two last functions of the assignement, especially for dijkstra remix
 * \author Aki Schmatzler
 * \version 1.0
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "listeArc.h"



typedef struct s_noeud* noeud;
typedef struct s_listeArc* listeArc;


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


/**
 * \brief creates a new list of nodes
 * \return a pointer on list of nodes structure
 */
listeNoeuds nouvlisteNoeuds ();

/**
 * \brief frees the memory allocated to a list of nodes
 * \param l a list of nodes
 */
void destroylisteNoeud (listeNoeuds ln);

/**
 * \brief adds a new node to a list of nodes
 * and initialise it's weight to -1 (which corresponds to infinity 
 * in our implementation of the dijkstra algorithm)
 * \param l a list of nodes
 * \param n the new node that is getting added
 * \return a pointer on the new list of nodes
 */
listeNoeuds addNoeud (listeNoeuds ln, noeud n);

/**
 * \brief calculates the length of a list of nodes
 * \param ln a list of nodes
 * \return an integer, length of the list
 */
int longueurNoeud (listeNoeuds ln);

/**
 * \brief removes a node from the list
 * \param l a list of nodes
 * \param n a node that is to be removed
 * \return the list without the node
 */
listeNoeuds removeNoeud (listeNoeuds l, noeud n);

/**
 * \brief checks if a node exists in a list of nodes
 * \param l a list of nodes
 * \param n a node
 * \return true if the node exists in the list, false if not
 */
bool existeNoeud (listeNoeuds l, noeud n);

/**
 * \brief gets the weight of a node in a list of nodes
 * returns -1 if the nodes doesn't exist in the list
 * \param ln a list of nodes
 * \param n a node
 * \return an integer the value of the weight
 */
int valueWeight (listeNoeuds ln, noeud n);

/**
 * \brief changes the value of the weight for a specific node in the list
 * \param ln a list of nodes
 * \param n a node
 * \param newWeight the new weight that is to be assigned
 * \return the list of nodes
 */
listeNoeuds changeValueWeight (listeNoeuds ln, noeud n, int newWeight);

/**
 * \brief finds the node that has the smallest positive weight in the list
 * returns NULL if there are only nodes that have a weight of -1
 * \param ln a list of nodes
 * \return the node that has the minimum positive weight
 */
noeud nodeMinimumWeight (listeNoeuds ln);

#endif
