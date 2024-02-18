CC=gcc
COMP_NAME = testd
COMP_SRCS = main.c
COMP_OBJS = $(COMP_SRCS:.c=.o)
CFLAGS = -lcurl -lpthread 
#CFLAGS = -lcurl -lpthread -lcrypt -lssl -lcrypto -Wall -Wextra -pedantic -Wwrite-strings

all:$(COMP_NAME)

$(COMP_NAME): $(COMP_OBJS)
	$(CC) -o $@ $(COMP_OBJS) -pthread

$(COMP_OBJS):%.o:%.c
	$(CC) -c $(CFLAGS)  $< -o $@ 

#LIBS = -lcurl -lpthread -lcrypt
#test :main.o
#	$(CC) main.o -o test
#test:main.o func.o
#   $(cc) main.o func.o -o test
#func.o:func.o
#   $(cc) -c func.c
#main.o:main.cc
#   $(cc) -c main.cc
#main: main.c fun.c func.h
#   $(cc) -c main.c
#cc = gcc
#test: program.o main.o mian1.o
#    $(cc) program.o main.o mian1.o -o test
#program.o: program.c
#    $(cc) -c program.c


clean:
	rm -f *.o
	rm -f $(COMP_NAME)

