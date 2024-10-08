
CC=gcc
CFLAGS=-std=c99 -Wall -Wextra -Wpedantic
LDFLAGS=

OBJ_FILES=main.c.o liblog.c.o
OBJS=$(addprefix obj/, $(OBJ_FILES))

BIN=liblog-test.out

#-------------------------------------------------------------------------------

.PHONY: clean all

all: $(BIN)

clean:
	rm -f $(BIN) $(OBJS)

#-------------------------------------------------------------------------------

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

obj/%.c.o : src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -o $@ -c $<
