cthulhu: src/main.c
	cc src/main.c -o cthulhu -Wall -Werror -std=c99 -pedantic-errors

clean:
	rm cthulhu
