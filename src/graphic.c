#include "graphic.h"

char* itostr(int i) {
    char const digit[] = "0123456789";
    char* p = (char*) malloc (4);
    int shifter = i;
    do{ //Move to where representation ends
        ++p;
        shifter = shifter/10;
    }while(shifter);
    *p = '\0';
    do{ //Move back, inserting digits as u go
        *--p = digit[i%10];
        i = i/10;
    }while(i);
    return p;
}

char* init_pgm (int x_size, int y_size) {
	char *init = {"P2\n"};
	char *end_init = {"255\n"};
	char* x = (char *) malloc (12); //tableau de char dans lequel on mettra la taille de x
	char* y = (char *) malloc (12);; //tableau de char dans lequel on mettra la taille de y
	sprintf (x, "%d ", x_size);
	sprintf (y, "%d\n", y_size);

	char *res = (char *) malloc (30);
	res = strcat (res, init);
	res = strcat (res, x);
	res = strcat (res, y);
	res = strcat (res, end_init);
	free (x);
	free (y);
	printf ("%s", res);
	return res;
}

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
		printf ("###########\n");
		int u = 0;
		int position_x1, position_y1;

		while (tmp->n1->voisins[u] != tmp->n2) { ++u; }

		position (tmp->n1, &position_x1, &position_y1);

		switch (u) {
			case NORD : 
				printf ("NORD : je vais de %d à %d en x = %d\n", position_y1, position_y1 - tmp->n1->distances[NORD], position_x1);
				for (int j = position_y1; j > position_y1 - tmp->n1->distances[NORD]; j--) {
					tab_pgm [j][position_x1] = 1;
				}
				break;
			case EST : 
				printf ("EST : je vais de %d à %d en y = %d\n", position_x1, position_x1 + tmp->n1->distances[EST], position_y1);
				for (int j = position_x1; j < position_x1 + tmp->n1->distances[EST]; j++) {
					tab_pgm [position_y1][j] = 1;
				}
				break;
			case SUD : 
				printf ("SUD : je vais de %d à %d en x = %d\n", position_y1, position_y1 + tmp->n1->distances[SUD], position_x1);
				for (int j = position_y1; j < position_y1 + tmp->n1->distances[SUD]; j++) {
					tab_pgm [j][position_x1] = 1;
				}
				break;	
			case OUEST :
				printf ("OUEST : je vais de %d à %d en y = %d\n", position_x1, position_x1 - tmp->n1->distances[OUEST], position_y1);
				for (int j = position_x1; j > position_x1 - tmp->n1->distances[OUEST]; j--) {
					tab_pgm [position_y1][j] = 1;
				}
				break;		
		}
		
		tab_pgm [position_y1][position_x1] = 2;
		tmp = tmp->next;
	}

	destroylisteArc (arcDuGraphe);
	return tab_pgm;
}

void write_to_file (int ** pgm_int_array, int x_size, int y_size) {
	char* pathname = {"image/image.pgm"};
	for (int i = 0; i <= y_size; i++) {
		for (int j = 0; j <= x_size; j++) {
			if (pgm_int_array [i][j] == 1) {
				if (pgm_int_array[i+1][j] == 1 || pgm_int_array[i+1][j]) {

				}
			}
			else if (pgm_int_array [i][j] == 2) {

			}
		}
	}

}

int create_black_image (int x_size, int y_size, char* pathname) {

	char buf [2*x_size*y_size+1];

	for (int i = 0; i < x_size*y_size; i+=2) {
		buf[i] = '0'; //0 == black
		buf[i+1] = ' '; //il faut un espace entre chaque nombre
	}

	buf[x_size*y_size] = '\0';

	size_t size_written;

	//syscall to create a file, or to write in existing file
	int fd = open (pathname, O_CREAT | O_WRONLY | O_TRUNC, 0666);
//	CHECK (fd);

	char *buf_init = init_pgm (x_size, y_size);

	size_written =  write(fd, buf_init, strlen(buf_init));
	//CHECK (size_written);

	for (int j = 0; j<y_size; j++) {
		
		size_written =  write (fd, buf, 2*x_size);
		//CHECK (size_written);
		size_written = write (fd, "\n", 1);
	//	CHECK (size_written);

	}
	
	free (buf_init);
	return fd;
}

/* petit test
int main () {
	char* file = {"image/image.pgm"};
	create_black_image (400, 400, file);
	return 0;
} */