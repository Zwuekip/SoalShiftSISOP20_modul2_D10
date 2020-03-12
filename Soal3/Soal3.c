#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main() {
  pid_t child_id1, child_id2, child_id3, child_id4, child_id5, child_id6;
  int status;

  child_id1 = fork();

  if (child_id1 == 0) {
    child_id2 = fork();
    if (child_id2 == 0) {
      child_id3 = fork();
      if (child_id3 == 0) {
        child_id4 = fork();
        if (child_id4 == 0) {
          child_id5 = fork();
          if (child_id5 == 0) {
            child_id6 = fork();
            if(child_id6 == 0) {
              char *argv[] = {"mkdir", "-p", "/home/dicki/modul2/indomie", NULL};
              execv("/bin/mkdir", argv);
            }else {
              while ((wait(&status)) > 0);
              sleep(5);
              char *argv[] = {"mkdir", "-p", "/home/dicki/modul2/sedaap", NULL};
              execv("/bin/mkdir", argv);
            }
          }else {
            while ((wait(&status)) > 0);
            char *argv[] = {"unzip", "jpg.zip", NULL};
            execv("/usr/bin/unzip", argv);
          }
        }else {
          while ((wait(&status)) > 0);
          char *argv[] = {"bash", "mv.sh" , NULL};
          execv("/bin/bash", argv);
        }  
      }else {
        while ((wait(&status)) > 0);
        char *argv[] = {"bash", "mvfile.sh" , NULL};
        execv("/bin/bash", argv);
      }
    }else {
      while ((wait(&status)) > 0);
      char *argv[] = {"bash", "mvdir.sh" , NULL};
      execv("/bin/bash", argv);
    }
  }
          
}
