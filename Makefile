CC=g++
CFLAGS=--std=c++11 -g -lrt -lpthread -O3

TARGETS=alice bob

all: ${TARGETS}

%: %.cpp common.h
	${CC} ${CFLAGS} $< -o $@

clean:
	rm -f ${TARGETS}

