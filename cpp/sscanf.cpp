// http://cplusplus.com/reference/clibrary/cstdio/sscanf.html
#include <cstdio>

main()
{
  char sentence[] = "Rudolph is 12 years old";
  char str[20];
  int i;
  // NB * here: %*s "is" will be ignored
  sscanf (sentence,"%s %*s %d",str,&i); 
  printf ("%s -> %d\n",str,i);            // Rudolph -> 12
}
