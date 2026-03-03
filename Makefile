CC=gcc
CFLAGS=-O2 -Wall
SRC=main.c confpars.c
OUT=build/poshta

all: $(OUT)

$(OUT): $(SRC) | build
	$(CC) $(CFLAGS) -o $@ $(SRC)

build:
	mkdir -p build

clean:
	rm -f $(OUT)