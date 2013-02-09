BIN=./bin/
SRC=./src/
OBJ=./obj/

SOURCES=main.c game.c board.c block.c net.c ai.c
BINARY=tetris_client

CFILES=$(addprefix $(SRC),$(SOURCES))
BINFILE=$(addprefix $(BIN),$(BINARY))

all: clean compile run

compile:
	mkdir -p $(BIN)
	gcc -o $(BINFILE) $(CFILES) -lncurses

clean:
	rm -f $(BINFILE)

run:
	$(BINFILE)
