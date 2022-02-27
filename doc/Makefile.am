# Makefile for gperf/doc

# Copyright (C) 1998, 2000, 2002-2003, 2006-2007, 2012, 2016, 2022 Free Software Foundation, Inc.
# Written by Douglas C. Schmidt <schmidt@ics.uci.edu>
# and Bruno Haible <bruno@clisp.org>.
# Refactored by Reini Urban, 2022
#
# This file is part of GNU GPERF.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

SVG = run.svg gperf.svg size.svg
PNG = run.png gperf.png size.png
IMAGES = $(SVG)
dist_man1_MANS = gperf.1
EXTRA_DIST = $(IMAGES)

info_TEXINFOS = gperf.texi
#TEXINFOS_SOURCES = gperf.texi gpl-3.0.texi $(IMAGES)

CLEANFILES = gperf.pdf gperf.info gperf.info*

html-local : gperf.html
	cp $(SVG) gperf.html/
#
## We still prefer texi2html over texi2any because it includes the titlepage.
#
#gperf.html-local : $(srcdir)/gperf.texi $(srcdir)/gpl-3.0.texi $(IMAGES)
#	cd $(srcdir) && $(TEXI2HTML) -number -monolithic gperf.texi
##	cd $(srcdir) && $(TEXI2ANY) --html --no-headers --no-split gperf.texi
#	cd $(srcdir) && perl -pi -e's/\@image\{(\w+),\d+pt,,(.+),\.svg\}/<img src="\1.svg" alt="\2">/' \
#	  gperf.html gperf_6.html
#
#gperf_toc.html : $(srcdir)/gperf.texi $(srcdir)/gpl-3.0.texi
#	cd $(srcdir) && $(RM) gperf_*.html
#	cd $(srcdir) && $(TEXI2HTML) -number -split_chapter gperf.texi
#
#gperf_0.html : $(srcdir)/gperf.texi $(srcdir)/gpl-3.0.texi
#	cd $(srcdir) && $(TEXI2ANY) --html --no-headers --split=chapter --no-node-files -o . gperf.texi

man : $(dist_man1_MANS)

gperf.1 : $(top_srcdir)/src/options.cc
	./help2man --name='generate a perfect hash function from a key set' --section=1 $(top_srcdir)/src/gperf >$@
