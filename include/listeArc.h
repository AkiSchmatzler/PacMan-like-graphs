#ifndef __LISTEARC_H
#define __LISTEARC_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct s_listeArc {
	noeud n1;
	noeud n2;
	struct s_listeArc *next;
} *listeArc;


listeArc nvListeArc ();

listeArc ajtlisteArc (listeArc l, noeud n1, noeud n2);

bool existeArc (listeArc l, noeud n1, noeud n2);

void destroylisteArc (listeArc l);

#endif