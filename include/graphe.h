#ifndef __GRAPHE_H
#define __GRAPHE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NDIR 4

typedef enum {
	NORD=0, EST, SUD, OUEST } Dir;


typedef struct s_noeud {
	struct s_noeud *voisins[NDIR];
	int distances[NDIR];
} *noeud;


typedef struct s_coord {
	int xRel;
	int yRel;
	int xMin;
	int xMax;
	int yMin;
	int yMax;
}*coord;

typedef struct s_listeArc {
	noeud n1;
	noeud n2;
	struct s_listeArc *next;
} *listeArc;



listeArc nvListeArc ();

listeArc ajtlisteArc (listeArc l, noeud n1, noeud n2);

bool existeArc (listeArc l, noeud n1, noeud n2);

void destroylisteArc (listeArc l);

int longueur_liste (listeArc l);


noeud nouvnoeud ();

void passage (noeud n1, noeud n2, Dir d, int dist);

void tailleRec (noeud n, listeArc arcParcourues, coord co);

void taille (noeud n, int *X, int *Y);

void position (noeud n, int *X, int *Y);

listeArc longueurRec (noeud n, listeArc arcParcourues);

int longueur (noeud n);

#endif