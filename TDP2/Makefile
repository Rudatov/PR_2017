#			Programmation Repartie (4I400)
#		Makefile pour TM 2. Toujours des fichiers


# Documentation: http://www.gnu.org/software/make/manual/make.html
CC =gcc
LDFLAGS =
CFLAGS =-W -Wall -ansi -pedantic -Iinclude -std=c11

DIR=.
BIN=$(DIR)/bin/
OBJ=$(DIR)/obj/
INCLUDE=$(DIR)/include/
LIB=$(DIR)/lib/
SRC=$(DIR)/src/

HC=

.SUFFIXES:
.PHONY: all clean test test-extended-grep test-inverser-fichier test-inverser-pread
all: $(BIN)extended-grep $(BIN)inverser-fichier $(BIN)inverser-pread $(OBJ)liste-rep.o

test: test-extended-grep test-inverser-fichier test-inverser-pread

test-memefichier: $(BIN)memefichier   	
	-$$PWD/bin/memefichier $(PWD)/src/memefichier.c $(PWD)/src/../src/memefichier.c

test-droitsfichier: $(BIN)droitsfichier
	-$$PWD/bin/droitsfichier c Makefile W

test-liste-rep: $(BIN)liste-rep
	-$$PWD/bin/liste-rep

test-rediriger: $(BIN)rediriger
	-$$PWD/bin/rediriger texte.txt toi a moi de jouer

test-extended-grep: $(BIN)extended-grep
	-bin/extended-grep if src

test-inverser-fichier: $(BIN)inverser-fichier
	-echo > t1.txt; echo "portsalut" >> t1.txt ; bin/inverser-fichier t1.txt 1t.txt; cat 1t.txt

test-inverser-pread: $(BIN)inverser-pread
	-echo > t2.txt; echo "portsalut" >> t2.txt ; bin/inverser-fichier t2.txt 2t.txt; cat 2t.txt


$(BIN)%: $(OBJ)%.o
	@if [ -d $(BIN) ]; then : ; else mkdir $(BIN); fi
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJ)%.o: $(SRC)%.c $(HC)
	@if [ -d $(OBJ) ]; then : ; else mkdir $(OBJ); fi
	$(CC) $(CFLAGS) -o $@ -c $<

$(OBJ)%.o: $(LIB)%.c $(HC)
	@if [ -d $(OBJ) ]; then : ; else mkdir $(OBJ); fi
	$(CC) $(CFLAGS) -o $@ -c $<

$(INCLUDE)%.h:
	@if [ -d $(INCLUDE) ]; then : ; else mkdir $(INCLUDE); fi

clean: 
	rm $(OBJ)*.o $(BIN)*
