#			Programmation Repartie (4I400)
#		Makefile pour TD 1. Prise en main


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
.PHONY: all clean test test-nfork test-mon_frere
all: $(BIN)nfork $(BIN)mon_frere $(OBJ)exec_sleep.o $(OBJ)repeat_nfork.o

test: test-nfork test-mon_frere

test-nfork: $(BIN)nfork
	-$$PWD/bin/nfork

test-mycp: $(BIN)mycp
	-$$PWD/bin/mycp

test-mon_frere: $(BIN)mon_frere
	-$$PWD/bin/mon_frere

test-remonte: $(BIN)remonte
	-$$PWD/bin/remonte 8 aleas

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
