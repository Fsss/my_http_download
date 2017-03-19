BINARY=$(patsubst %.c,$(ROOT)/bin/%.o,$(wildcard *.c))

all : $(BINARY)

$(ROOT)/bin/%.o : %.c
	@$(CC) -c $< -o $@ -g -I$(ROOT) -O2 -Wall


##test
#SRC = a.c b.c m.c.c

#.PHONY : test
#test :
#	@echo $(patsubst %.c,%.s,$(SRC))
#	@echo $(subst .c,.s,$(SRC))
