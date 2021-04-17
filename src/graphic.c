#include "graphic.h"

int ** create_int_array (int x_size, int y_size, noeud node) {

	//tableau d'entier 
	int ** tab_pgm = (int **) malloc ((y_size + 1) * sizeof (int*));
	if (tab_pgm == NULL) abort ();
	for (int i = 0; i <= x_size; i++) {
		tab_pgm[i] = (int*) malloc ((x_size + 1) * sizeof (int));
		if (tab_pgm [i] == NULL) abort ();
	}

	//on remplit le tableau avec des 0
	for (int j = 0; j <= y_size; j++) {
		for (int k = 0; k <= x_size; k++) {
			tab_pgm[j][k] = 0;
		}
	} 

	//on recupere tout les arcs du graphe dans arcDuGraphe
	listeArc arcDuGraphe = nvListeArc ();
	arcDuGraphe = longueurRec (node, arcDuGraphe); 
	
	listeArc tmp = arcDuGraphe;
	for (int v = 0; v < longueur_liste (arcDuGraphe); v++) {
		int u = 0;
		int position_x1, position_y1, position_x2, position_y2;

		while (tmp->n1->voisins[u] != tmp->n2) { ++u; }

		position (tmp->n1, &position_x1, &position_y1);
		position (tmp->n2, &position_x2, &position_y2);

		switch (u) {
			case NORD : 
				for (int j = position_y1; j > position_y1 - tmp->n1->distances[NORD]; j--) {
					tab_pgm [j][position_x1] = 200;
				}
				break;
			case EST : 
				for (int j = position_x1; j < position_x1 + tmp->n1->distances[EST]; j++) {
					tab_pgm [position_y1][j] = 200;
				}
				break;
			case SUD : 
				for (int j = position_y1; j < position_y1 + tmp->n1->distances[SUD]; j++) {
					tab_pgm [j][position_x1] = 200;
				}
				break;	
			case OUEST :
				for (int j = position_x1; j > position_x1 - tmp->n1->distances[OUEST]; j--) {
					tab_pgm [position_y1][j] = 200;
				}
				break;		
		}
		
		tab_pgm [position_y1][position_x1] = 128;
		tab_pgm [position_y2][position_x2] = 128;
		tmp = tmp->next;
	}

	destroylisteArc (arcDuGraphe);
	return tab_pgm;

}

void write_to_file (int ** pgm_int_array, int x_size, int y_size) {
	char* pathname = {"image/image.pgm"};
	
	int ** resized = (int**) malloc ((y_size+2) * N * sizeof (int*));

	if (resized == NULL) abort ();
	for (int i = 0; i<=(y_size+2)*N; i++) {
		resized[i] = (int *) malloc ((x_size+2) * N * sizeof (int));
		if (resized[i] == NULL) abort ();
	}
	printf ("memory allocated\n");
	for (int i = 0; i <= y_size; i++) {
		for (int j = 0; j <= x_size; j++) {
			for (int k = 0; k <= N+1; k++) {
				for (int l = 0; l <= N+1; l++) {
          			//transfer the data
          			resized[i * N + k][j * N + l] =  pgm_int_array[i][j];
				}
			}
		}
	}
	printf ("resized\n");

	int fd = open (pathname, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1) { fprintf (stderr, "problem with syscall open\n"); abort();}

	printf ("file opened\n");
	char *buf_init = (char*) malloc (40);
	sprintf (buf_init, "P2\n%d %d\n255\n", x_size*N+N, y_size*N+N);
	printf ("%s",buf_init);
	
	int size_written =  write(fd, buf_init, strlen(buf_init));
	if (size_written == -1) { fprintf (stderr, "problem with syscall write\n"); abort();}
	free (buf_init);

 	for (int y = 0; y < y_size * N + N; y++) {
		for (int x = 0; x < x_size * N + N; x++) {

			char *strint = (char*) malloc (10);
			sprintf (strint, "%d ", resized[y][x]);
			size_written = write (fd, strint, strlen (strint));
			if (size_written == -1) { fprintf (stderr, "problem with syscall write\n"); abort();}
			free (strint);

		}

		size_written = write (fd, "\n", 1);
		if (size_written == -1) { fprintf (stderr, "problem with syscall write\n"); abort();}

	}

	if (close (fd) == -1) { fprintf (stderr, "problem with syscall close\n"); abort();}
	printf ("file closed\n");
	printf ("\nlabyrinth is in image/ and has name image.pmg\n\n");
}