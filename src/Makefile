CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror
OBJS = main.o utils.o word.o sentence.o text.o primary_processing.o print_text.o option_1.o option_2.o option_3.o option_4.o

all: cw

cw: $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o cw

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf *.o cw