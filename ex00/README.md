# Rush01 — El puzle de los rascacielos

Este programa resuelve el puzle de los rascacielos en un tablero de 4x4. El README cuenta primero cómo funciona el juego, para que lo entienda cualquiera aunque no lo haya visto nunca, y después qué hace cada archivo del programa.

## Cómo funciona el juego

### El tablero

El juego va de una ciudad pequeñita vista desde arriba, como en un mapa: una cuadrícula de 4x4 manzanas. En cada manzana hay un rascacielos que puede tener 1, 2, 3 o 4 pisos. En el enunciado los llaman "cajas", pero es lo mismo.

Quien juega no sabe qué altura tiene cada uno. Lo único que tiene son 16 pistas colocadas alrededor del tablero, cuatro por cada lado, y con ellas tiene que averiguar dónde va cada edificio.

### Las dos reglas

1. **No se repiten alturas.** En cada fila y en cada columna tienen que estar el 1, el 2, el 3 y el 4, una vez cada uno, como en un sudoku pequeñito.
2. **Cada pista dice cuántos edificios se ven.** Es como si alguien se pusiera de pie en el sitio de la pista, fuera del tablero, y mirara a lo largo de esa fila o columna: la pista es el número de edificios que vería.

### Cómo se cuentan los edificios que se ven

Los edificios altos tapan a los bajos que tienen detrás. Así que, desde donde se mira, un edificio solo se ve si es más alto que todos los que tiene delante.

Para contarlos sin liarse, basta con recorrer la fila desde ese lado y acordarse del más alto que ha salido hasta ahora. Cada vez que aparece uno más alto que ese, se ve y cuenta uno más; si es más bajo, queda tapado.

Unos ejemplos, mirando siempre desde la izquierda:


1 2 3 4   →  se ven 4: cada uno es más alto que el anterior
4 3 2 1   →  se ve 1: el 4 está delante y tapa a todos
2 3 1 4   →  se ven 3: el 2, el 3 y el 4 (el 1 queda escondido detrás del 3)
3 1 4 2   →  se ven 2: el 3 y el 4 (el 1 y el 2 quedan tapados)


Ojo, que la misma fila cambia según desde dónde se mire: `2 3 1 4` deja ver 3 edificios desde la izquierda, pero desde la derecha lo primero que aparece es el 4, que tapa a todos, así que solo se ve 1.

### Trucos para resolverlo a mano

Algunas pistas dan mucha información de golpe:

- **Un 4** quiere decir que se ven todos, así que van en escalera, `1 2 3 4`, empezando por ese lado.
- **Un 1** quiere decir que solo se ve uno, así que el 4 está justo delante, en la primera casilla.
- **El 4 siempre se ve** desde los dos extremos de su fila y de su columna, porque no hay nada más alto que lo tape.
- **Las dos pistas de una misma fila o columna nunca suman más de 5.** Desde cada lado solo se ven edificios hasta llegar al 4 (lo que hay detrás queda tapado), y el 4 lo cuentan los dos lados. Si dos pistas enfrentadas suman 6 o más, el puzle no tiene solución.

### Un ejemplo resuelto paso a paso

Estas son las pistas del ejemplo del enunciado colocadas alrededor del tablero vacío:

```
                desde arriba
                 4  3  2  1
               +------------+
            4  | .  .  .  . |  1
desde la    3  | .  .  .  . |  2   desde la
izquierda   2  | .  .  .  . |  2   derecha
            1  | .  .  .  . |  2
               +------------+
                 1  2  2  2
                desde abajo
```

1. La primera columna tiene un 4 arriba, así que es una escalera: 1, 2, 3 y 4 bajando.
2. La primera fila tiene un 4 a la izquierda, así que también es una escalera: `1 2 3 4`.
3. Las dos pistas de 1 cuadran con eso: la de arriba de la última columna pide un 4 en la esquina de arriba a la derecha, y la de la izquierda de la última fila pide un 4 en la esquina de abajo a la izquierda. Los dos ya están ahí.

   Por ahora el tablero va así:

   ```
   1 2 3 4
   2 . . .
   3 . . .
   4 . . .
   ```

4. La segunda fila empieza por 2 y le faltan el 1, el 3 y el 4. Tiene que dejar ver 3 edificios desde la izquierda y 2 desde la derecha. Probando las combinaciones, la única que cumple las dos es `2 3 4 1`.
5. La tercera fila empieza por 3. En la última columna ya están el 4 y el 1, y la fila ya tiene su 3, así que en la última casilla de la fila solo cabe el 2. Para el medio quedan el 1 y el 4, y como la tercera columna ya tiene un 4, el orden es `3 4 1 2`.
6. La última fila empieza por 4, y en cada columna solo queda un número por usar: el 1, el 2 y el 3. Queda `4 1 2 3`.

Y ya está. Si se comprueban todas las pistas, cuadran:

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

### Cuando no hay solución

No todas las combinaciones de pistas tienen solución. Si, por ejemplo, todas las pistas fueran 4, la primera columna tendría que ser una escalera bajando (por la pista de arriba) y a la vez una escalera subiendo (por la de abajo), y eso es imposible. Además, 4 + 4 son 8, más de 5. En casos así el programa contesta `Error`.

## Cómo se usa el programa

Las 16 pistas se le pasan en un solo argumento, separadas por un espacio y en este orden:

1. Las 4 de arriba, de izquierda a derecha.
2. Las 4 de abajo, de izquierda a derecha.
3. Las 4 de la izquierda, de arriba abajo.
4. Las 4 de la derecha, de arriba abajo.

Para el ejemplo de antes:

```bash
cc -Wall -Wextra -Werror -o rush01 *.c
./rush01 "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2" | cat -e
```

```
1 2 3 4$
2 3 4 1$
3 4 1 2$
4 1 2 3$
```

El `| cat -e` solo sirve para ver dónde acaba cada línea (el `$`). En Windows saldrá `^M$`, porque allí cada salto de línea lleva un `\r` delante.

Si las pistas están mal escritas o el puzle no tiene solución, el programa escribe `Error` y un salto de línea.

## Qué hace cada archivo

El programa está repartido en seis archivos. Cuando se ejecuta, el recorrido es este:

```
main.c   →  comprueba que haya exactamente un argumento
parse.c  →  saca las 16 pistas del texto
main.c   →  deja el tablero vacío
solve.c  →  rellena el tablero probando alturas
            (y le pregunta a check.c si lo que pone vale)
print.c  →  enseña el tablero, o escribe Error si algo ha fallado
```

### `rush01.h` — la lista de la compra

No hace nada por sí solo, pero lo incluyen todos los `.c`:

- Define `LADO`, que vale 4. Es el tamaño del tablero, y se usa en todo el programa en lugar de escribir el 4 a mano.
- Apunta los nombres de las funciones que se usan de un archivo a otro, para que cada `.c` sepa que existen las de los demás.
- Incluye `unistd.h`, que es donde está `write`.

### `main.c` — el que manda

Es donde empieza el programa, y el que va llamando a los demás.

- `main` comprueba que se le haya pasado exactamente un argumento y que `leer_pistas` lo acepte. Si todo va bien, vacía el tablero, le pide a `resolver` que lo rellene y lo enseña con `ensenar_tablero`. Si algo falla por el camino, se lo apunta en `todo_va_bien` y al final llama a `quejarse`, que escribe `Error`.
- `limpiar_tablero` pone las 16 casillas a 0. En todo el programa, un 0 quiere decir "casilla vacía".

### `parse.c` — el que lee las pistas

Convierte el texto que se escribe al ejecutar el programa en los 16 números de las pistas.

- `leer_pistas` va letra a letra. Cada letra tiene que ser un número del 1 al 4, y justo detrás solo puede venir un espacio con algo más después, o el final del texto. Cada número bueno lo guarda en `pistas`: de la 0 a la 3 las de arriba, de la 4 a la 7 las de abajo, de la 8 a la 11 las de la izquierda y de la 12 a la 15 las de la derecha. Solo da el visto bueno si ha juntado justo 16.
- `es_cifra_buena` dice si una letra es un número del 1 al 4.

Con esto quedan fuera los espacios dobles, los espacios al principio o al final, los números de dos cifras, las letras, el 0, el 5 y cualquier cantidad de números que no sea 16.

### `check.c` — el árbitro

Aquí están las dos reglas del juego convertidas en código.

- `cuantas_se_ven` cuenta cuántos edificios se ven en una hilera, igual que lo contaría una persona: se acuerda del más alto que lleva y suma uno cada vez que aparece uno más alto. Si se le pide `al_reves`, mira la hilera desde el otro extremo.
- `poner_en_orden` es su ayudante: copia la hilera tal cual o dada la vuelta, para que `cuantas_se_ven` siempre pueda contar de delante hacia atrás.
- `fila_bien` mira una fila desde la izquierda y desde la derecha, y comprueba que coincida con sus dos pistas.
- `columna_bien` hace lo mismo con una columna, desde arriba y desde abajo. El tablero está guardado fila por fila, así que para tener la columna seguida primero la copia en una hilera aparte (`de_pie`), y luego ya puede usar `cuantas_se_ven`.
- `cabe_aqui` es la primera regla: antes de poner una altura en una casilla, repasa su fila y su columna por si esa altura ya está. Las casillas vacías valen 0, así que no molestan.

### `solve.c` — el que resuelve

El programa no usa los trucos de antes: no razona, prueba. Hace lo mismo que haría cualquiera con un lápiz y una goma de borrar si no se le ocurriera nada mejor.

- `resolver` rellena las 16 casillas en orden, de izquierda a derecha y de arriba abajo. En cada casilla prueba el 1, el 2, el 3 y el 4:
  1. Si la altura no se repite (`cabe_aqui`), la escribe.
  2. Si con eso todo sigue cuadrando (`encaja`), se llama a sí misma para rellenar la casilla siguiente.
  3. Si no cuadra, o si más adelante se queda atascada, borra la altura (vuelve a poner un 0) y prueba con la siguiente.
  4. Si no le sirve ninguna de las cuatro, se rinde con esa casilla y le toca a la anterior cambiar la suya.

  Cuando consigue poner las 16 casillas, el tablero ya cumple todas las reglas y ha terminado. Como prueba siempre de menor a mayor, se queda con la primera solución que encuentra, que es la que pide el enunciado. Si lo prueba todo y no hay manera, devuelve 0 y `main` escribe `Error`.
- `donde_cae` pasa del número de casilla (del 0 al 15) a su fila y su columna: le va quitando 4 y baja una fila cada vez; lo que sobra es la columna.
- `encaja` comprueba las pistas, pero solo cuando una fila o una columna se acaba de llenar. Con una fila a medias todavía no se puede saber cuántos edificios se verán.

### `print.c` — el que habla

Todo lo que sale por pantalla pasa por aquí. Como el enunciado solo deja usar `write`, se escribe letra a letra.

- `ensenar_tablero` escribe el tablero fila por fila. Convierte cada altura en su número escrito sumándole `'0'`, pone un espacio entre número y número (menos después del último) y un salto de línea al final de cada fila.
- `escribir_letra` escribe una sola letra con `write`.
- `quejarse` escribe `Error` y un salto de línea.
