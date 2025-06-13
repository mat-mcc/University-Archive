all: hello

hello: first.c
		gcc -Wall -Werror -fsanitize=address,undefined -g -lm first.c -o first


clean:
		rm -rf first *~