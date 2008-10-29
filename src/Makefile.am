AAM_CFLAGS = -g -g3 -O2 -Wall -DVERSION=\"$(VERSION)\"

purple_cmdsdir = $(PURPLE_INSTALL)

purple_cmds_LTLIBRARIES = \
	purple_grep.la    \
	purple_shout.la

purple_grep_la_CFLAGS =	$(purple_CFLAGS)
purple_grep_la_SOURCES = purple-grep.c
purple_grep_la_LDFLAGS =    \
	-module		    \
	-avoid-version	    \
	-L$(PURPLE_INSTALL) \
	$(purple_LIBS)

purple_shout_la_CFLAGS = $(purple_CFLAGS)
purple_shout_la_SOURCES = purple-shout.c
purple_shout_la_LDFLAGS =   \
	-module             \
	-avoid-version	    \
	-L$(PURPLE_INSTALL) \
	$(purple_LIBS)	
