LOCAL_CFLAGS = -static -march=armv5 -std=c++11 -O2

LOCAL_SRC_FILES = src/main.cpp src/functions.cpp src/helpers.cpp src/customizer.cpp \
		src/classes.cpp src/time_in_state.cpp

LOCAL_CPP_INCLUDES = -Iinclude

all: src/main.cpp
	$(CC) -o dinfo $(LOCAL_SRC_FILES) $(LOCAL_CPP_INCLUDES) $(LOCAL_CFLAGS)

clean:
	rm -f dinfo dinfo.o
