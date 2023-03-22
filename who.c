#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <utmpx.h>

#define n 16 /* max amount of users to display */

int main(int argc, char *argv[]) {
  struct utmpx * utp;
  gid_t * groups = malloc(n*sizeof(gid_t));

  setutxent();
  while ((utp = getutxent()) != NULL) {
    if (utp->ut_type == USER_PROCESS) {
      printf("%s\n", utp->ut_user);
    }
  }
  endutxent();
  free(groups);

  return 0;
}