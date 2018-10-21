all:
	gcc -Wall src/Players/bot.c -o src/Players/bot
	gcc -Wall src/Players/usuario.c -o src/Players/user
	gcc -Wall src/Lista/lista.h src/Lista/lista.c src/main.c -o main
run:
	./main
val:
	valgrind -v ./main
