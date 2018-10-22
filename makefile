all:
	gcc -c src/funciones/procesos.c -Wall
	gcc -c src/Players/bot.c -Wall
	gcc -c src/Players/usuario.c -Wall
	gcc -c src/Lista/lista.c -Wall
	gcc -c src/main.c -Wall
	gcc procesos.o bot.o main.o -o main
	make clean

run:
	./main

val:
	valgrind -v ./main

clean:
	find . -name '*.o' -type f -delete
	# rm -f main