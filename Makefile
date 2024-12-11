CC=g++
CFLAGS=--std=c++11 -g

TARGETS=alice bob

all: ${TARGETS}

%: %.cpp common.h
	${CC} ${CFLAGS} $< -o $@

clean:
	rm -f ${TARGETS}
