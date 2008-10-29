AAM_CFLAGS = -g -g3 -O2 -Wall -DVERSION=\"$(VERSION)\"

pidgin_cmdsdir = $(PIDGIN_INSTALL)

pidgin_cmds_LTLIBRARIES = \
	pidgin_grep.la    \
	pidgin_shout.la

pidgin_grep_la_CFLAGS =	$(pidgin_CFLAGS)
pidgin_grep_la_SOURCES = purple-grep.c
pidgin_grep_la_LDFLAGS =    \
	-module		    \
	-avoid-version	    \
	-L$(PIDGIN_INSTALL) \
	$(pidgin_LIBS)

pidgin_shout_la_CFLAGS = $(pidgin_CFLAGS)
pidgin_shout_la_SOURCES = purple-shout.c
pidgin_shout_la_LDFLAGS =   \
	-module             \
	-avoid-version	    \
	-L$(PIDGIN_INSTALL) \
	$(pidgin_LIBS)	
