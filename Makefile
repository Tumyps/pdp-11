IDIR=
CC=gcc
CFLAGS=-I$(IDIR) -g
BIN=pdp.out


SDIR=
ODIR=


DEPS = mem.h run.h do_func.h 
#DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))


OBJ = main.o mem.o run.o do_func.o
#OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


all: $(BIN)


$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)


$(BIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


.PHONY: clean


clean:
	rm -f $(ODIR)/*.o $(SDIR)/*~ $(INCDIR)/*~