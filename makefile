OBJ = tftpc.o packetopt.o fileopt.o handlearg.o translate.o
CC = gcc
FLAGS = -g -Wall

test: $(OBJ)
	$(CC) $(OBJ) -o $@ $(FLAGS)
%.o:%.c
	$(CC) -c $^
clean:
	rm *.o test
