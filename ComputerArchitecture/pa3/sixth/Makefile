all: hello

hello: sixth.c
		gcc -Wall -Werror -fsanitize=address,undefined -g -lm sixth.c -o sixth


clean:
		rm -rf sixth *~