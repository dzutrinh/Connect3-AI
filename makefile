prg=c3
source=$(prg).c
target=$(prg)
cc=gcc
cflags=--std=c99
lflags=-o $(target)

all: $(target)

$(target): $(source)
	$(cc) $(cflags) $(source) $(lflags)

clean:
	rm $(target)
