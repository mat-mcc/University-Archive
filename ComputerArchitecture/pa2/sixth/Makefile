all: hello

hello: sixth.c
		gcc -Wall -Werror -fsanitize=address,undefined -g sixth.c -o sixth


clean:
		rm -rf fifth *~