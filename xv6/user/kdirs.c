#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  int amt;

  amt = kdirs();

  printf("kdirs() = %d\n", amt);

  return 0;
}
