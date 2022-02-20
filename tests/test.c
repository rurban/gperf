/*
   Tests the generated perfect hash function.
   The -v option prints diagnostics as to whether a word is in
   the set or not.  Without -v the program is useful for timing.
*/

#include <stdio.h>
#include <string.h>

extern const char * in_word_set (const char *, size_t);
#ifdef DEBUG
unsigned int hash (const char *str, size_t len);
#endif

#define MAX_LEN 80

int
main (int argc, char *argv[])
{
  int  verbose = argc > 1 && !strcmp(argv[1], "-v") ? 1 : 0;
  char *in = argc > 2 ? argv[2] : !verbose && argc > 1 ? argv[1] : NULL;
  char buf[MAX_LEN];
  FILE *f = in ? fopen (in, "r") : stdin;
  int ret = 0;
#ifdef DEBUG
  unsigned i = 0;
#endif

  while (fgets (buf, MAX_LEN, f))
    {
      size_t len = strlen (buf);
      if (len > 0 && buf[len - 1] == '\n')
        buf[--len] = '\0';

      if (in_word_set (buf, len))
        {
          if (verbose)
#ifdef DEBUG
            printf ("in word set %s (hash=%u, index=%u)\n", buf,
                    hash (buf, len), i++);
#else
            printf ("in word set %s\n", buf);
#endif
        }
      else
        {
          ret = 1;
          if (verbose)
#ifdef DEBUG
            printf ("NOT in word set %s (hash=%u, index=%u)\n",
                    buf, hash (buf, len), i++);
#else
            printf ("NOT in word set %s\n", buf);
#endif
        }
    }
  if (in)
    fclose(f);

  return ret;
}
