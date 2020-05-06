
dist_doc_DATA = README.md
ACLOCAL_AMFLAGS = -Im4
AM_DEFAULT_SOURCE_EXT = .cpp
AM_CPPFLAGS = -I$(top_srcdir)

bin_PROGRAMS = wEE
wEE_SOURCES = wEE.cpp

wEE_CXXFLAGS = \
        -std=c++11 \
		-lxml2 \
        $(LIBXML2_CFLAGS)
		
wEE_LDADD = \
        $(LIBXML2_LIBS)
