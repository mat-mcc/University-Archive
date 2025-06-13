all: hello

hello: fourth.c
		gcc -Wall -Werror -fsanitize=address,undefined -g fourth.c -o fourth


clean:
		rm -rf fourth *~