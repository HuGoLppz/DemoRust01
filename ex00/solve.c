#include "rush01.h"

static void	donde_cae(int casilla, int *fila, int *columna)
{
	*fila = 0;
	*columna = casilla;
	while (*columna >= LADO)
	{
		*columna = *columna - LADO;
		*fila = *fila + 1;
	}
}

static int	encaja(int tablero[LADO][LADO], int *pistas, int fila, int columna)
{
	int	fila_llena;
	int	columna_llena;

	fila_llena = 0;
	columna_llena = 0;
	if (columna == LADO - 1)
		fila_llena = 1;
	if (fila == LADO - 1)
		columna_llena = 1;
	if (fila_llena == 1 && fila_bien(tablero, pistas, fila) == 0)
		return (0);
	if (columna_llena == 1 && columna_bien(tablero, pistas, columna) == 0)
		return (0);
	return (1);
}

int	resolver(int tablero[LADO][LADO], int *pistas, int casilla)
{
	int	fila;
	int	columna;
	int	altura;

	if (casilla == LADO * LADO)
		return (1);
	donde_cae(casilla, &fila, &columna);
	altura = 1;
	while (altura <= LADO)
	{
		if (cabe_aqui(tablero, fila, columna, altura) == 1)
		{
			tablero[fila][columna] = altura;
			if (encaja(tablero, pistas, fila, columna) == 1
				&& resolver(tablero, pistas, casilla + 1) == 1)
				return (1);
			tablero[fila][columna] = 0;
		}
		altura = altura + 1;
	}
	return (0);
}

/*
Aqui esta la parte de pensar, y lo hago a base de prueba y error. Voy
rellenando las 16 casillas una detras de otra, de izquierda a derecha y
de arriba abajo; para saber en que fila y columna cae cada casilla voy
restando 4 hasta que me quedo dentro del tablero. En cada casilla pruebo
las alturas del 1 al 4: si no se repite, la pongo, y si con eso acabo
de llenar una fila o una columna compruebo que se vean las cajas que
dicen las pistas. Si todo cuadra paso a la siguiente casilla, y si mas
adelante me quedo atascado vuelvo, borro lo que puse y pruebo otra
altura. Cuando consigo llenar las 16, ya esta, tengo la solucion.
*/
