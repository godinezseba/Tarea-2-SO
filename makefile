all:
	gcc -Wall src/bot.c -o src/bot
	gcc -Wall src/usuario.c -o src/user
	gcc -Wall src/lista.h src/lista.c src/main.c -o main
run:
	./main
val:
	valgrind -v ./main
