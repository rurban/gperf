# Makefile for gperf/tests

# Copyright (C) 1989, 1992-1993, 1995, 1998, 2000, 2002-2004, 2007-2009, 2012, 2016, 2018, 2022 Free Software Foundation, Inc.
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

#### Start of system configuration section. ####

DIFF=@DIFF@
# The 2nd hunk only if GPERF is set. for testing an external gperf
# if EXT_GPERF
# RUN_DIFF = $(DIFF) -I 'code produced by gperf version' -I'Command-line:'
# RUN_GPERF = $(GPERF)
# else
RUN_DIFF = $(DIFF) -I 'code produced by gperf version'
RUN_GPERF = ../src/gperf$(EXXEXT)
# endif

#### End of system configuration section. ####


check : check-c check-ada check-modula3 check-pascal check-lang-utf8	\
	check-lang-ucs2 check-smtp check-test check-languages		\
	check-languages-S check-chm check-bpz
	@true

extracheck : @CHECK_LANG_SYNTAX@
	@true

../src/gperf_perf$(EXEEXT): ../src/main.cc
	$(MAKE) -C ../src gperf_perf$(EXEEXT)

perf$(EXEEXT): perf.cc perf.h perf_test.c ../src/gperf_perf
	$(CXX) $(CXXFLAGS) perf.cc -o perf$(EXEEXT)
run-perf: perf$(EXEEXT)
	./perf$(EXEEXT) && ./perf_img.sh

check-chm: check-c-chm check-languages-chm check-languages-chm3
check-bpz: check-c-bpz check-languages-bpz

check-c: test.$(OBJEXT)
	@echo "testing ANSI C reserved words, all items should be found in the set"
	$(RUN_GPERF) -c -l -S1 -I -o $(srcdir)/c.gperf > cinset.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o cout cinset.c test.$(OBJEXT)
	./cout -v < $(srcdir)/c.gperf | LC_ALL=C tr -d '\r' > c.out
	$(RUN_DIFF) $(srcdir)/c.exp c.out
check-c-chm: test.$(OBJEXT)
	$(RUN_GPERF) --chm -I < $(srcdir)/c.gperf > c2.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o cout2 c2.c test.$(OBJEXT)
	@echo "testing languages with chm, all items should be found in the set"
	./cout2 $(srcdir)/c.gperf
check-c-bpz: test.$(OBJEXT)
	$(RUN_GPERF) --bpz -I < $(srcdir)/c.gperf > c4.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o cout4 c4.c test.$(OBJEXT)
	@echo "testing languages with bpz, all items should be found in the set"
	./cout4 $(srcdir)/c.gperf

check-ada: test.$(OBJEXT)
	$(RUN_GPERF) -k1,4,'$$' -I $(srcdir)/ada.gperf > adainset.c
# double '$$' is only there since make gets confused; program wants only 1 '$'
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o aout adainset.c test.$(OBJEXT)
	@echo "testing Ada reserved words, all items should be found in the set"
	./aout -v < $(srcdir)/ada.gperf | LC_ALL=C tr -d '\r' > ada-res.out
	$(RUN_DIFF) $(srcdir)/ada-res.exp ada-res.out
	$(RUN_GPERF) -D -k1,'$$' -s 2 -I -o $(srcdir)/adadefs.gperf > preinset.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o preout preinset.c test.$(OBJEXT)
	@echo "testing Ada predefined words, all items should be found in the set"
	./preout -v < $(srcdir)/adadefs.gperf | LC_ALL=C tr -d '\r' > ada-pred.out
	$(RUN_DIFF) $(srcdir)/ada-pred.exp ada-pred.out

check-modula3: test.$(OBJEXT)
	$(RUN_GPERF) -k1,2,'$$' -I -o $(srcdir)/modula3.gperf > m3inset.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o m3out m3inset.c test.$(OBJEXT)
	@echo "testing Modula3 reserved words, all items should be found in the set"
	./m3out -v < $(srcdir)/modula3.gperf | LC_ALL=C tr -d '\r' > modula.out
	$(RUN_DIFF) $(srcdir)/modula.exp modula.out

check-pascal: test.$(OBJEXT)
	$(RUN_GPERF) -o -S2 -I < $(srcdir)/pascal.gperf > pinset.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o pout pinset.c test.$(OBJEXT)
	@echo "testing Pascal reserved words, all items should be found in the set"
	./pout -v < $(srcdir)/pascal.gperf | LC_ALL=C tr -d '\r' > pascal.out
	$(RUN_DIFF) $(srcdir)/pascal.exp pascal.out

check-languages: test1.$(OBJEXT)
	$(RUN_GPERF) -I < $(srcdir)/languages.gperf > languages0.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o lout0 languages0.c test1.$(OBJEXT)
	@echo "testing 685 languages, all items should be found in the set"
	./lout0 $(srcdir)/languages.gperf

check-languages-S: test1.$(OBJEXT)
	$(RUN_GPERF) -S 2 -I < $(srcdir)/languages.gperf > languages1.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o lout1 languages1.c test1.$(OBJEXT)
	@echo "testing languages with --switch 2, all items should be found in the set"
	./lout1 $(srcdir)/languages.gperf

check-languages-chm: test1.$(OBJEXT)
	$(RUN_GPERF) --chm -I < $(srcdir)/languages.gperf > languages2.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o lout2 languages2.c test1.$(OBJEXT)
	@echo "testing languages with chm, all items should be found in the set"
	./lout2 $(srcdir)/languages.gperf

check-languages-chm3: test1.$(OBJEXT)
	$(RUN_GPERF) --chm3 -I < $(srcdir)/languages.gperf > languages3.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o lout3 languages3.c test1.$(OBJEXT)
	@echo "testing languages with chm3, all items should be found in the set"
	./lout3 $(srcdir)/languages.gperf

check-languages-bpz: test.$(OBJEXT)
	$(RUN_GPERF) --bpz -I < $(srcdir)/languages.gperf > languages4.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o lout4 languages4.c test1.$(OBJEXT)
	@echo "testing languages with bpz, all items should be found in the set"
	./lout4 $(srcdir)/languages.gperf

# check for 8-bit cleanliness
check-lang-utf8: test1.$(OBJEXT)
	$(RUN_GPERF) -k1 -t -I -K foreign_name < $(srcdir)/lang-utf8.gperf > lu8inset.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o lu8out lu8inset.c test1.$(OBJEXT)
	@echo "testing UTF-8 encoded languages, all items should be found in the set"
	./lu8out -v $(srcdir)/lang-utf8.gperf | LC_ALL=C tr -d '\r' > lang-utf8.out
	$(RUN_DIFF) $(srcdir)/lang-utf8.exp lang-utf8.out

test.$(OBJEXT) : $(srcdir)/test.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(srcdir)/test.c

test1.$(OBJEXT) : $(srcdir)/test1.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(srcdir)/test1.c

# check for binary keywords with NUL bytes
check-lang-ucs2: test2.$(OBJEXT)
	$(RUN_GPERF) -k4 -t -l -I -K foreign_name < $(srcdir)/lang-ucs2.gperf > lu2inset.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o lu2out lu2inset.c test2.$(OBJEXT)
	@echo "testing UCS-2 encoded languages, all items should be found in the set"
	./lu2out -v < $(srcdir)/lang-ucs2.in | LC_ALL=C tr -d '\r' > lang-ucs2.out
	$(RUN_DIFF) $(srcdir)/lang-ucs2.exp lang-ucs2.out

test2.$(OBJEXT) : $(srcdir)/test2.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $(srcdir)/test2.c

# check case-insensitive lookup
check-smtp:
	@echo "testing SMTP keywords, case-insensitive"
	$(RUN_GPERF) --struct-type --readonly-table --enum --global -K field_name -N header_entry --ignore-case $(srcdir)/smtp.gperf > smtp.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o smtp smtp.c
	./smtp
	$(RUN_GPERF) --struct-type --readonly-table --enum --global -K field_name -N header_entry --ignore-case --compare-strncmp $(srcdir)/smtp.gperf > smtp.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o smtp smtp.c
	./smtp
	$(RUN_GPERF) --struct-type --readonly-table --enum --global -K field_name -N header_entry --ignore-case --compare-lengths $(srcdir)/smtp.gperf > smtp.c
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) -o smtp smtp.c
	./smtp

# these next 5 are demos that show off the generated code
POSTPROCESS_FOR_MINGW = LC_ALL=C tr -d '\r' | LC_ALL=C sed -e 's|[^ ]*[/\\][\\]*src[/\\][\\]*gperf[^ ]*|../src/gperf|'
check-test: check-ada
	$(RUN_GPERF) -L C -F ', 0, 0' -j1 -i 1 -g -o -t -G -N is_reserved_word -k1,3,'$$' < $(srcdir)/c-parse.gperf | $(POSTPROCESS_FOR_MINGW) > c-parse.out
	$(RUN_DIFF) $(srcdir)/c-parse.exp c-parse.out
	$(RUN_GPERF) -j1 -i 1 -g -o -t -N is_reserved_word -k1,3,'$$' < $(srcdir)/objc.gperf | $(POSTPROCESS_FOR_MINGW) > objc.out
	$(RUN_DIFF) $(srcdir)/objc.exp objc.out
	$(RUN_GPERF) -L C -F ', 0, 0, 0' -D -E -S1 -j1 -i 1 -g -o -t -k'*' < $(srcdir)/chill.gperf | $(POSTPROCESS_FOR_MINGW) > chill.out
	$(RUN_DIFF) $(srcdir)/chill.exp chill.out
	$(RUN_GPERF) -L C -F ', 0, 0' -j1 -g -o -t -N is_reserved_word -k1,4,7,'$$' < $(srcdir)/cplusplus.gperf | $(POSTPROCESS_FOR_MINGW) > cplusplus.out
	$(RUN_DIFF) $(srcdir)/cplusplus.exp cplusplus.out
	$(RUN_GPERF) -L C -F ', 0' -t -j1 -i 1 -g -o -N java_keyword -k1,3,'$$' < $(srcdir)/java.gperf | $(POSTPROCESS_FOR_MINGW) > java.out
	$(RUN_DIFF) $(srcdir)/java.exp java.out
	$(RUN_GPERF) -n -k1-8 -l < $(srcdir)/modula2.gperf | $(POSTPROCESS_FOR_MINGW) > modula2.out
	$(RUN_DIFF) $(srcdir)/modula2.exp modula2.out
	$(RUN_GPERF) -D -t -k1,'$$' < $(srcdir)/c-parse.gperf | $(POSTPROCESS_FOR_MINGW) > test-4.out
	$(RUN_DIFF) $(srcdir)/test-4.exp test-4.out
	$(RUN_GPERF) -g -o -j1 -t -N is_reserved_word < $(srcdir)/gpc.gperf | $(POSTPROCESS_FOR_MINGW) > gpc.out
	$(RUN_DIFF) $(srcdir)/gpc.exp gpc.out
	$(RUN_GPERF) -m5 < $(srcdir)/permut2.gperf | $(POSTPROCESS_FOR_MINGW) > permut2.out
	$(RUN_DIFF) $(srcdir)/permut2.exp permut2.out
	$(RUN_GPERF) -m5 < $(srcdir)/permut3.gperf | $(POSTPROCESS_FOR_MINGW) > permut3.out
	$(RUN_DIFF) $(srcdir)/permut3.exp permut3.out
	$(RUN_GPERF) -m5 --ignore-case < $(srcdir)/permutc2.gperf | $(POSTPROCESS_FOR_MINGW) > permutc2.out
	$(RUN_DIFF) $(srcdir)/permutc2.exp permutc2.out
	$(RUN_GPERF) -C -E -G -I -t < $(srcdir)/charsets.gperf | $(POSTPROCESS_FOR_MINGW) > charsets.out
	$(RUN_DIFF) $(srcdir)/charsets.exp charsets.out
	$(RUN_GPERF) -C -E -G -I -t < $(srcdir)/languages.gperf | $(POSTPROCESS_FOR_MINGW) > languages.out
	$(RUN_DIFF) $(srcdir)/languages.exp languages.out
	$(RUN_GPERF) -t < $(srcdir)/incomplete.gperf | $(POSTPROCESS_FOR_MINGW) > incomplete.out
	$(RUN_DIFF) $(srcdir)/incomplete.exp incomplete.out
# prints out the help message
	-$(RUN_GPERF) -h | $(POSTPROCESS_FOR_MINGW) > test-6.out
	$(RUN_DIFF) $(srcdir)/test-6.exp test-6.out
	@echo "only if, do, for, case, goto, else, while, and return should be found "
	./aout -v < $(srcdir)/c.gperf | $(POSTPROCESS_FOR_MINGW) > test-7.out
	$(RUN_DIFF) $(srcdir)/test-7.exp test-7.out

# The following validates valid language syntax with different parameters.
# Works only with gcc and g++, and only on platforms where "gcc -ansi" is
# usable. (There are still platforms where gcc-2.8.0's fixincludes does not
# work well enough.)

VALIDATE = CC='$(CC)' CFLAGS='$(CFLAGS)' CXX='$(CXX)' CXXFLAGS='$(CXXFLAGS)' CPPFLAGS='$(CPPFLAGS)' GPERF='$(RUN_GPERF)' $(srcdir)/validate

force:

check-lang-syntax : force
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -c
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -C
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -E
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -G
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -G -C
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -G -E
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -l
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -D
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k2   $(srcdir)/jstest1.gperf -D
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -D -l
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k2   $(srcdir)/jstest1.gperf -D -l
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -S 10
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -S 10 -c
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -S 10 -C
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -S 10 -E
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -S 10 -G
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -S 10 -l
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -S 10 -D
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k2   $(srcdir)/jstest1.gperf -S 10 -D
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -S 10 -D -l
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k2   $(srcdir)/jstest1.gperf -S 10 -D -l
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -S 1000
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -P
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -P -c
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -P -C
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -P -E
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -P -G
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -P -G -C
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -P -G -E
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -P -l
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -P -D
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k2   $(srcdir)/jstest1.gperf -P -D
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -P -D -l
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k2   $(srcdir)/jstest1.gperf -P -D -l
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -P -S 10
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -P -S 10 -c
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -P -S 10 -C
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -P -S 10 -E
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -P -S 10 -G
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -P -S 10 -l
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -P -S 10 -D
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k2   $(srcdir)/jstest1.gperf -P -S 10 -D
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -P -S 10 -D -l
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k2   $(srcdir)/jstest1.gperf -P -S 10 -D -l
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -P -S 1000
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -P -Q auxstrings
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -P -Q auxstrings -S 10
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -K key_name
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -H hash_function_name
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -W word_list_name
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf -l --length-table-name=length_table_name
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf --chm
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf --chm -r
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf --chm -rf
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf --chm -rf -u 3
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf --chm3
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf --chm3 -r
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf --chm3 -rf
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf --chm3 -rf -u 3
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf --bpz
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf --bpz -r
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf --bpz -rf
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest1.gperf --bpz -rf -u 3
	sed -e 's,in_word_set,lookup_function_name,g' < $(srcdir)/jstest1.gperf > tmp-jstest1.gperf && \
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 tmp-jstest1.gperf -N lookup_function_name
	sed -e 's,Perfect_Hash,class_name,g' < $(srcdir)/jstest1.gperf > tmp-jstest1.gperf && \
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 tmp-jstest1.gperf -Z class_name
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest2.gperf -t
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest2.gperf -t -c
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest2.gperf -t -C
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest2.gperf -t -E
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest2.gperf -t -G
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest2.gperf -t -G -C
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest2.gperf -t -G -E
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest2.gperf -t -l
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest2.gperf -t -D
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k2   $(srcdir)/jstest2.gperf -t -D
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest2.gperf -t -D -l
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k2   $(srcdir)/jstest2.gperf -t -D -l
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest2.gperf -t -S 10
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest2.gperf -t -S 10 -c
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest2.gperf -t -S 10 -C
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest2.gperf -t -S 10 -E
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest2.gperf -t -S 10 -G
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest2.gperf -t -S 10 -l
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest2.gperf -t -S 10 -D
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k2   $(srcdir)/jstest2.gperf -t -S 10 -D
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest2.gperf -t -S 10 -D -l
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k2   $(srcdir)/jstest2.gperf -t -S 10 -D -l
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest2.gperf -t -S 1000
	sed -e 's,name,key_name,g' < $(srcdir)/jstest2.gperf > tmp-jstest2.gperf && \
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 tmp-jstest2.gperf -t -K key_name
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 $(srcdir)/jstest2.gperf -t -H hash_function_name
	sed -e 's,in_word_set,lookup_function_name,g' < $(srcdir)/jstest2.gperf > tmp-jstest2.gperf && \
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 tmp-jstest2.gperf -t -N lookup_function_name
	sed -e 's,Perfect_Hash,class_name,g' < $(srcdir)/jstest2.gperf > tmp-jstest2.gperf && \
	$(VALIDATE) KR-C,C,ANSI-C,C++ -k1,2 tmp-jstest2.gperf -t -Z class_name
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest3.gperf -t
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest3.gperf -t -c
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest3.gperf -t -C
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest3.gperf -t -E
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest3.gperf -t -G
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest3.gperf -t -G -C
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest3.gperf -t -G -E
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest3.gperf -t -l
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest3.gperf -t -D
	$(VALIDATE) C,ANSI-C,C++ -k2   $(srcdir)/jstest3.gperf -t -D
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest3.gperf -t -D -l
	$(VALIDATE) C,ANSI-C,C++ -k2   $(srcdir)/jstest3.gperf -t -D -l
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest3.gperf -t -S 10
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest3.gperf -t -S 10 -c
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest3.gperf -t -S 10 -C
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest3.gperf -t -S 10 -E
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest3.gperf -t -S 10 -G
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest3.gperf -t -S 10 -l
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest3.gperf -t -S 10 -D
	$(VALIDATE) C,ANSI-C,C++ -k2   $(srcdir)/jstest3.gperf -t -S 10 -D
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest3.gperf -t -S 10 -D -l
	$(VALIDATE) C,ANSI-C,C++ -k2   $(srcdir)/jstest3.gperf -t -S 10 -D -l
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest3.gperf -t -S 1000
	sed -e 's,name,key_name,g' < $(srcdir)/jstest3.gperf > tmp-jstest3.gperf && \
	$(VALIDATE) C,ANSI-C,C++ -k1,2 tmp-jstest3.gperf -t -K key_name
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest3.gperf -t -H hash_function_name
	sed -e 's,in_word_set,lookup_function_name,g' < $(srcdir)/jstest3.gperf > tmp-jstest3.gperf && \
	$(VALIDATE) C,ANSI-C,C++ -k1,2 tmp-jstest3.gperf -t -N lookup_function_name
	sed -e 's,Perfect_Hash,class_name,g' < $(srcdir)/jstest3.gperf > tmp-jstest3.gperf && \
	$(VALIDATE) C,ANSI-C,C++ -k1,2 tmp-jstest3.gperf -t -Z class_name
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest4.gperf -t -P
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest4.gperf -t -P -c
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest4.gperf -t -P -C
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest4.gperf -t -P -E
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest4.gperf -t -P -G
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest4.gperf -t -P -G -C
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest4.gperf -t -P -G -E
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest4.gperf -t -P -l
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest4.gperf -t -P -D
	$(VALIDATE) C,ANSI-C,C++ -k2   $(srcdir)/jstest4.gperf -t -P -D
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest4.gperf -t -P -D -l
	$(VALIDATE) C,ANSI-C,C++ -k2   $(srcdir)/jstest4.gperf -t -P -D -l
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest4.gperf -t -P -S 10
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest4.gperf -t -P -S 10 -c
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest4.gperf -t -P -S 10 -C
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest4.gperf -t -P -S 10 -E
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest4.gperf -t -P -S 10 -G
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest4.gperf -t -P -S 10 -l
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest4.gperf -t -P -S 10 -D
	$(VALIDATE) C,ANSI-C,C++ -k2   $(srcdir)/jstest4.gperf -t -P -S 10 -D
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest4.gperf -t -P -S 10 -D -l
	$(VALIDATE) C,ANSI-C,C++ -k2   $(srcdir)/jstest4.gperf -t -P -S 10 -D -l
	$(VALIDATE) C,ANSI-C,C++ -k1,2 $(srcdir)/jstest4.gperf -t -P -S 1000
	sed -e 's,stringpool,auxstrings,g' < $(srcdir)/jstest4.gperf > tmp-jstest4.gperf && \
	$(VALIDATE) C,ANSI-C,C++ -k1,2 tmp-jstest4.gperf -t -P -Q auxstrings
	sed -e 's,stringpool,auxstrings,g' < $(srcdir)/jstest4.gperf > tmp-jstest4.gperf && \
	$(VALIDATE) C,ANSI-C,C++ -k1,2 tmp-jstest4.gperf -t -P -Q auxstrings -S 10

CLEANFILES = *.$(OBJEXT) core *inset.c output.* *.out \
	      lout*$(EXEEXT) languages*.c c2.c c4.c cout*$(EXEEXT) \
	      aout$(EXEEXT) aout$(EXEEXT).manifest \
	      cout$(EXEEXT) cout$(EXEEXT).manifest \
	      lu2out$(EXEEXT) lu2out$(EXEEXT).manifest \
	      lu8out$(EXEEXT) lu8out$(EXEEXT).manifest \
	      m3out$(EXEEXT) m3out$(EXEEXT).manifest \
	      pout$(EXEEXT) pout$(EXEEXT).manifest \
	      preout$(EXEEXT) preout$(EXEEXT).manifest \
	      smtp.c smtp$(EXEEXT) smtp$(EXEEXT).manifest \
	      tmp-* valitest*
clean-local:
	rm -rf *.dSYM

# List of source files.
SOURCE_FILES = \
  configure.ac Makefile.am \
  test.c \
  c.gperf c.exp \
  ada.gperf ada-res.exp adadefs.gperf ada-pred.exp \
  modula3.gperf modula.exp \
  pascal.gperf pascal.exp \
  lang-utf8.gperf lang-utf8.exp \
  lang-ucs2.gperf lang-ucs2.in lang-ucs2.exp test2.c \
  smtp.gperf \
  c-parse.gperf c-parse.exp \
  objc.gperf objc.exp \
  chill.gperf chill.exp \
  cplusplus.gperf cplusplus.exp \
  java.gperf java.exp \
  modula2.gperf modula2.exp \
  test-4.exp \
  gpc.gperf gpc.exp \
  permut2.gperf permut2.exp \
  permut3.gperf permut3.exp \
  permutc2.gperf permutc2.exp \
  charsets.gperf charsets.exp \
  languages.gperf languages.exp \
  incomplete.gperf incomplete.exp \
  test-6.exp \
  test-7.exp \
  validate \
  jstest1.gperf \
  jstest2.gperf \
  jstest3.gperf \
  jstest4.gperf \
  c++.gperf irc.gperf jscript.gperf makeinfo.gperf
# List of distributed files imported from other packages.
IMPORTED_FILES =
# List of distributed files generated by autotools or Makefile.devel.
GENERATED_FILES = \
  configure
# List of distributed files generated by "make".
DISTRIBUTED_BUILT_FILES =
# List of distributed files.
EXTRA_DIST = $(SOURCE_FILES) $(IMPORTED_FILES) $(GENERATED_FILES) $(DISTRIBUTED_BUILT_FILES)
