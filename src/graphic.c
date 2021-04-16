#include "graphic.h"

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

void create_black_image (int x_size, int y_size, char* pathname) {

	char buf [2*x_size*y_size+1];

	for (int i = 0; i < x_size*y_size; i+=2) {
		buf[i] = '0'; //0 == black
		buf[i+1] = ' '; //il faut un espace entre chaque nombre
	}

	buf[x_size*y_size] = '\0';

	size_t size_written;

	//syscall to create a file, or to write in existing file
	int fd = open (pathname, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	CHECK (fd);

	char *buf_init = init_pgm (x_size, y_size);

	size_written =  write(fd, buf_init, strlen(buf_init));
	CHECK (size_written);

	for (int j = 0; j<y_size; j++) {
		
		size_written =  write (fd, buf, 2*x_size);
		CHECK (size_written);
		size_written = write (fd, "\n", 1);
		CHECK (size_written);

	}
	
	free (buf_init);
}

/* petit test
int main () {
	char* file = {"image/image.pgm"};
	create_black_image (400, 400, file);
	return 0;
} */