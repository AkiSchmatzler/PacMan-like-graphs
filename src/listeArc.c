#include "graphe.h"

listeArc nvListeArc () {
	return NULL;
}

listeArc ajtlisteArc (listeArc l, noeud n1, noeud n2) {
	listeArc res = (listeArc) malloc (sizeof (struct s_listeArc));
	res->n1 = n1;
	res->n2 = n2;
	res->next = l;
	return res;
}

bool existeArc (listeArc l, noeud n1, noeud n2) {
	if (l != NULL) {
		if((l->n1 == n1 && l->n2 == n2) || (l->n1 == n2 && l->n2 == n1)) return true;
		return existeArc (l->next, n1, n2);
	}
	return false;
}

int longueur_liste (listeArc l) {
	if (l == NULL) return 0;
	else return 1 + longueur_liste(l->next);
}

void destroylisteArc (listeArc l) {
	if (l == NULL) return;
	destroylisteArc (l->next);
	free(l);
	return;
}
