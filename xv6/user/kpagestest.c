#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  int n, p1, p2, diff;
  char *p;

  if(argc != 2){
    printf("usage: kpagestest <npages>\n");
    exit(-1);
  }

  n = atoi(argv[1]);

  p1 = kpages();
  p = malloc(n * 4096);
  memset(p, 'a', n * 4096);
  p2 = kpages();

  diff = p1 - p2;

  printf("kpagetest diff = %d\n", diff);

  free(p);
  
  return 0;
}
