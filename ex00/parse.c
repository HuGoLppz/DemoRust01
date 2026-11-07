#include "rush01.h"

static int	es_cifra_buena(char letra)
{
	if (letra >= '1' && letra <= '0' + LADO)
		return (1);
	return (0);
}

int	leer_pistas(char *texto, int *pistas)
{
	int	sitio;
	int	cuantas_llevo;
	int	se_acabo;

	sitio = 0;
	cuantas_llevo = 0;
	se_acabo = 0;
	while (se_acabo == 0)
	{
		if (cuantas_llevo == LADO * 4 || es_cifra_buena(texto[sitio]) == 0)
			return (0);
		pistas[cuantas_llevo] = texto[sitio] - '0';
		cuantas_llevo = cuantas_llevo + 1;
		sitio = sitio + 1;
		if (texto[sitio] == '\0')
			se_acabo = 1;
		else if (texto[sitio] == ' ' && texto[sitio + 1] != '\0')
			sitio = sitio + 1;
		else
			return (0);
	}
	if (cuantas_llevo == LADO * 4)
		return (1);
	return (0);
}

/*
Aqui leo el texto que me pasan letra a letra, como si lo fuera leyendo
con el dedo. Cada letra tiene que ser un numero del 1 al 4, y justo
despues solo puede venir un espacio (con algo detras) o el final del
texto; cualquier otra cosa, como dos espacios seguidos, un espacio al
final, una letra o un 5, hace que me rinda y devuelva 0. Cada numero
bueno lo guardo en pistas y voy contando cuantos llevo, y al terminar
solo doy el visto bueno si he juntado justo 16, ni uno mas ni uno menos.
*/
