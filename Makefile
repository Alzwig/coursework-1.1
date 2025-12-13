TARGET = cw
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -Werror

PREF_SRC = src/
PREF_OBJ = build/

SRC = $(wildcard $(PREF_SRC)*.c)
OBJ = $(patsubst $(PREF_SRC)%.c, $(PREF_OBJ)%.o, $(SRC))

all: build $(TARGET)

build:
	mkdir -p $(PREF_OBJ)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

$(PREF_OBJ)%.o: $(PREF_SRC)%.c 
	$(CC) -c $< -o $@


clean:
	rm -f $(TARGET) $(PREF_OBJ)*.o