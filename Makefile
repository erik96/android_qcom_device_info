CFLAGS = -static -march=armv5

all: main.cpp
	$(CC) -o arm main.cpp functions.cpp $(CFLAGS)

clean:
	rm -f arm arm.o
