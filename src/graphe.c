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
		//checking if the path exists in any of the direction
		if((l->n1 == n1 && l->n2 == n2) || (l->n1 == n2 && l->n2 == n1)) return true;
		//recursive call
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


noeud nouvnoeud () {
	noeud res = (noeud) malloc (sizeof (struct s_noeud));
	for (int i = 0; i<NDIR; i++) {
		//initialize all neighbors to NULL, distance to 0 and aray of treasures to NULL
		res->distances[i] = 0;
		res->voisins[i] = NULL;
		res->tresors[i] = NULL;
	}
	return res;
}

void destroynoeud (noeud n) {
	for (int i = 0; i<NDIR; i++) {
		//if theres a neighbor in that direction
		if (n->voisins[i] != NULL) {
			free (n->tresors[i]);
			//we let him know that we're gonna die
			//so he can wipe our existence away
			n->voisins[i]->voisins[(i+2)%4] = NULL;
			n->voisins[i]->distances[(i+2)%4] = 0;
			free (n->voisins[i]->tresors[(i+2)%4]);
		}
	}
	free (n);
}


void passage (noeud n1, noeud n2, Dir d, int dist, float tr[]) {
	n1->voisins[d] = n2;
	//opposite direction of d is (d+2)%4
	n2->voisins[(d+2)%4] = n1;
	n1->distances[d] = dist;
	n2->distances[(d+2)%4] = dist;
	//malloc for the arrays of treasures
	n1->tresors [d] = 		(float *) malloc (dist * sizeof(float));
	if (n1->tresors[d] == NULL) abort ();
	n2->tresors[(d+2)%4] =  (float *) malloc (dist * sizeof(float));
	if (n2->tresors [(d+2)%4] == NULL) abort ();
	//filling the array of treasures
	for (int i = 0; i<dist; i++) {
		//in one way
		n1->tresors[d][i] = tr[i];
		//and the opposite
		n2->tresors [(d+2)%4][i] = tr[dist-i-1];
	}
}


listeArc tailleRec (noeud n, listeArc arcParcourues, coord co) {
	//for each direction
    for (Dir i = 0; i<NDIR; i++) {
		int tmpX = co->xTmp;
		int tmpY = co->yTmp;
		//if there is a neigbor in that direction and we haven't checked that path yet
        if (n->distances[i] != 0 && !existeArc (arcParcourues, n, n->voisins[i])) {
				//we add the path to our list of paths
                arcParcourues = ajtlisteArc (arcParcourues, n, n->voisins[i]);

			switch (i) {
				//measuring from top to bottom and from left to right
				case NORD :
					//if in direction north, we substract to y
					co->yTmp -= n->distances[i];
					//if we're more to the north than we've ever been we get that data in xMin
					if (co->yTmp < co->yMin) co->yMin = co->yTmp;
					break;
				case EST : 
					//if in direction east we add to x
					co->xTmp += n->distances[i];
					//if we're more to the east than we've ever been we get that data in xMax
					if (co->xTmp > co->xMax) co->xMax = co->xTmp;
					break;
				case SUD : 
					//if in direction south we add to y
					co->yTmp += n->distances[i];
					//if we're more to the south than we've ever been we get that data in yMax
					if (co->yTmp > co->yMax) co->yMax = co->yTmp;
					break;
				case OUEST : 
					//if in direction west we substract to x
					co->xTmp -= n->distances[i];
					//if we're more to the west than we've ever been we get that data in xMin
					if (co->xTmp < co->xMin) co->xMin = co->xTmp;
					break;
			} 
			//recursive call
			arcParcourues = tailleRec (n->voisins[i], arcParcourues, co);
			co->xTmp = tmpX;
			co->yTmp = tmpY;
		}
	}
	return arcParcourues;
}

void taille (noeud n, int *X, int *Y) {
	if (n == NULL) return;
	struct s_coord coord = {0};
	//list for the paths for our recursive function
	listeArc arcParcourues = nvListeArc();

	arcParcourues = tailleRec (n, arcParcourues, &coord);

	destroylisteArc (arcParcourues);

	//the total length of the y and z axis
	*Y = abs(coord.yMin) + abs(coord.yMax);
	*X = abs(coord.xMin) + abs(coord.xMax);
	return;
}


void position (noeud n, int *X, int *Y) {
	if (n == NULL) return;

	struct s_coord coord = {0};

	listeArc arcParcourues = nvListeArc();
  
	arcParcourues = tailleRec (n, arcParcourues, &coord);	

	destroylisteArc (arcParcourues);

	//X position is the absolute value of the farthest we've been to the west
	*X = abs(coord.xMin);
	//Y position is the absolute value of the farthest we've been to the north
	*Y = abs(coord.yMin);
	
	return;	
}

listeArc longueurRec (noeud n, listeArc arcParcourues) {
	for (int i = 0; i<4; i++) {
		//if there is a neighbor and we haven't checked that path yet
		if (n->voisins[i] != NULL && !existeArc (arcParcourues, n, n->voisins[i])){
			//we add the path to the list of paths structure
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
		//we look for the directions in which the neighbor is
		while (tmp->n1->voisins[j] != tmp->n2) {
			j++;
		}
		//and we add to res the distance of the neighbor
		res += tmp->n1->distances[j];
		tmp = tmp->next;
	}

	destroylisteArc (arcParcourues);

	return res;	
}



float sum_float_array (float *ar, int beginning, int end) {
	float res = 0;
	for (int i = beginning; i<end; i++) {
		res += ar[i];
	}
	return res;
}

float valeurTotalTresors (noeud n) {
	float res = 0;
	listeArc arcParcourues = nvListeArc ();
	arcParcourues = longueurRec (n, arcParcourues);
	listeArc tmp = arcParcourues;
	//list of pointer on s_noeud structure we've already visited
	//to deal with the case of a treasure being on a node 
	//we don't wanna count it multiple times !
	listeArc noeudsVisites = nvListeArc();

	//for each path bewteen two nodes in the graph
	for (int i = 0; i<longueur_liste (arcParcourues); i++) {
		int j = 0;
		//we find in which direction the neighbor is
		while (tmp->n1->voisins[j] != tmp->n2) {
			j++;
		}
		//if we never checked both of the nodes
		if (!existeArc (noeudsVisites, tmp->n1, NULL) && !existeArc (noeudsVisites, tmp->n2, NULL)) {
			noeudsVisites = ajtlisteArc (noeudsVisites, tmp->n1, NULL);
			noeudsVisites = ajtlisteArc (noeudsVisites, tmp->n2, NULL);
			//we add to res the whole array
			res += sum_float_array (tmp->n1->tresors[j], 0, tmp->n1->distances[j]);
		}
		//if we checked only node 2
		else if (!existeArc (noeudsVisites, tmp->n1, NULL) && existeArc (noeudsVisites, tmp->n2, NULL)) {
			noeudsVisites = ajtlisteArc (noeudsVisites, tmp->n1, NULL);
			//we add to res the whole array minus the tresor at the second node
			res += sum_float_array (tmp->n1->tresors[j], 0, tmp->n1->distances[j] - 1);
		} 	
		//if we checked only node 1
		else if (existeArc (noeudsVisites, tmp->n1, NULL) && !existeArc (noeudsVisites, tmp->n2, NULL)) {
			noeudsVisites = ajtlisteArc (noeudsVisites, tmp->n2, NULL);
			//we add to res the whole array minus the tresor at the first node
			res += sum_float_array (tmp->n1->tresors[j], 1, tmp->n1->distances[j]);
		} 
		//if we checked both nodes alreadt
		else if (existeArc (noeudsVisites, tmp->n1, NULL) && existeArc (noeudsVisites, tmp->n2, NULL)) {
			//we add to res the whole array minus the tresors at both nodes
			res += sum_float_array (tmp->n1->tresors[j], 1, tmp->n1->distances[j] - 1);
		} 	
	
		tmp = tmp->next;
	}

	destroylisteArc (noeudsVisites);
	destroylisteArc (arcParcourues);
	return res;
}



