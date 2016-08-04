CC=gcc
MCC=musl-gcc
INSTALL_PATH?=/usr/local/bin
SMFLAGS=-s -Os -fno-unwind-tables -fno-ident -fmerge-all-constants \
	-fsingle-precision-constant -fshort-enums -ffunction-sections \
	-static

initra:
	$(CC) -o initra init-rdahead.c -Wall

debug:
	$(CC) -o initra init-rdahead.c -Wall -DDEBUG

small:
	$(CC) -o initra init-rdahead.c -Wall $(SMFLAGS) -g

smallmusl:
	$(MCC) -o initra init-rdahead.c -Wall $(SMFLAGS) -g

smalldebug:
	$(CC) -o initra init-rdahead.c -Wall $(SMFLAGS) -DDEBUG

install:
	cp initra $(INSTALL_PATH)

clean:
	rm initra
