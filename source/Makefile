CFLAGS = -static -march=armv5 -O2

SRC_FILES = main.cpp functions.cpp helpers.cpp customizer.cpp \
		classes.cpp


all: main.cpp
	$(CC) -o dinfo $(SRC_FILES) $(CFLAGS)

clean:
	rm -f dinfo dinfo.o
