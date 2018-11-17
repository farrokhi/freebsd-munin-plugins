CC?=
PREFIX?=/usr/local
CPPFLAGS=-I$(PREFIX)/include
CFLAGS=-Wall -Wextra -g -O2 -pipe -funroll-loops -ffast-math -fno-strict-aliasing
CFLAGS+=$(CPPFLAGS)
LDFLAGS=-L$(PREFIX)/lib
LDLIBS=-lm
RM?=rm -f

CPUSTAT = cpustat
OBJ = cpustat.o

all: $(CPUSTAT)

$(CPUSTAT): $(OBJ)
	$(CC) $(LDFLAGS) $(OBJ) $(LDLIBS) -o $(CPUSTAT)

install: all
	install -s -C $(CPUSTAT) $(PREFIX)/bin

clean:
	$(RM) *.o *.a a.out core temp.* $(CPUSTAT)
	$(RM) -r *.dSYM

