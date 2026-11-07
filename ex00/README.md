# Rush01 — Rascacielos 4x4

Es el puzzle de los rascacielos de toda la vida. Tienes un tablero de 4x4 y en cada casilla va una caja (o un edificio, como prefieras) de altura 1, 2, 3 o 4. Lo único que sabes es cuántas cajas se ven si te pones en cada borde del tablero y miras hacia dentro. Y ojo, que las altas tapan a las bajas que tienen detrás.

El programa tiene que rellenar el tablero cumpliendo dos reglas:

1. En una misma fila o columna no se puede repetir ninguna altura.
2. Desde cada lado se tiene que ver justo el número de cajas que dice la pista.

## Cómo probarlo

Primero lo compilas:

```bash
cc -Wall -Wextra -Werror -o rush01 *.c
```

Y luego lo ejecutas pasándole las 16 pistas entre comillas, todas juntas en un solo argumento:

```bash
./rush01 "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2" | cat -e
```

Si todo va bien, te pinta el tablero resuelto:

```
1 2 3 4$
2 3 4 1$
3 4 1 2$
4 1 2 3$
```

El `| cat -e` es solo para ver dónde acaba cada línea: el `$` es el salto de línea. Si lo pruebas en Windows te saldrá `^M$`, porque allí cada salto de línea lleva un `\r` delante; en Linux o en Mac sale tal cual.

Si le pasas algo mal escrito, o un puzzle que no tiene solución, te contesta `Error` (con su salto de línea) y ya está, sin más explicaciones.

## Cómo se escriben las pistas

Las 16 pistas van en este orden, que es lo que más lía al principio:

1. Las 4 de arriba, de izquierda a derecha: lo que se ve mirando cada columna desde arriba.
2. Las 4 de abajo, también de izquierda a derecha.
3. Las 4 de la izquierda, de arriba abajo: lo que se ve mirando cada fila desde la izquierda.
4. Las 4 de la derecha, también de arriba abajo.

Si colocas las pistas del ejemplo alrededor de su solución, queda así:

```
                desde arriba
                 4  3  2  1
               +------------+
            4  | 1  2  3  4 |  1
desde la    3  | 2  3  4  1 |  2   desde la
izquierda   2  | 3  4  1  2 |  2   derecha
            1  | 4  1  2  3 |  2
               +------------+
                 1  2  2  2
                desde abajo
```

Mira la primera fila, `1 2 3 4`: desde la izquierda se ven las cuatro, porque cada caja es más alta que la anterior, y desde la derecha solo se ve el 4, que tapa a todas las demás. Por eso sus pistas son un 4 y un 1.

Dentro del programa las pistas se guardan en ese mismo orden en `pistas`: de la 0 a la 3 las de arriba, de la 4 a la 7 las de abajo, de la 8 a la 11 las de la izquierda y de la 12 a la 15 las de la derecha.

## Qué hay en cada archivo

- **`rush01.h`**: la "lista de la compra". Dice que el tablero mide 4 de lado (`LADO`) y apunta todas las funciones, para que los archivos se conozcan entre ellos.
- **`main.c`**: el que manda. Mira que le hayas pasado un solo argumento, manda leer las pistas, deja el tablero vacío, le pide a `resolver` que lo rellene y al final enseña el resultado o dice `Error`.
- **`parse.c`**: lee el texto que le pasas y saca de ahí las 16 pistas (`leer_pistas`).
- **`check.c`**: el árbitro. Cuenta cuántas cajas se ven (`cuantas_se_ven`), revisa filas (`fila_bien`) y columnas (`columna_bien`), y mira si una altura se puede poner en una casilla sin repetirse (`cabe_aqui`).
- **`solve.c`**: donde se piensa. Aquí está `resolver`, que va probando alturas hasta dar con la solución, con sus dos ayudantes: `donde_cae` y `encaja`.
- **`print.c`**: lo que sale por pantalla, o sea, el tablero (`ensenar_tablero`) o el `Error` (`quejarse`).

## Cómo funciona por dentro

### Leer las pistas

`leer_pistas` va leyendo el texto letra a letra, como si lo siguieras con el dedo. Cada letra tiene que ser un número del 1 al 4, y justo detrás solo puede venir:

- un espacio, siempre que después haya algo más, o
- el final del texto.

Con esa regla tan sencilla ya se quedan fuera los espacios dobles, los espacios al principio o al final, los números de dos cifras, las letras, el 0, el 5… Y al terminar tiene que haber justo 16 números, ni uno más ni uno menos.

### Contar cuántas cajas se ven

Una caja se ve si es más alta que todas las que tiene delante. Así que `cuantas_se_ven` recorre la hilera acordándose de la caja más alta que ha visto hasta ahora, y cada vez que aparece una más alta, suma uno:

```
2 3 1 4   →   el 2 se ve, el 3 se ve, el 1 queda tapado, el 4 se ve   →   se ven 3
```

Para mirar desde el otro lado (desde la derecha o desde abajo), primero copia la hilera dada la vuelta con `poner_en_orden` y luego cuenta igual. Se podría hacer sin copiar nada, pero así se entiende mejor.

Con eso ya está casi todo:

- `fila_bien` mira una fila desde la izquierda y desde la derecha, y lo compara con sus pistas.
- `columna_bien` primero copia la columna en una hilera aparte (`de_pie`) y luego hace lo mismo, desde arriba y desde abajo.

### Que no se repitan alturas

Antes de poner una altura en una casilla, `cabe_aqui` repasa toda su fila y después toda su columna, por si esa altura ya estaba. Las casillas vacías valen 0, así que no molestan.

### Resolver a base de prueba y error

Aquí no hay ninguna fórmula mágica: el programa hace lo mismo que harías tú con un lápiz y una goma de borrar.

Va rellenando las 16 casillas una detrás de otra, de izquierda a derecha y de arriba abajo. Las casillas van numeradas del 0 al 15, y para saber dónde cae cada una, `donde_cae` le va quitando 4 al número y baja una fila cada vez que lo hace; lo que sobra al final es la columna. Sí, con `/` y `%` sería más corto, pero así se ve mejor lo que pasa.

En cada casilla:

1. Prueba las alturas en orden: 1, 2, 3 y 4.
2. Si la altura no está ya en esa fila ni en esa columna (`cabe_aqui`), la apunta.
3. Si con eso acaba de llenar una fila o una columna, `encaja` comprueba que se vea lo que dicen las pistas. Con una fila a medias no tiene sentido mirarlo, porque todavía no se sabe cómo va a quedar.
4. Si todo cuadra, pasa a la casilla siguiente.
5. Si no cuadra, o si más adelante se queda atascado, borra esa altura (la deja otra vez a 0) y prueba con la siguiente.
6. Si no le vale ninguna de las cuatro, se rinde con esa casilla y le toca a la anterior cambiar la suya.

Cuando consigue llenar las 16 casillas sin romper ninguna regla, ya tiene la solución y para. Como siempre prueba las alturas de menor a mayor, la solución que enseña es la primera que encuentra, que es justo lo que pide el enunciado.

Y si lo ha probado todo y no hay manera, `resolver` acaba devolviendo 0 y `main` dice `Error`.

### Enseñar el resultado

`ensenar_tablero` va fila por fila y casilla por casilla. Convierte cada altura en su número escrito sumándole `'0'`, pone un espacio entre número y número (menos después del último) y un salto de línea al acabar cada fila. Todo con `write`, letra a letra.

## Cosas que he probado

- El ejemplo del enunciado sale clavado.
- Con entradas mal escritas contesta `Error`: sin argumentos, con dos argumentos, con el texto vacío, con 15 o 17 números, con un espacio al principio o al final, con dos espacios seguidos, con un 5 o con un número de dos cifras.
- Con puzzles imposibles (por ejemplo, todas las pistas a 4) también contesta `Error`.
- Y la prueba gorda: saqué todos los tableros 4x4 válidos que existen (576), calculé las pistas de cada uno (salen 438 combinaciones distintas) y el programa encuentra una solución correcta para todas.

## Funciones que uso

Solo `write`. No hace falta `malloc` ni `free`, porque el tablero (16 casillas) y las pistas (16 números) son tan pequeños que caben de sobra en variables normales.
