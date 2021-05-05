#include "listeNoeuds.h"

/**
 * \file listeNoeuds.c
 * \brief definition of functions on list of weighted node structure
 * These functions are useful for the two last functions of the assignement, especially for dijkstra remix
 * \author Aki Schmatzler
 * \version 1.0
 */



listeNoeuds nouvlisteNoeuds () {
	return NULL;
}

void destroylisteNoeud (listeNoeuds ln) {
	if (ln == NULL) return;
	destroylisteNoeud (ln->next);
	free(ln);
	return;
}

listeNoeuds addNoeud (listeNoeuds ln, noeud n) {
	listeNoeuds res = (listeNoeuds) malloc (sizeof (struct s_listeNoeuds));
	if (res == NULL) abort ();
	res->n = n;
	//initialise weight to -1
	res->poids = -1;
	res->next = ln;
	return res;
}

int longueurNoeud (listeNoeuds ln) {
	if (ln == NULL) return 0;
	return 1 + longueurNoeud (ln->next);
}

listeNoeuds removeNoeud (listeNoeuds l, noeud n) {
	if (l == NULL) return NULL;
	if (l->n == n) {
		listeNoeuds l1 = l->next;
		free (l);
		return l1;
	}
	else {
		listeNoeuds tmp = l;

		while (tmp->next->n != n)
			tmp = tmp->next;
		
		listeNoeuds tmp2 = tmp->next;
		tmp->next = tmp->next->next;
		free (tmp2);
		return l;
	}
}

bool existeNoeud (listeNoeuds l, noeud n) {
	if (l != NULL) {
		if (l->n == n) return true;
		else return existeNoeud (l->next, n);
	}
	return false;
}


int valueWeight (listeNoeuds ln, noeud n) {
	if (ln != NULL) {
		if (ln->n == n) return ln->poids;
		else return valueWeight (ln->next, n);
	}
	return -1;
}

listeNoeuds changeValueWeight (listeNoeuds ln, noeud n, int newWeight) {
	listeNoeuds tmp = ln;
	for (int i = 0; i<longueurNoeud(ln); i++) {
		if (tmp->n == n) {
			tmp->poids = newWeight;
			return ln;
		}
		tmp = tmp->next;
	}
	return ln;
}

noeud nodeMinimumWeight (listeNoeuds ln) {
	if (ln == NULL) return NULL;
	listeNoeuds tmp = ln;
	int min = __INT_MAX__;
	noeud res = NULL;
	for (int i = 0; i < longueurNoeud (ln); i++) {
		if (tmp->poids < min && tmp->poids > 0) {
			res = tmp->n;
			min = tmp->poids;
		}
		tmp = tmp->next;
	}
	return res;
}