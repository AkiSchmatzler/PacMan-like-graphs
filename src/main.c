#include "graphe.h"
#include "graphic.h"
#include <stdio.h>
#include <stdlib.h>

int main () {
	noeud laby[12];

	for (int i = 0; i<12; i++) {
		laby[i] = nouvnoeud ();
	}
	
	float zero_to_1 	[60] = {0};
	float one_to_2  	[80] = {0};
	float one_to_6  	[30] = {0};
	float two_to_8  	[30] = {0};
	float three_to_9 	[30] = {0};
	float four_to_5 	[20] = {0};
	float five_to_6 	[70] = {0};
	float five_to_10 	[20] = {0};
	float six_to_7		[50] = {0};
	float seven_to_8	[30] = {0};
	float seven_to_11	[20] = {0};
	float eight_to_9	[30] = {0};
	float ten_to_11	   [120] = {0};

	one_to_6 	[29] = 1000;
	five_to_6 	[69] = 1000;
	six_to_7 	[0]  = 1000;
	three_to_9	[15] = 1000;
	ten_to_11	[10] = 1000;

	

	passage(laby[0], laby[1], EST, 60, 	zero_to_1);
	passage(laby[1], laby[2], EST, 80, 	one_to_2);
	passage(laby[1], laby[6], SUD, 30, 	one_to_6);
	passage(laby[2], laby[8], SUD, 30, 	two_to_8);
	passage(laby[3], laby[9], SUD, 30, 	three_to_9);
	passage(laby[4], laby[5], SUD, 20, 	four_to_5);
	passage(laby[5], laby[6], EST, 70, 	five_to_6);
	passage(laby[5], laby[10], SUD, 20, five_to_10);
	passage(laby[6], laby[7], EST, 50, 	six_to_7);
	passage(laby[7], laby[8], EST, 30, 	seven_to_8);
	passage(laby[7], laby[11], SUD, 20, seven_to_11);
	passage(laby[8], laby[9], EST, 30, 	eight_to_9);
	passage(laby[10], laby[11], EST, 120, ten_to_11);


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
/* 
	for (int i = 0; i<=y; i++) {
		for (int j = 0; j<=x; j++) {
			printf ("%d ", tab[i][j]);
		}
		printf("\n");
	} */

	write_to_file (tab, x,y);

/* 	for (int k = 0; k<12; k++) {
		printf ("V'la les trésors : %.1f moulaga\n", valeurTotalTresors(laby[k]));
	} */


	for (int k = 0; k<12; k++) {
		destroynoeud(laby[k]);
	}
	return 0;
	
/* 	noeud pacman[54];
	for (int i = 0; i<54; i++) {
		pacman[i] = nouvnoeud();
	}
	float tr_3[3] = {0};
	float tr_5[5] = {0};
	float tr_6[6] = {0};
	float tr_9[9] = {0};
	float tr_2[2] = {0};
	passage (pacman[0], pacman[1], EST, 5, tr_5);
	passage (pacman[0], pacman[6], SUD, 3, tr_3);
	passage (pacman[1], pacman[7], SUD, 3, tr_3);
	passage (pacman[1], pacman[2], EST, 3, tr_3);
	passage (pacman[2], pacman[8], SUD, 3, tr_3);
	passage (pacman[2], pacman[3], EST, 9, tr_9);
	passage (pacman[3], pacman[11], SUD, 3, tr_3);
	passage (pacman[3], pacman[4], EST, 3, tr_3);
	passage (pacman[4], pacman[12], SUD, 3, tr_3);
	passage (pacman[4], pacman[5], EST, 5, tr_5);
	passage (pacman[5], pacman[13], SUD, 3, tr_3);
	passage (pacman[6], pacman[7], EST, 5, tr_5);
	passage (pacman[7], pacman[19], SUD, 6, tr_6);
	passage (pacman[8], pacman[9], EST, 3, tr_3);
	passage (pacman[9], pacman[15], SUD, 3, tr_3);
	passage (pacman[10], pacman[16], SUD, 3, tr_3);
	passage (pacman[10], pacman[11], EST, 3, tr_3);
	passage (pacman[12], pacman[22], SUD, 6, tr_6);
	passage (pacman[12], pacman[13], EST, 5, tr_5);
	passage (pacman[14], pacman[20], SUD, 3, tr_3);
	passage (pacman[14], pacman[15], EST, 3, tr_3);
	passage (pacman[15], pacman[16], EST, 3, tr_3);
	passage (pacman[16], pacman[17], EST, 3, tr_3);
	passage (pacman[17], pacman[21], SUD, 3, tr_3);
	passage (pacman[18], pacman[19], EST, 5, tr_5);
	passage (pacman[19], pacman[27], SUD, 6, tr_6);
	passage (pacman[19], pacman[20], EST, 3, tr_3);
	passage (pacman[20], pacman[24], SUD, 3, tr_3);
	passage (pacman[21], pacman[25], SUD, 3, tr_3);
	passage (pacman[21], pacman[22], EST, 3, tr_3);
	passage (pacman[22], pacman[23], EST, 5, tr_5);
	passage (pacman[22], pacman[32], SUD, 6, tr_6);
	passage (pacman[24], pacman[25], EST, 9, tr_9);
	passage (pacman[24], pacman[28], SUD, 3, tr_3);
	passage (pacman[25], pacman[31], SUD, 3, tr_3);
	passage (pacman[26], pacman[34], SUD, 3, tr_3);
	passage (pacman[26], pacman[27], EST, 5, tr_5);
	passage (pacman[27], pacman[36], SUD, 3, tr_3);
	passage (pacman[27], pacman[28], EST, 3, tr_3);
	passage (pacman[28], pacman[29], EST, 3, tr_3);
	passage (pacman[29], pacman[38], SUD, 3, tr_3);
	passage (pacman[30], pacman[39], SUD, 3, tr_3);
	passage (pacman[30], pacman[31], EST, 3, tr_3);
	passage (pacman[31], pacman[32], EST, 3, tr_3);
	passage (pacman[32], pacman[41], SUD, 3, tr_3);
	passage (pacman[32], pacman[33], EST, 5, tr_5);
	passage (pacman[33], pacman[43], SUD, 3, tr_3);
	passage (pacman[34], pacman[35], EST, 2, tr_2);
	passage (pacman[35], pacman[45], SUD, 3, tr_3);
	passage (pacman[36], pacman[37], EST, 3, tr_3);
	passage (pacman[36], pacman[46], SUD, 3, tr_3);
	passage (pacman[37], pacman[47], SUD, 3, tr_3);
	passage (pacman[37], pacman[38], EST, 3, tr_3);
	passage (pacman[38], pacman[39], EST, 3, tr_3);
	passage (pacman[39], pacman[40], EST, 3, tr_3);
	passage (pacman[40], pacman[50], SUD, 3, tr_3);
	passage (pacman[40], pacman[41], EST, 3, tr_3);
	passage (pacman[41], pacman[51], SUD, 3, tr_3);
	passage (pacman[42], pacman[52], SUD, 3, tr_3);
	passage (pacman[42], pacman[43], EST, 2, tr_2);
	passage (pacman[44], pacman[45], EST, 2, tr_2);
	passage (pacman[45], pacman[46], EST, 3, tr_3);
	passage (pacman[47], pacman[48], EST, 3, tr_3);
	passage (pacman[49], pacman[50], EST, 3, tr_3);
	passage (pacman[51], pacman[52], EST, 3, tr_3);
	passage (pacman[52], pacman[53], EST, 2, tr_2);

	int x = 0;
	int y = 0;

	taille (pacman[0], &x,&y);

	int ** tab = create_int_array (x, y, pacman[1]);

	for (int i = 0; i<=y; i++) {
		for (int j = 0; j<=x; j++) {
			printf ("%d ", tab[i][j]);
		}
		printf("\n");
	}

	write_to_file (tab, x,y);

	for (int k = 0; k<54; k++) {
		free(pacman[k]);
	} */

	return 0;
}