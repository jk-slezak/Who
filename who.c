#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <utmpx.h>
#include <pwd.h>
#include <grp.h>

#define MAX_GROUPS 16 /* max amount of groups to display */

int main(int argc, char *argv[]) {
  struct utmpx * utp;
  struct passwd * pw;
  struct group * gr;

  int groups_amount = MAX_GROUPS;
  gid_t * groups = malloc(MAX_GROUPS*sizeof(gid_t));
  
  int arg;
  bool flag_h = false;
  bool flag_g = false;

  /* parse options from program call */
  while((arg = getopt(argc, argv, "hg")) != -1) {
    switch (arg) {
      case 'h':
        flag_h = true;
        break;
      case 'g':
        flag_g = true;
        break;
      default:
        break;
    }
  }

  setutxent();
  while ((utp = getutxent()) != NULL) {
    if (utp->ut_type == USER_PROCESS) {

      /* prints logged in username */
      printf("%s  ", utp->ut_user);

      /* if true prints logged in user host*/
      if (flag_h) {
        printf("%s  ", utp->ut_host);
      }

      /* if true prints logged in user groups*/
      if (flag_g) {
        pw = getpwnam(utp->ut_user);
        getgrouplist(utp->ut_user, pw->pw_gid, groups, &groups_amount);
        for(int i = 0; i < groups_amount; i++) {
          gr = getgrgid(groups[i]);
        printf("%s ", gr->gr_name);
        }
      }
      printf("\n");
    }
  }
  endutxent();
  free(groups);

  return 0;
}
