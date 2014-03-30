LOCAL_CFLAGS = -static -march=armv5 -O2

LOCAL_SRC_FILES = src/main.cpp src/functions.cpp src/helpers.cpp src/customizer.cpp \
		src/classes.cpp

LOCAL_CPP_INCLUDES = -Iinclude

all: src/main.cpp
	$(CC) -o dinfo $(LOCAL_SRC_FILES) $(LOCAL_CPP_INCLUDES) $(LOCAL_CFLAGS)

clean:
	rm -f dinfo dinfo.o