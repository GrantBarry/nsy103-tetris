CC=gcc
CFLAGS=-Wall

EXEC=./bin/gba_tetris
ROOTDIR=$(realpath .)
EXEC2=/test_server/server
SRC=$(filter-out ./src/ai_runner.c, $(wildcard ./src/*.c))
OBJ=$(SRC:./src%.c=./obj%.o)



all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ -lncurses


./obj/%.o: ./src/%.c ./src/%.h
	$(CC) -o $@ -c $< $(CFLAGS)


clean:
	rm $(EXEC)
	rm $(OBJ)

run:
	xterm $(ROOTDIR)$(EXEC2) &
	$(EXEC)

run1:
	$(EXEC) -h 1.0 -l -20.0 -e 10.0
#	$(EXEC) -s 127.0.0.1 -h 1.0 -l -20.0 -e 10.0
#	$(EXEC) -s 127.0.0.1 -h 1.0 -l -20.0 -e 10.0 -m

cplai: ./bin/ai_runner

./bin/ai_runner: ./src/ai_runner.c
	$(CC) -o $@ $<

runai:
	./bin/ai_runner
		
testt: 
	@echo "yo: $(ROOTDIR)"
	@echo "yo: $(SRC)"
	@echo "yo: $(EXEC)"
	@echo " "
