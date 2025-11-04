CC=gcc
CFLAGS=-Wall

EXECUTABLES=info pinfo pmod finfo

SOURCES=$(addsuffix .c,$(EXECUTABLES))
OBJECTS=$(SOURCES:.c=.o)


all: $(EXECUTABLES)

# build each from its own .c file
%: %.c
	$(CC) $(CFLAGS) $< -o $@

# generate dependency files
%.o: %.c
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d

-include $(OBJECTS:.o=.d)

clean:
	rm -rf $(OBJECTS) $(EXECUTABLES) *.d