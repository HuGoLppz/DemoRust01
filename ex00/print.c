#include "rush01.h"

static void	escribir_letra(char letra)
{
	write(1, &letra, 1);
}

void	ensenar_tablero(int tablero[LADO][LADO])
{
	int		fila;
	int		columna;
	char	numero;

	fila = 0;
	while (fila < LADO)
	{
		columna = 0;
		while (columna < LADO)
		{
			numero = tablero[fila][columna] + '0';
			escribir_letra(numero);
			if (columna != LADO - 1)
				escribir_letra(' ');
			columna = columna + 1;
		}
		escribir_letra('\n');
		fila = fila + 1;
	}
}

void	quejarse(void)
{
	write(1, "Error\n", 6);
}

/*
Esto solo sirve para sacar cosas por pantalla, y como solo dejan usar
write, lo hago letra a letra. Para ensenar el tablero voy fila por fila
y casilla por casilla, convierto cada altura en su numero escrito
sumandole '0', y pongo un espacio entre medias menos despues del ultimo,
que ahi va un salto de linea. Y si algo ha ido mal, quejarse escribe
Error y punto.
*/
