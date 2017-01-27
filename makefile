makeznake: main.c apple.c canvas.c input.c znake.c
	gcc -pthread -o znake main.c apple.c canvas.c input.c znake.c
