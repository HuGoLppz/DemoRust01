#include "rush01.h"

static void	limpiar_tablero(int tablero[LADO][LADO])
{
	int	fila;
	int	columna;

	fila = 0;
	while (fila < LADO)
	{
		columna = 0;
		while (columna < LADO)
		{
			tablero[fila][columna] = 0;
			columna = columna + 1;
		}
		fila = fila + 1;
	}
}

int	main(int argc, char **argv)
{
	int	tablero[LADO][LADO];
	int	pistas[LADO * 4];
	int	todo_va_bien;

	todo_va_bien = 1;
	if (argc != 2)
		todo_va_bien = 0;
	if (todo_va_bien == 1 && leer_pistas(argv[1], pistas) == 0)
		todo_va_bien = 0;
	if (todo_va_bien == 1)
	{
		limpiar_tablero(tablero);
		if (resolver(tablero, pistas, 0) == 0)
			todo_va_bien = 0;
	}
	if (todo_va_bien == 0)
	{
		quejarse();
		return (1);
	}
	ensenar_tablero(tablero);
	return (0);
}

/*
Aqui empieza todo. Primero miro que me hayan pasado exactamente una cosa
al ejecutar el programa y que esa cosa sean las 16 pistas bien escritas.
Si algo falla me lo apunto en todo_va_bien y sigo hasta el final. Si las
pistas estan bien, pongo el tablero entero a cero (vacio), le pido a
resolver que lo rellene, y si lo consigue lo enseno por pantalla. Si en
cualquier momento algo ha salido mal, solo digo Error y me voy.
*/
