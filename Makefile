###########################################################
# CS480 Summer 2026
# Programming Assignment #2 - XSH
# Angela Lee (cssc3130)
# Caitlin Corpus (cssc3114)
# ###########################################################

EXEC = xsh
FILES = main.cpp shell.cpp pipe.cpp
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

