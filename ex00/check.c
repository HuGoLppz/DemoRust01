#include "rush01.h"

static void	poner_en_orden(int *hilera, int *en_orden, int al_reves)
{
	int	vuelta;

	vuelta = 0;
	while (vuelta < LADO)
	{
		if (al_reves == 1)
			en_orden[vuelta] = hilera[LADO - 1 - vuelta];
		else
			en_orden[vuelta] = hilera[vuelta];
		vuelta = vuelta + 1;
	}
}

int	cuantas_se_ven(int *hilera, int al_reves)
{
	int	en_orden[LADO];
	int	vuelta;
	int	la_mas_alta;
	int	se_ven;

	poner_en_orden(hilera, en_orden, al_reves);
	la_mas_alta = 0;
	se_ven = 0;
	vuelta = 0;
	while (vuelta < LADO)
	{
		if (en_orden[vuelta] > la_mas_alta)
		{
			la_mas_alta = en_orden[vuelta];
			se_ven = se_ven + 1;
		}
		vuelta = vuelta + 1;
	}
	return (se_ven);
}

int	fila_bien(int tablero[LADO][LADO], int *pistas, int fila)
{
	int	desde_la_izquierda;
	int	desde_la_derecha;

	desde_la_izquierda = cuantas_se_ven(tablero[fila], 0);
	desde_la_derecha = cuantas_se_ven(tablero[fila], 1);
	if (desde_la_izquierda == pistas[LADO * 2 + fila]
		&& desde_la_derecha == pistas[LADO * 3 + fila])
		return (1);
	return (0);
}

int	columna_bien(int tablero[LADO][LADO], int *pistas, int columna)
{
	int	de_pie[LADO];
	int	piso;
	int	desde_arriba;
	int	desde_abajo;

	piso = 0;
	while (piso < LADO)
	{
		de_pie[piso] = tablero[piso][columna];
		piso = piso + 1;
	}
	desde_arriba = cuantas_se_ven(de_pie, 0);
	desde_abajo = cuantas_se_ven(de_pie, 1);
	if (desde_arriba == pistas[columna]
		&& desde_abajo == pistas[LADO + columna])
		return (1);
	return (0);
}

int	cabe_aqui(int tablero[LADO][LADO], int fila, int columna, int altura)
{
	int	mirando;
	int	cabe;

	cabe = 1;
	mirando = 0;
	while (mirando < LADO)
	{
		if (tablero[fila][mirando] == altura)
			cabe = 0;
		mirando = mirando + 1;
	}
	mirando = 0;
	while (mirando < LADO)
	{
		if (tablero[mirando][columna] == altura)
			cabe = 0;
		mirando = mirando + 1;
	}
	return (cabe);
}

/*
Este archivo es el que hace de arbitro. Para saber cuantas cajas se ven
en una hilera, primero la copio en el orden en que la miro (si miro
desde el otro lado, le doy la vuelta) y luego la recorro acordandome de
la caja mas alta que he visto: cada vez que aparece una mas alta, esa se
ve y sumo uno. Con eso, fila_bien mira una fila desde la izquierda y la
derecha, y columna_bien hace lo mismo con una columna desde arriba y
abajo (antes la pongo "de pie" en una hilera para poder usar lo mismo).
Por ultimo, cabe_aqui revisa primero toda la fila y luego toda la
columna para asegurarse de que esa altura no esta ya repetida.
*/
