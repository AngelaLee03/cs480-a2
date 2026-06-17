###########################################################
# CS480 Assignment #2
# # Experimental Shell (XSH)
# ###########################################################

EXEC = xsh
FILES = main.cpp shell.cpp
CC = g++
CFLAGS = -c

OBJECTS = $(FILES:.cpp=.o)

$(EXEC): $(OBJECTS)
	$(CC) -o $(EXEC) $(OBJECTS)

.cpp.o:
	$(CC) $(CFLAGS) $<

clean:
	rm -f *.o $(EXEC)

#######################[ EOF: Makefile ]###################

