# Makefile for gperf/src
AM_CXXFLAGS = -I. -I$(top_srcdir)/lib -I$(srcdir)
LDADD       = ../lib/libgp.a @GPERF_LIBM@

SOURCES = main.cc version.cc positions.cc options.cc keyword.cc	\
           keyword-list.cc input.cc bool-array.cc hash-table.cc	\
           search.cc output.cc nbperf-chm.cc nbperf-chm3.cc	\
           nbperf-bdz.cc graph2.cc graph3.cc mi_vector_hash.c
# These need to be included into generated MPH .c code */
HASHES   = mi_vector_hash.c wyhash3.h wyhash.h fnv3.h fnv.h crc3.h
gperf_SOURCES = $(SOURCES)
gperf_perf_SOURCES = $(SOURCES) perf.h
gperf_perf_CXXFLAGS = -DPERF $(CXXFLAGS) $(AM_CXXFLAGS)
EXTRA_DIST = $(HASHES) nbperf.h output.ic output.icc bool-array.icc	\
       keyword.icc keyword-list.icc options.icc output.icc		\
       positions.icc bool-array.h hash-table.h keyword.h options.h	\
       search.h config.h input.h keyword-list.h output.h version.h	\
       positions.h

bin_PROGRAMS  = gperf
EXTRA_PROGRAMS  = gperf_perf

output.ic: $(HASHES)
	$(XXD) --version && ( \
	echo "/* ex: set ro ft=c: -*- mode: c; buffer-read-only: t -*- */" >$@; \
	echo "/* C code of $(HASHES), generated via xxd */" >>$@; \
	for h in $(HASHES); do $(XXD) -i $$h >>$@; done )

#gperf_perf$(EXEEXT): main_perf.cc $(NONMAIN_SOURCES) Makefile
#	$(CXX) -DPERF $(CXXFLAGS) $(LDFLAGS) -o $@ main_perf.cc \
#	  $(NONMAIN_SOURCES) $(LIBS)
#CLEANFILES = gperf_perf$(EXEEXT)
