CFLAGS=-O3
LIBS=-lroot -lbe -lscreensaver
CC=g++
OBJS = Symetrie.o fbview.o Render.o

all: SymetrieSaver

SymetrieSaver: $(OBJS)
	$(CC) -shared -Xlinker -soname=SymetrieSaver -o SymetrieSaver $^ $(LIBS)
	xres -o SymetrieSaver SymetrieSaver.rsrc
	
.cpp.o:
	$(CC) $(CFLAGS) -c $^

clean:
	rm -f SymetrieSaver $(OBJS)
