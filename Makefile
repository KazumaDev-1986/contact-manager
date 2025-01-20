APP := contact-manager
COMPILER := gcc
# SRC := $(wildcard src/*.c)
SRC := $(shell find src -name "*.c")
OBJFILES := $(SRC:.c=.o)
CFLAGS := -Wall -pedantic -g -std=c99
FILENAME := contact.data

.PHONY: clean cleanall

$(APP): $(OBJFILES)
	$(COMPILER) $^ -o $@

src/%.o: src/%.c
	$(COMPILER) $(CFLAGS) -c $< -o $@ 

clean:
	@-rm -f $(APP)

cleanall:
	@-rm -f $(APP)
	@-rm -f $(OBJFILES)
	# @-rm -f $(FILENAME)
