#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int main() {
  pid_t child_id1, child_id2, child_id3, child_id4, child_id5, child_id6, child_id7, child_id8;
  int status;
  char ch[100];
  FILE *destination;
  struct stat check;

  child_id1 = fork();

  if (child_id1 == 0) {
    child_id2 = fork();
    if (child_id2 == 0) {
      child_id3 = fork();
      if (child_id3 == 0) {
        child_id4 = fork();
        if (child_id4 == 0) {
          // child_id5 = fork();
          // if (child_id5 == 0) {
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
        sprintf(ch, "/home/dicki/Praktikum/Praktikum2/jpg");
        char *argv[] = {"mv", ch, "/home/dicki/modul2", NULL};
        execv("/bin/mv", argv);
      }  
    }else {
      while ((wait(&status)) > 0);
      chdir("/home/dicki/modul2/jpg/");
      struct dirent *de;
      DIR *dr = opendir(".");
      while ((de = readdir(dr)) != NULL){
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
          continue;
        child_id6 = fork();
        if (child_id6 == 0) {
          child_id7 = fork();
          if (child_id7 == 0) {
            child_id8 = fork();
            if (child_id8 == 0) {
              if (stat(de->d_name,&check) == 0){
                if (check.st_mode & S_IFDIR) {
                  sprintf(ch, "/home/dicki/modul2/jpg/%s", de->d_name);
                  char *argv[] = {"mv", ch, "/home/dicki/modul2/indomie", NULL};
                  execv("/bin/mv", argv);
                }else {
                  while ((wait(&status)) > 0);
                  sprintf(ch, "/home/dicki/modul2/jpg/%s", de->d_name);
                  char *argv[] = {"mv", ch, "/home/dicki/modul2/sedaap" , NULL};
                  execv("/bin/mv", argv);
                } 
              }
            }else {
                while ((wait(&status)) > 0);
                sprintf(ch, "/home/dicki/modul2/indomie/%s/coba1.txt", de->d_name);
                destination = fopen(ch, "w+");
                fclose(destination);
            }
          }else {
            while ((wait(&status)) > 0);
            sleep(3);
            sprintf(ch, "/home/dicki/modul2/indomie/%s/coba2.txt", de->d_name);
            destination = fopen(ch, "w+");
            fclose(destination);
          }
        }else {
          while ((wait(&status)) > 0);    
        }
      }
      close(dr);
    }
}
