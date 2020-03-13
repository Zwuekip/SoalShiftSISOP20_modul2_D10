#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>
#include <wait.h>

int main() {
    pid_t pid, sid;

    pid = fork();
  
    if (pid < 0) {
        exit(EXIT_FAILURE);
    }

    if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    umask(0);

    sid = setsid();
    if (sid < 0) {
        exit(EXIT_FAILURE);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    while (1) {
        pid_t child_id1, child_id2, child_id3;
        int status;
        time_t t;
        struct tm *tmp;
        char ch[100], chr[100], file[100], s[100], filezip[100];
        t = time(NULL);
        tmp = localtime(&t);
        strftime(ch, 100, "%Y-%m-%d - %X", tmp);
        child_id1 = fork();
        if (child_id1 == 0) {
            child_id2 = fork();
            if (child_id2 == 0){
                child_id3 = fork();
                if (child_id3 == 0) {
                    char *argv[] = {"mkdir", ch, NULL};
                    execv("/bin/mkdir", argv);
                    t = (t % 1000) + 100;
                }else {
                    while ((wait(&status)) > 0);
                    chdir(ch);
                    for (int i=0; i<20; i++) {
                        if (fork() == 0) {
                            time_t waktu;
                            struct tm *waktu_check;
                            waktu = time(NULL);
                            waktu_check = localtime(&waktu);
                            int sec = time(NULL);
                            sec = (sec % 1000) +100;
                            sprintf(chr, "https://picsum.photos/%d", sec);
                            strftime(file, 100, "%Y-%m-%d - %X", waktu_check);
                            char *argv[] = {"wget", chr, "-O", file, NULL};
                            execv("/usr/bin/wget", argv);
                        }
                        sleep(5);
                    }
                    sprintf(filezip, "%s.zip", ch);
                    char *argv[] = {"zip", filezip, ch, NULL};
                    execv("/usr/bin/zip", argv);
                }
            }else {
                while ((wait(&status)) > 0);
                char *argv[] = {"rm", "-r", ch, NULL};
                execv("/bin/rm", argv);
            }
        }else 
            sleep(30)
    }
}
