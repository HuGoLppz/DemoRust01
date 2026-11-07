#ifndef RUSH01_H
# define RUSH01_H

# include <unistd.h>

# define LADO 4

int		leer_pistas(char *texto, int *pistas);
int		cuantas_se_ven(int *hilera, int al_reves);
int		fila_bien(int tablero[LADO][LADO], int *pistas, int fila);
int		columna_bien(int tablero[LADO][LADO], int *pistas, int columna);
int		cabe_aqui(int tablero[LADO][LADO], int fila, int columna, int altura);
int		resolver(int tablero[LADO][LADO], int *pistas, int casilla);
void	ensenar_tablero(int tablero[LADO][LADO]);
void	quejarse(void);

#endif

/*
Esto es como la lista de la compra del programa: aqui apunto que el
tablero tiene 4 casillas de lado y dejo escritos los nombres de todas
las funciones que voy a usar, para que cada archivo .c sepa que existen
las de los demas aunque esten en otro sitio. Tambien meto unistd.h
porque es donde vive write, que es lo unico que uso para escribir.
*/
