/*
   Tests the generated perfect hash function.
   For keyword lists with %% and structs.
*/

#include <stdio.h>
#include <string.h>

extern const char * in_word_set (const char *, size_t);

#define MAX_LEN 255

int
main (int argc, char *argv[])
{
  char buf[MAX_LEN];
  char *p;
  const int verbose = argc > 2;
  char *in = argc > 2 ? argv[2] : argc > 1 ? argv[1] : NULL;
  int found = 0;
  int ret = 0;

  if (!in)
    return 1;
  FILE *f = fopen (in, "r");
  while (fgets (buf, MAX_LEN, f))
    {
      size_t len = strlen (buf);
      if (len > 0 && buf[len - 1] == '\n')
        buf[--len] = '\0';

      if (strcmp (buf, "%%") == 0)
        found++;
      if (found != 1)
        continue;

      if ((p = strchr (buf, ',')))
        *p = '\0';
      else
        continue;
      if (in_word_set (buf, strlen (buf)))
        {
          if (verbose)
            printf ("in word set %s\n", buf);
        }
      else
        {
          ret = 1;
          if (verbose) {
            printf ("NOT in word set %s\n", buf);
          }
        }
    }
  fclose (f);

  return ret;
}
