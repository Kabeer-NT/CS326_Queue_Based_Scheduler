#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
memcheck(char *addr, int c, int n)
{
  int match = 1;

  for(int i = 0; i < n; i++){
    if(addr[i] != c){
      match = 0;
      break;
    }
  }
  
  return match;
}

void
memcheck_print(char *name, char *addr, int c, int n){
  int r;

  r = memcheck(addr, c, n);
  if(r == 0){
    printf("[%s] memcheck(%p, %c, %d) failed\n", name, addr, c, n);
    exit(-1);
  }
  printf("[%s] memcheck(%p, %c, %d) succeeded\n", name, addr, c, n);
}

void
smemtest(int n)
{
  char *smem_addr = (char *) 0x40000000;
  int smem_size;
  char smem_start_char = 'a';
  char smem_end_char = 'b';
  
  int r;
  int id;

  smem_size = n * 4096;

  // Create shared memory region at VA 1GB
  r = smem(smem_addr, smem_size);
  if(r < 0){
    printf("smem(%p, %d) failed\n", smem_addr, smem_size);
    exit(-1);
  }

  // Initialize shared memory region to all 'a's
  memset(smem_addr, smem_start_char, smem_size);
  memcheck_print("parent_pre", smem_addr, smem_start_char, smem_size);

   // Fork a child, which should inherit the shared region
  id = fork();

  if(id == 0){
    // In child
    memcheck_print("child_pre", smem_addr, smem_start_char, smem_size);
    memset(smem_addr, smem_end_char, smem_size);
    memcheck_print("child_post", smem_addr, smem_end_char, smem_size);

    exit(0);
  }

  // In parent
  wait(0);

  memcheck_print("parent_post", smem_addr, smem_end_char, smem_size);
}


int
main(int argc, char **argv)
{
  int n;
  int p1, p2, diff;
  
  int id;

  if(argc != 2){
    printf("usage: smemtest <npages>\n");
    exit(-1);
  }

  n = atoi(argv[1]);

  p1 = kpages();

  id = fork();
  if(id == 0){
    smemtest(n);
    exit(0);
  }else{
    wait(0);
  }

  p2 = kpages();

  diff = p1 - p2;
  printf("[main] kpages() diff = %d\n", diff);

  return 0;
}
