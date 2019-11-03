INCDIR = ./include
SRCDIR = ./src
OBJDIR = ./obj
BINDIR = ./bin

SOURCE = $(wildcard ${SRCDIR}/*.cpp)
OBJECT = $(patsubst %.cpp,${OBJDIR}/%.o,$(notdir ${SOURCE}))

TARGET = ez-npd
BIN_TARG = ${BINDIR}/${TARGET}

CC = g++ 
CPPFLAGS = -fopenmp -g -Wall -O2 -std=c++11 -I${INCDIR} #-D_DEBUG

${BIN_TARG}:${OBJECT}
	$(CC) -fopenmp -o $@ ${OBJECT}

${OBJDIR}/%.o:${SRCDIR}/%.cpp
	$(CC) ${CPPFLAGS} -c $< -o $@

.PHONY:clean
clean:
	find ${OBJDIR} -name *.o -exec rm -rf {} \;
	rm -rf $(BIN_TARG)
