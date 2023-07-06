#include "kernel/types.h"
#include "kernel/uproc.h"
#include "user/user.h"

enum procstate { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };


int
main(int argc, char **argv)
{
  int pid;
  int r;
  struct uproc up;

  static char *states[] = {
  [UNUSED]    "unused",
  [USED]      "used",
  [SLEEPING]  "sleep ",
  [RUNNABLE]  "runble",
  [RUNNING]   "run   ",
  [ZOMBIE]    "zombie"
  };
  
  if(argc != 2){
    fprintf(2, "usage: uproc <pid>\n");
    exit(-1);
  }

  pid = atoi(argv[1]);

  r = uproc(pid, &up);

  if(r > 0)
    printf("PID=%d NAME=%s SIZE=%d STATE=%s NSCHED=%l NTICKS=%l\n",
           up.pid, up.name, up.sz, states[up.state], up.nsched, up.nticks);
    
  return 0;
}
