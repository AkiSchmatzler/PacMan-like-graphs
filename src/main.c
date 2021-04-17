#include "graphe.h"
#include "graphic.h"
#include <stdio.h>
#include <stdlib.h>


int main () {
	noeud laby[12];

	for (int i = 0; i<12; i++) {
		laby[i] = nouvnoeud ();
	}
	

	passage(laby[0], laby[1], EST, 60);
	passage(laby[1], laby[2], EST, 80);
	passage(laby[1], laby[6], SUD, 30);
	passage(laby[2], laby[8], SUD, 30);
	passage(laby[3], laby[9], SUD, 30);
	passage(laby[4], laby[5], SUD, 20);
	passage(laby[5], laby[6], EST, 70);
	passage(laby[5], laby[10], SUD, 20);
	passage(laby[6], laby[7], EST, 50);
	passage(laby[7], laby[8], EST, 30);
	passage(laby[7], laby[11], SUD, 20);
	passage(laby[8], laby[9], EST, 30);
	passage(laby[10], laby[11], EST, 120);


/* 
	for (int i = 0; i<12; i++) {
		printf("\n\n###############################\n\n");
		printf ("laby[%d] : distance voisin EST = %d\n", i, laby[i]->distances[EST]);
		printf ("laby[%d] : distance voisin SUD = %d\n", i, laby[i]->distances[SUD]);
		printf ("laby[%d] : distance voisin OUEST = %d\n", i, laby[i]->distances[OUEST]);
		printf ("laby[%d] : distance voisin NORD = %d\n", i, laby[i]->distances[NORD]);
	} */

	int x = 0;
	int y = 0;

	taille (laby[0], &x,&y);

	int ** tab = create_int_array (x, y, laby[1]);
	printf ("write to file\n");

	for (int i = 0; i<=y; i++) {
		for (int j = 0; j<=x; j++) {
			printf ("%d ", tab[i][j]);
		}
		printf("\n");
	}

	write_to_file (tab, x,y);


	for (int k = 0; k<12; k++) {
		free(laby[k]);
	}
	return 0;
}