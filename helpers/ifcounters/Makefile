CC?=
PREFIX?=/usr/local
CPPFLAGS=-I$(PREFIX)/include
CFLAGS=-Wall -Wextra -g -O2 -pipe -funroll-loops -ffast-math -fno-strict-aliasing
CFLAGS+=$(CPPFLAGS)
LDFLAGS=-L$(PREFIX)/lib
LDLIBS=-lm
RM?=rm -f

IFCOUNTERS = ifcounters
OBJ = ifcounters.o

all: $(IFCOUNTERS)

$(IFCOUNTERS): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $(IFCOUNTERS)

install: all
	install -s -C $(IFCOUNTERS) $(PREFIX)/bin

clean:
	$(RM) *.o *.a a.out core *.core temp.* $(IFCOUNTERS)
	$(RM) -r *.dSYM

