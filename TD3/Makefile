#			Programmation Repartie (4I400)
#		Makefile pour TD 3. Signaux et processus


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
.PHONY: all clean test test-chaine_proc test-suspend test-stop_and_go
all: $(BIN)chaine_proc $(BIN)suspend $(BIN)stop_and_go 

test: test-chaine_proc test-suspend test-stop_and_go

test-chaine_proc: $(BIN)chaine_proc
	-$$PWD/bin/chaine_proc 10

test-suspend: $(BIN)suspend
	-$$PWD/bin/suspend 10

test-stop_and_go: $(BIN)stop_and_go
	-$$PWD/bin/stop_and_go 10

test-synchro_proc: $(BIN)synchro_proc
	-$$PWD/bin/synchro_proc

test-mon_petit_frere: $(BIN)mon_petit_frere
	-$$PWD/bin/mon_petit_frere


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
