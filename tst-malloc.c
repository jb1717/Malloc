#include <errno.h>
#include <malloc.h>
#include <stdio.h>

static int errors = 0;

static void
merror (const char *msg)
{
  ++errors;
  printf ("Error: %s\n", msg);
}

int
main (void)
{
  void *p, *q;
  int save;

  errno = 0;

  p = malloc (-1);
  save = errno;

  if (p != NULL)
    merror ("malloc (-1) succeeded.");

  if (p == NULL && save != ENOMEM)
    merror ("errno is not set correctly");

  p = malloc (10);
  if (p == NULL)
    merror ("malloc (10) failed.");

  /* realloc (p, 0) == free (p).  */
  p = realloc (p, 0);
  if (p != NULL)
    merror ("realloc (p, 0) failed.");
  
  p = malloc (0);
  if (p == NULL)
    merror ("malloc (0) failed.");

  p = realloc (p, 0);
  if (p != NULL)
    merror ("realloc (p, 0) failed.");

  p = malloc (513 * 1024);
  if (p == NULL)
    merror ("malloc (513K) failed.");

  q = malloc (-512 * 1024);
  if (q != NULL)
    merror ("malloc (-512K) succeeded.");

  free (p);

  return errors != 0;
}
