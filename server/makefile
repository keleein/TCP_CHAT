HEADER=-I./include
TARGET=./app/server
SRCDIR=./src
OBJDIR=./obj
SRC=$(wildcard ${SRCDIR}/*.c)
OBJ=$(patsubst ${SRCDIR}/%.c,${OBJDIR}/%.o,${SRC})
CMD=gcc
FLAG=-c -o
RM=rm -r
CLEAN=clean
DEL=delete

${TARGET}:${OBJ}
	${CMD} $^ -o $@
${OBJDIR}/%.o:${SRCDIR}/%.c
	${CMD} ${HEADER} ${FLAG} $@ $^
${CLEAN}:
	${RM} ${OBJDIR}/*
${DEL}:
	${RM} ${TARGET} ${OBJDIR}/*
