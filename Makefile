CC=gcc
CFLAGS=-g -Wall
LIB=-lapue -L/home/huxinyu/bin/
OBJ1=simple_sig10-2
OBJ2=
PROG=
OUT_OPT=-o
all: ${OBJ1} ${OBJ2}

%: %.c
	${CC} ${CFLAGS} $< ${OUT_OPT} $@ ${LIB}

.PHONY: clean
clean:
	rm -f ${OBJ1}
	rm -f ${OBJ2}
