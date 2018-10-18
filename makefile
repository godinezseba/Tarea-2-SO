all:
	gcc -Wall src/main.c -o main
run:
	./main
val:
	valgrind -v ./main
