CFLAGS = -static -march=armv5 -O2

all: main.cpp
	$(CC) -o dinfo main.cpp functions.cpp helpers.cpp $(CFLAGS)

clean:
	rm -f dinfo dinfo.o
