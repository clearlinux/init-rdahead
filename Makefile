CC=gcc
INSTALL_PATH?=/usr/local/bin
STFLAGS=-s -Os -m32 -fno-unwind-tables -fno-ident -fmerge-all-constants \
	-fsingle-precision-constant -fshort-enums -ffunction-sections \
	-static

initra:
	$(CC) -o initra init-rdahead.c -Wall

debug:
	$(CC) -o initra init-rdahead.c -Wall -DDEBUG

static:
	$(CC) -o initra init-rdahead.c -Wall $(STFLAGS) -g
	strip -R .note -R .comment -R .eh_frame -R .eh_frame_hdr -s ./initra

staticdebug:
	$(CC) -o initra init-rdahead.c -Wall $(STFLAGS) -DDEBUG
	strip -R .note -R .comment -R .eh_frame -R .eh_frame_hdr -s ./initra

install:
	cp initra $(INSTALL_PATH)

clean:
	rm initra
