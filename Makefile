FLAGS = *.c

make : 
	gcc -Wall -Wextra -g -o a.out ${FLAGS} -lraylib -lm 
	./a.out
