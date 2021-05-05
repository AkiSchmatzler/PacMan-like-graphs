#include "graphe.h"

/**
 * \file graphe.c
 * \brief definition from function on node structure and graph
 * This file specifies functions to manipulate graphs
 * \author Aki Schmatzler
 * \version 1.0
 */

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
	//list for the vertices of our graph for our recursive function
	listeArc arcParcourues = nvListeArc();

	arcParcourues = tailleRec (n, arcParcourues, &coord);

	destroylisteArc (arcParcourues);

	//the total length of the y and x axis
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

listeArc allVertices (noeud n, listeArc arcParcourues) {
	for (int i = 0; i<4; i++) {
		//if there is a neighbor and we haven't checked that path yet
		if (n->voisins[i] != NULL && !existeArc (arcParcourues, n, n->voisins[i])){
			//we add the path to the list of paths structure
			arcParcourues = ajtlisteArc (arcParcourues, n, n->voisins[i]);
			arcParcourues = allVertices(n->voisins[i], arcParcourues);
		}
	}
	return arcParcourues;
} 

int longueur (noeud n) {
	int res = 0;
	listeArc arcParcourues = nvListeArc();
	arcParcourues = allVertices (n, arcParcourues);	
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
	//free the list of paths
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
	arcParcourues = allVertices (n, arcParcourues);
	listeArc tmp = arcParcourues;
	//list of pointer on s_noeud structure we've already visited
	//to deal with the case of a treasure being on a node 
	//we don't wanna count it multiple times !
	listeNoeuds noeudsVisites = nouvlisteNoeuds();

	//for each path bewteen two nodes in the graph
	for (int i = 0; i<longueur_liste (arcParcourues); i++) {
		int j = 0;
		//we find in which direction the neighbor is
		while (tmp->n1->voisins[j] != tmp->n2) {
			j++;
		}
		//if we never checked both of the nodes
		if (!existeNoeud (noeudsVisites, tmp->n1) && !existeNoeud (noeudsVisites, tmp->n2)) {
			noeudsVisites = addNoeud (noeudsVisites, tmp->n1);
			noeudsVisites = addNoeud (noeudsVisites, tmp->n2);
			//we add to res the whole array
			res += sum_float_array (tmp->n1->tresors[j], 0, tmp->n1->distances[j]);
		}
		//if we checked only node 2
		else if (!existeNoeud (noeudsVisites, tmp->n1) && existeNoeud (noeudsVisites, tmp->n2)) {
			noeudsVisites = addNoeud (noeudsVisites, tmp->n1);
			//we add to res the whole array minus the tresor at the second node
			res += sum_float_array (tmp->n1->tresors[j], 0, tmp->n1->distances[j] - 1);
		} 	
		//if we checked only node 1
		else if (existeNoeud (noeudsVisites, tmp->n1) && !existeNoeud (noeudsVisites, tmp->n2)) {
			noeudsVisites = addNoeud (noeudsVisites, tmp->n2);
			//we add to res the whole array minus the tresor at the first node
			res += sum_float_array (tmp->n1->tresors[j], 1, tmp->n1->distances[j]);
		} 
		//if we checked both nodes already
		else if (existeNoeud (noeudsVisites, tmp->n1) && existeNoeud (noeudsVisites, tmp->n2)) {
			//we add to res the whole array minus the tresors at both nodes
			res += sum_float_array (tmp->n1->tresors[j], 1, tmp->n1->distances[j] - 1);
		} 	
	
		tmp = tmp->next;
	}

	destroylisteNoeud (noeudsVisites);
	destroylisteArc (arcParcourues);
	return res;
}



int valueToTreasure (noeud n, Dir d) {
	for (int i = 0; i<n->distances[d]; i++) {
		if (n->tresors[d][i] > 0) return i;
	}
	return n->distances[d];
}



float dijkstraRemix (listeNoeuds* nonVisites, noeud n) {
	if (*nonVisites == NULL) return -1;
	//value for the current weight of our path
	int tmp;
	//current node
	noeud current = n;
	float res[2];
	//res[0] is gonna take the value of the distance to a treasure
	res[0] = __INT32_MAX__;
	//res[1] is gonna take the value of the treasure
	res[1] = __INT32_MAX__;
	int val = 0;
	int treasureOrNot;
	//while there's still unvisited nodes
	while (*nonVisites != NULL) {
		//we check in every direction
		for (Dir i = 0; i<NDIR; i++) {
			//if there's a neighbor we haven't visited yet
			if (current->voisins[i] != NULL && existeNoeud (*nonVisites, current->voisins[i])) {
				//we get it's value
				treasureOrNot = valueToTreasure (current, i);
				tmp = treasureOrNot + val;

				//if the value is different from the distance we know there is a treasure
				if (current->distances[i] != treasureOrNot) {
					//if it's closer than the one we have right now we get that as our result
					if (tmp < res[0]) {
						res[0] = tmp;
						res[1] = current->tresors[i][treasureOrNot];
						/*	TO SHOW THAT WE DON'T STOP AT THE FIRST TREASURE FOUND IF THERE'S OTHERS
						fprintf (stderr, "################################################################");
						fprintf (stderr, "\nwe got a treasure !! distance : %.1f value :  %.1f\n",res[0], res[1]); */
					}
				}
				//we get the weight to go to the neighbor
				int valNeighbor = valueWeight (*nonVisites, current->voisins[i]);
				//if it's bigger than the distance we have through this path we change it's weight
				if (valNeighbor > tmp || valNeighbor < 0) {
					*nonVisites = changeValueWeight (*nonVisites, current->voisins[i], tmp);
				}
			}

		}
		//we remove the current node from the non-visited list
		*nonVisites = removeNoeud (*nonVisites, current);
		//we get the node that has the minimum weight as our current node
		current = nodeMinimumWeight (*nonVisites);
		//if there are only nodes that have a weight of infinity (-1) we return
		if (current == NULL) return res[1];
		//update val
		val += valueWeight (*nonVisites, current);
	}

	return res[1];
}

float valeurPlusProcheTresors (noeud n) {

	listeNoeuds nonVisites = nouvlisteNoeuds ();
	listeArc chemins = nvListeArc ();
	//we get all the vertices of the graph in a list
	chemins = allVertices (n, chemins);
	listeArc tmp = chemins;

	//we get all the nodes of the graph inside our list of nodes
	for (int i = 0; i < longueur_liste (chemins); i++) {
		if (!existeNoeud (nonVisites, tmp->n1))
			nonVisites = addNoeud (nonVisites, tmp->n1);
		if (!existeNoeud (nonVisites, tmp->n2))
			nonVisites = addNoeud (nonVisites, tmp->n2);
		tmp = tmp->next;
	}
	//we change the value of the node we're asked to start from to 0 (initial value)
	nonVisites = changeValueWeight (nonVisites, n, 0);
	float res = dijkstraRemix (&nonVisites, n);
	destroylisteArc (chemins);
	destroylisteNoeud (nonVisites);
	return res;
}

