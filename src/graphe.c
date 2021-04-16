#include "graphe.h"




noeud nouvnoeud () {
	return (noeud) malloc (sizeof (struct s_noeud));
}

void passage (noeud n1, noeud n2, Dir d, int dist) {
	n1->voisins[d] = n2;
	n2->voisins[(d+2)%4] = n1;
	n1->distances[d] = dist;
	n2->distances[(d+2)%4] = dist;
}


void tailleRec (noeud n, listeArc arcParcourues, coord co) {
    for (Dir i = 0; i<NDIR; i++) {
		int tmpX = co->xRel;
		int tmpY = co->yRel;
        if (n->distances[i] != 0 && !existeArc (arcParcourues, n, n->voisins[i])) {
                arcParcourues = ajtlisteArc (arcParcourues, n, n->voisins[i]);

			switch (i) {
				//on mesure du haut vers le bas et de la gauche vers la droite
				case NORD :
					co->yRel -= n->distances[i];
					if (co->yRel < co->yMin) co->yMin = co->yRel;
					break;
				case EST : 
					co->xRel += n->distances[i];
					if (co->xRel > co->xMax) co->xMax = co->xRel;
					break;
				case SUD : 
					co->yRel += n->distances[i];
					if (co->yRel > co->yMax) co->yMax = co->yRel;
					break;
				case OUEST : 
					co->xRel -= n->distances[i];
					if (co->xRel < co->xMin) co->xMin = co->xRel;
					break;
			} 
			tailleRec (n->voisins[i], arcParcourues, co);
			co->xRel = tmpX;
			co->yRel = tmpY;
		}
	}
}

void taille (noeud n, int *X, int *Y) {
	if (n == NULL) return;
	struct s_coord coord = {0};

	listeArc arcParcourues = nvListeArc();
  
	tailleRec (n, arcParcourues, &coord);	

	destroylisteArc (arcParcourues);

	*Y = abs(coord.yMin) + abs(coord.yMax);
	*X = abs(coord.xMin) + abs(coord.xMax);
	return;
}


void position (noeud n, int *X, int *Y) {
	if (n == NULL) return;
	struct s_coord coord = {0};

	listeArc arcParcourues = nvListeArc();
  
	tailleRec (n, arcParcourues, &coord);	

	destroylisteArc (arcParcourues);

	*X = abs(coord.xMin);
	*Y = abs(coord.yMin);
	
	return;	
}

listeArc longueurRec (noeud n, listeArc arcParcourues) {
	for (int i = 0; i<4; i++) {
		if (n->voisins[i] != NULL && !existeArc (arcParcourues, n, n->voisins[i])){
			arcParcourues = ajtlisteArc (arcParcourues, n, n->voisins[i]);
			arcParcourues = longueurRec(n->voisins[i], arcParcourues);
		}
	}
	return arcParcourues;
} 

int longueur (noeud n) {

	int res = 0;
	listeArc arcParcourues = nvListeArc();
	arcParcourues = longueurRec (n, arcParcourues);	
	listeArc tmp = arcParcourues;
	for (int i = 0; i<longueur_liste (arcParcourues); i++) {
		int j = 0;
		while (tmp->n1->voisins[j] != tmp->n2) {
			j++;
		}
		res += tmp->n1->distances[j];
		tmp = tmp->next;
	}

	destroylisteArc (arcParcourues);

	return res;	
}
