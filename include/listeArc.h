#ifndef __LISTEARC_H
#define __LISTEARC_H


/**
 * \file listeArc.h
 * \brief header for all the functions for list of vertices of the graph
 * This file specifies functions to manipulate this data structure
 * \author Aki Schmatzler
 * \version 1.0
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "graphe.h"


typedef struct s_noeud* noeud;

/**
 * \struct s_listeArc
 * \brief  list structure to handle vertices between two nodes in some functions
 * contains two pointer on a s_node structure
 * and a pointer on the next element of the list
 */
typedef struct s_listeArc {
	noeud n1;
	noeud n2;
	struct s_listeArc *next;
} *listeArc;



/////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////	OPERATION ON s_listeArcs STRUCTURE //////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////


/**
 * \brief creates a new liste of vertices
 * \return a pointer on the new list (which is NULL)
 */
listeArc nvListeArc ();

/**
 * \brief adds a path to a list of vertices
 * the new path is added at the beginning of the list
 * \param l a pointer on a list ofPaths
 * \param n1 a node
 * \param n2 another node
 * \return a pointer on the new list
 */
listeArc ajtlisteArc (listeArc l, noeud n1, noeud n2);

/**
 * \brief check if a path exists in a given list of vertices
 * checks both ways (if l->n1 == n1 and l->n2 == n2 or the other way)
 * both of these cases return true
 * recursive functuion
 * \param l a pointer on a list of vertices
 * \param n1 a node
 * \param n2 another node
 * \return if the node exists true, if not then false
 */
bool existeArc (listeArc l, noeud n1, noeud n2);


/**
 * \brief frees the memory allocated to a list of vertices
 * \param l a list of vertices
 */
void destroylisteArc (listeArc l);


/**
 * \brief counts the number of elements in a list of vertices
 * recursive functions
 * \param l a list of vertices
 * \return the length of the list
 */
int longueur_liste (listeArc l);



#endif