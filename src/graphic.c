#include "graphic.h"

int ** create_int_array (int x_size, int y_size, noeud node) {

	//2d array of integers
	int ** tab_pgm = (int **) malloc ((y_size + 1) * sizeof (int*));
	if (tab_pgm == NULL) abort ();
	for (int i = 0; i <= y_size; i++) {
		tab_pgm[i] = (int*) malloc ((x_size + 1) * sizeof (int));
		if (tab_pgm [i] == NULL) abort ();
	}

	//we fille the array with zeros
	for (int j = 0; j <= y_size; j++) {
		for (int k = 0; k <= x_size; k++) {
			tab_pgm[j][k] = 0;
		}
	} 

	//we get all the paths in the graphe in a list of paths
	listeArc arcDuGraphe = nvListeArc ();
	arcDuGraphe = longueurRec (node, arcDuGraphe); 
	
	listeArc tmp = arcDuGraphe;
	//for each path between two distinct nodes in the graph
	for (int v = 0; v < longueur_liste (arcDuGraphe); v++) {
		int u = 0;
		//we get the direction in which the path is (according to n1)
		while (tmp->n1->voisins[u] != tmp->n2) { ++u; }
		//we get the position of the two nodes in the graph
		int position_x1, position_y1, position_x2, position_y2;
		position (tmp->n1, &position_x1, &position_y1);
		position (tmp->n2, &position_x2, &position_y2);

		switch (u) {
			case NORD :
				//if the path goes to the north we go backwards on the y axis
				for (int j = position_y1; j > position_y1 - tmp->n1->distances[NORD]; j--) {
					tab_pgm [j][position_x1] = ARC_VERTICAL;	//flag for vertical paths
				}
				break;
			case EST : 
				//if the path goes to the east we go forward on the x axis
				for (int j = position_x1; j < position_x1 + tmp->n1->distances[EST]; j++) {
					tab_pgm [position_y1][j] = ARC_HORIZONTAL;	//flag for vertical paths
				}
				break;
			case SUD : 
				//if the path goes to the south we go forward on the y axis
				for (int j = position_y1; j < position_y1 + tmp->n1->distances[SUD]; j++) {
					tab_pgm [j][position_x1] = ARC_VERTICAL;	//flag for vertical paths
				}
				break;	
			case OUEST :
				//if the path goes to the west we go backwards on the x axis
				for (int j = position_x1; j > position_x1 - tmp->n1->distances[OUEST]; j--) {
					tab_pgm [position_y1][j] = ARC_HORIZONTAL;	//flag for vertical paths
				}
				break;		
		}
		
		tab_pgm [position_y1][position_x1] = NOEUD;	//flag for nodes
		tab_pgm [position_y2][position_x2] = NOEUD;	//flag for nodes
		tmp = tmp->next;
	}

	destroylisteArc (arcDuGraphe);
	return tab_pgm;

}


int ** adapt_size (int** pgm_int_array, int x_size, int y_size) {
	//non_passage is the width of each N*N square that is not getting 
	//painted in white when there is a path on that square, divided by 2
	//because there is this width on each side of the M pixels
	int non_passage = (int) (N - M) / 2;

	int ** resized = (int**) malloc ((y_size+2) * N * sizeof (int*));

	if (resized == NULL) abort ();
	for (int i = 0; i<(y_size+2)*N; i++) {
		resized[i] = (int *) malloc ((x_size+2) * N * sizeof (int));
		if (resized[i] == NULL) abort ();
	}
	printf ("memory allocated\n");

	for (int i = 0; i <= y_size; i++) {
		for (int j = 0; j <= x_size; j++) {

			for (int k = 0; k <= N+1; k++) {
				for (int l = 0; l <= N+1; l++) {
          			//if the integer in the array corresponds to a node we color the whole square lightgrey
					if (pgm_int_array[i][j] == NOEUD){
          				resized[i * N + k][j * N + l] =  170;
					}
					//if the integer in the array corresponds to a vertical path we color the square with
					//a white vertical line that has a width of M
					else if (pgm_int_array[i][j] == ARC_VERTICAL) {
						if ( l >= non_passage && l < (non_passage + M)) {
							resized[i * N + k][j * N + l] =  255;
						}
						else resized[i * N + k][j * N + l] =  0;
					}
					//if the integer in the array corresponds to an horizontal path we color the square with
					//a white horizontal line that has a width of M
					else if (pgm_int_array[i][j] == ARC_HORIZONTAL) {
						if ( k >= non_passage && k < (non_passage + M)) {
							resized[i * N + k][j * N + l] =  255;
						}
						else resized[i * N + k][j * N + l] =  0;
					}
					
					else resized[i * N + k][j * N + l] = 0;
				}
			}
		}
	}
	printf ("resized\n");
	return resized;
}

void write_to_file (int ** pgm_int_array, int x_size, int y_size) {
	char* pathname = {"image/image.pgm"};
	//call to function adapt_size
	int ** resized = adapt_size (pgm_int_array, x_size, y_size);

	//opening the file, creating it if doesn't exist, if it exists we delete it's content
	int fd = open (pathname, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1) { fprintf (stderr, "problem with syscall open\n"); abort();}

	printf ("file opened\n");
	char *buf_init = (char*) malloc (40);
	sprintf (buf_init, "P2\n%d %d\n255\n", x_size*N+N, y_size*N+N);
	printf ("%s",buf_init);
	//we write to the file the magic number and the data concerning our image (height and width)
	int size_written =  write(fd, buf_init, strlen(buf_init));
	if (size_written == -1) { fprintf (stderr, "problem with syscall write\n"); abort();}
	free (buf_init);

 	for (int y = 0; y < y_size * N + N; y++) {
		for (int x = 0; x < x_size * N + N; x++) {
			//we write each number of our array in the file
			char *strint = (char*) malloc (10);
			sprintf (strint, "%d ", resized[y][x]);
			size_written = write (fd, strint, strlen (strint));
			if (size_written == -1) { fprintf (stderr, "problem with syscall write\n"); abort();}
			free (strint);
		}
		//and print a new line character between each line of pixels
		size_written = write (fd, "\n", 1);
		if (size_written == -1) { fprintf (stderr, "problem with syscall write\n"); abort();}

	}
	//freeing resized
	for (int i = 0; i<(y_size+2)*N; i++) {
		free (resized[i]);
	}
	free (resized);

	//freeing pgm_int_array
	for (int i = 0; i <= y_size; i++) {
		free (pgm_int_array[i]);
	}
	free (pgm_int_array);


	if (close (fd) == -1) { fprintf (stderr, "problem with syscall close\n"); abort();}
	printf ("file closed\n");
	printf ("\nlabyrinth is in image/ and has name image.pmg\n\n");
}