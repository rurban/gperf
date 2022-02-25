/*
   Measure the generated perfect hash functions.
*/

#include <stdio.h>
#include <string.h>
#include "perf.h"

extern const char * in_word_set (const char *, size_t);

#define MAX_LEN 80

int
main (int argc, char *argv[])
{
  char *in = argv[1];
  char *log = argv[2];
  size_t size;
  char buf[MAX_LEN];
  FILE *f = fopen (in, "r");
  int ret = 0;
  unsigned i = 0;
  sscanf(argv[3], "%u", &size);

  uint64_t t = timer_start ();
 restart:
  while (fgets (buf, MAX_LEN, f))
    {
      size_t len = strlen (buf);
      if (len > 0 && buf[len - 1] == '\n')
        buf[--len] = '\0';

      if (!in_word_set (buf, len))
        {
          ret = 1;
          printf ("NOT in word set %s\n", buf);
        }
      i++;
      if (i > PERF_LOOP)
        break;
    }
  if (i < PERF_LOOP)
    {
      rewind (f);
      goto restart;
    }
  t = timer_end () - t;
  fclose(f);
  f = fopen (log, "a");
  fprintf(f, "%20zu %20lu\n", size, t / PERF_LOOP);
  fclose(f);
  
  return ret;
}
