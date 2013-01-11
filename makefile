BIN=./bin/
SRC=./src/
OBJ=./obj/

SOURCES=main.c game.c board.c block.c net.c ai.c
BINARY=gba_tetris

CFILES=$(addprefix $(SRC),$(SOURCES))
BINFILE=$(addprefix $(BIN),$(BINARY))

all: compile run

compile:
	gcc -o $(BINFILE) $(CFILES) -lncurses

clean:
	rm $(BINFILE)

run:
	$(BINFILE)
