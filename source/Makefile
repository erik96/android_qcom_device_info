CFLAGS = -static -march=armv5 -O2

all: main.cpp
	$(CC) -o arm main.cpp functions.cpp $(CFLAGS)

clean:
	rm -f arm arm.o
