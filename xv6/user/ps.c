#include "kernel/types.h"
#include "kernel/uproc.h"
#include "kernel/param.h"
#include "user/user.h"

enum procstate { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };


int
main(int argc, char **argv)
{
  struct uproc up;
  int allflag = 0;

  static char *states[] = {
  [UNUSED]    "unused",
  [USED]      "used",
  [SLEEPING]  "sleep",
  [RUNNABLE]  "runble",
  [RUNNING]   "run",
  [ZOMBIE]    "zombie"
  };
  
  if(argc >= 3){
    fprintf(2, "usage: ps [a]\n");
    exit(-1);
  }

  if (argc == 2 && argv[1][0] == 'a')
    allflag = 1;

  for(int i = 0; i < NPROC; i++){
    sproc(i, &up);
    if(up.state != UNUSED && up.state != USED){
      if(allflag){
        printf("PID=%d NAME=%s SIZE=%d STATE=%s NSCHED=%l NTICKS=%l\n",
               up.pid, up.name, up.sz, states[up.state], up.nsched, up.nticks);
      }else{
        printf("PID=%d NAME=%s\n",
               up.pid, up.name, up.sz, states[up.state]);
      }               
    }
  }

  return 0;
}
