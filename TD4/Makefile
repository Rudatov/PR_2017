#			Programmation Repartie (4I400)
#		Makefile pour TD 4.  Pipes et tubes


# Documentation: http://www.gnu.org/software/make/manual/make.html
CC =gcc
LDFLAGS = -lpthread
CFLAGS =-W -Wall -ansi -pedantic -Iinclude -std=c11 -g

DIR=.
BIN=$(DIR)/bin/
OBJ=$(DIR)/obj/
INCLUDE=$(DIR)/include/
LIB=$(DIR)/lib/
SRC=$(DIR)/src/

HC=

.SUFFIXES:
.PHONY: all clean test test-pipe_maj test-serveur_maj test-client_maj
all: $(BIN)pipe_maj $(BIN)serveur_maj $(BIN)client_maj 

test: test-pipe_maj test-serveur_maj test-client_maj service

test-pipe_maj: $(BIN)pipe_maj
	-echo abcd.ext | $$PWD/bin/pipe_maj

test-serveur_maj: $(BIN)serveur_maj
	-$$PWD/bin/serveur_maj minmaj &

test-client_maj: $(BIN)client_maj
	-$$PWD/bin/client_maj minmaj

test-thread_create: $(BIN)thread_create
	-$$PWD/bin/thread_create 10

test-thread_rand: $(BIN)thread_rand
	-$$PWD/bin/thread_rand 10

test-thread_wait: $(BIN)thread_wait
	-$$PWD/bin/thread_wait 10

test-thread_detach: $(BIN)thread_detach
	-$$PWD/bin/thread_detach 10

test-thread_broadcast:$(BIN)thread_broadcast
	-$$PWD/bin/thread_broadcast 10

service: $(BIN)service

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
