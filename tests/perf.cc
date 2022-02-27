/* Copyright (C) 2022 Free Software Foundation, Inc.
   Written by Reini Urban, 2022

   This file is part of GNU GPERF.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

#include <cstddef>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include "perf.h"
#include <sys/stat.h>
#include <vector>
#include <string>
#include <climits>
using namespace std;

#ifndef WORDS
#define WORDS "/usr/share/dict/words"
#endif

#define PERF_PRE "_perf_set"
static char perf_in[64] = PERF_PRE "2000000.gperf";
static char perf_c[64] = PERF_PRE "2000000.c";
static char perf_exe[64] = PERF_PRE "2000000";

#define PICK(n) ((unsigned)rand()) % (n)
char buf[128];

static size_t random_word(char *buf, const size_t buflen) {
  const char* const alpha =
    "abcdefeghijklmnopqrstuvwxyz0123456789_ABCDEFEGHIJKLMNOPQRSTUVWXYZ";
  size_t len = 2 + PICK(buflen / 2);
  const size_t l = len;
  while(len--)
    *buf++ = alpha[PICK(sizeof(alpha)-1)];
  *buf = '\0';
  return l;
}

static inline void set_names (const size_t size) {
  snprintf(perf_in, sizeof perf_in, "%s%zu%s", PERF_PRE, size, ".gperf");
  snprintf(perf_c, sizeof perf_c, "%s%zu%s", PERF_PRE, size, ".c");
  snprintf(perf_exe, sizeof perf_exe, "%s%zu", PERF_PRE, size);
}

static inline void cleanup_files (void) {
  unlink(perf_in);
  unlink(perf_c);
  unlink(perf_exe);
}

static inline void create_set (const size_t size) {
  char cmd[128];
  static unsigned lines = 0;
  printf("Creating set of size %zu\n", size);
  set_names (size);

  if (!lines)
    {
       system("wc -l " WORDS " >words.wc");
       FILE *f = fopen("words.wc","r");
       fscanf(f, "%u", &lines);
       unlink("words.wc");
     }
   if (lines < size)
     {
       FILE *f = fopen("words.tmp","w");
       for (unsigned i=0; i<size; i++)
         {
           random_word(buf, 128);
           fprintf(f, "%s\n", buf);
         }
       fclose(f);
       snprintf(cmd, sizeof cmd, "sort <words.tmp | uniq >%s", perf_in);
       system(cmd);
       unlink("words.tmp");
     }
   else
     {
       snprintf(cmd, sizeof cmd, "head -n %zu " WORDS
                " | grep -v \",\" | sort | uniq >%s", size + 2, perf_in);
       system(cmd);
     }
 }
 static inline void run_gperf (const char *cmd) {
   system(cmd);
 }
 static inline int compile_result (void) {
   char cmd[128];
   snprintf(cmd, sizeof cmd, "cc -O2 -I. %s perf_test.c -o %s",
            perf_c, perf_exe);
   printf("%s", cmd);
   return system(cmd);
 }
static inline int run_result (const char *log, const uint32_t size) {
   char cmd[128];
   snprintf(cmd, sizeof cmd, "./%s %s %s %u", perf_exe, perf_in,
            log, size);
   return system(cmd);
 }

 // measure creation-time (only gperf, not cc), and run-time.
 // also measure compiled-size.
 // use sample sizes from 20, 200, 2k, 20k, 200k, 2m for all variants.
int main (int argc, char **argv)
{
   const string options[] = {
     "", "-S2", "-S4",
     "--chm", "--chm3", "--bpz",
     "--chm --mph-hash-function wyhash",
     "--chm3 --mph-hash-function wyhash",
     "--bpz --mph-hash-function wyhash",
     "--chm --mph-hash-function fnv",
     "--chm3 --mph-hash-function fnv3",
     "--bpz --mph-hash-function fnv3",
   };
   const uint32_t sizes[] = {
     20, 40, 80,
     200, 400, 800,
     2000, 4000, 8000,
     20000, 40000, 80000,
     200000, 2000000
   };
   FILE *comp = fopen("gperf.log", "w");
   FILE *run = fopen("run.log", "w");
   FILE *fsize = fopen("size.log", "w");
   srand(0xbeef);

   for(int i=0; i<(sizeof sizes)/(sizeof *sizes); i++)
     create_set (sizes[i]);

   for (auto option : options) {

     const bool is_mph = option.find("--chm") != string::npos ||
       option.find("--bpz") != string::npos;
     if (argc > 1) {
       option.push_back(' ');
       option.append(argv[1]);
     }
     printf("--- %s ---\n", option.c_str());
     fprintf(comp, "option: %s\n", option.c_str());
     fprintf(run, "option: %s\n", option.c_str());
     fclose(comp);
     fclose(run);
     fprintf(fsize, "option: %s\n", option.c_str());

     for(int i=0; i<(sizeof sizes)/(sizeof *sizes); i++)
       {
         char cmd[128];
         const uint32_t size = sizes[i];
         set_names (size);
         snprintf(cmd, sizeof cmd, "../src/gperf_perf -I %s %s >%s", option.c_str(),
                  perf_in, perf_c);
         printf("size %zu: %s\n", size, cmd);

         // timeout gperf with size>20000 (several minutes)
         if (size > 20000 && !is_mph)
           {
             fprintf(comp, "%20zu %20ld\n", size, 0);
             printf("  skipped\n");
             continue;
           }
#ifndef DUMMY
         run_gperf (cmd);
#endif
         printf("  gperf: %20zu\n", size);
#ifndef DUMMY
         const int ret = compile_result();
         printf("  => %d\n", ret);
#else
         const int ret = 0;
#endif
         if (!ret) {
           struct stat st;
           stat (perf_exe, &st);
           printf("  %s (%lu) %s:\n", perf_exe, st.st_size,  perf_in);
           fprintf(fsize, "%20zu %20lu\n", size, st.st_size);

#ifndef DUMMY
           run_result ("run.log", size);
#endif
         }
       }
     run = fopen("run.log", "a");
     comp = fopen("gperf.log", "a");
   }
#if 1
   for(int i=0; i<(sizeof sizes)/(sizeof *sizes); i++)
     {
       const uint32_t size = sizes[i];
       set_names (size);
       cleanup_files ();
     }
#endif
   fclose(comp);
   fclose(run);
   fclose(fsize);
 }
