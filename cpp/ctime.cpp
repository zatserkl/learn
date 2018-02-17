/* ctime example */
#include <cstdio>      /* printf */
#include <ctime>       /* time_t, time, ctime */
#include <cstdarg>
#include <cstdlib>

int main (int argc, char *argv[])
{
  if (argc == 1) {
    printf("Usage:\n%s rawtime\n", argv[0]);
    return 0;
  }

  time_t rawtime = atoi(argv[1]);

  printf ("The current local time is: %s", ctime (&rawtime));

  return 0;
}
