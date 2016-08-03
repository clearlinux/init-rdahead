CC=gcc
INSTALL_PATH?=/usr/local/bin
SMFLAGS=-s -Os -m32 -fno-unwind-tables -fno-ident -fmerge-all-constants \
	-fsingle-precision-constant -fshort-enums -ffunction-sections

initra:
	$(CC) -o initra init-rdahead.c -Wall

debug:
	$(CC) -o initra init-rdahead.c -Wall -DDEBUG

small:
	$(CC) -o initra init-rdahead.c -Wall $(SMFLAGS) -g
	strip -R .note -R .comment -R .eh_frame -R .eh_frame_hdr -s ./initra

smalldebug:
	$(CC) -o initra init-rdahead.c -Wall $(SMFLAGS) -DDEBUG
	strip -R .note -R .comment -R .eh_frame -R .eh_frame_hdr -s ./initra

install:
	cp initra $(INSTALL_PATH)

clean:
	rm initra
