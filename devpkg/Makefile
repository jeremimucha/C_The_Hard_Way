# PREFIX?=C:/_clib
CFLAGS=-g -Wall -std=gnu11
# #CFLAGS+=-I${PREFIX}/apr/include/apr-util-1
# LDFLAGS=-L${PREFIX}/apr/lib -lapr-1 -pthread -laprutil-1

# all: devpkg

devpkg: bstrlib.o db.o shell.o commands.o

# install: all
# 	install -d $(DESTDIR)/$(PREFIX)/bin/
# 	install devpkg $(DESTDIR)/$(PREFIX)/bin/

# clean:
# 	rm -f *.o
# 	rm -f devpkg
# 	rm -rf *dSYM
