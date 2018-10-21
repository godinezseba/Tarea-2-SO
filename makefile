all:
	gcc -c src/funciones/procesos.c -Wall
	gcc -c src/Players/bot.c -Wall
	gcc -c src/Players/usuario.c -Wall
	gcc -c src/Lista/lista.c -Wall
	gcc -c src/main.c -Wall
	gcc procesos.o usuario.o -o src/Players/usuario
	gcc procesos.o bot.o -o src/Players/bot
	gcc procesos.o main.o -o main
	make clean

run:
	./main

val:
	valgrind -v ./main

clean:
	find . -name '*.o' -type f -delete
	# rm -f src/Players/bot
	# rm -f src/Players/usuario
	# rm -f main