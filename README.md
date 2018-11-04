# Tarea 2 Sistema Operativo
### Sebastian Godinez 201673520-8

## COMPILACIÓN
`make`
## EJECUCIÓN:
`make run`
## CONSIDERACIONES:
- Considere que al invertirce el tablero tambien se invierten las posiciones, es decir, si alguien estaba en la casilla 10 al invertirce estara en la 19.

## USO DE PIPES Y MEMORIA COMPARTIDA:
La estructura princial `tablero.h` hace uso de memoria compartida tanto para la estructura, como el tablero y las posiciones de los jugadores. De esta manera todos pueden ver el tablero y si se invierte todos tambien podran verlo. Aprovecho que la posicion esta en memoria compartida y al caer en una casilla que manipule la posicion de todos, se hace a partir de este arreglo.
Los Pipes los uso para poder mantener el orden en la ejecución de los jugadores y asi no ocurran cosas raras, como que un jugador juegue antes de su turno correspondiente y ademas para la opción _siguiente pierde su turno_.
