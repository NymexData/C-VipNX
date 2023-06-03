/*
 *************************************
 Shell Vip Utility written in C for *NX Systems
 *************************************
 *  Simple: Vip shell to avoid usage of sudo
 *************************************
 * Developed and engineered by 
 * Felipe Alfonso gonzalez <f.alfonso@res-ear.ch>
 * Under GNU/GPL
 *************************************
 * gunzip vip.c.gz
 * gcc -o vip vip.c (compilation)
 * su
 * vi /etc/group (nuevo grupo, ej.: staff:x:100:user)
 * mv vip /usr/bin/
 * exit
 * vip
 *
 * */

/*
 # include <stdio.h>
 
 # include <stdlib.h>
 # include <string.h>
 # include <stddef.h>
*/

// # include <strcat.h>
/*

Included necessary header files 
(unistd.h and sys/wait.h) for functions like setuid, setgid, fork, and wait.
Added proper return type and parameter types to the main function.
Fixed the comment syntax (removed leading spaces before #include and #define).
Replaced exit(0) with return 0 at the end of main function.
Replaced the hardcoded value "q" with a proper condition in the if statement.
Removed the duplicated fprintf(stderr, "Vip Shell Ending.\n"); 
line after the if-else statement.


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> // Include for setuid, setgid, and fork
#include <sys/wait.h> // Include for wait

#define MAXLENCMD 1024*6

int main(int argc, char *argv[]) {
    char cmd[MAXLENCMD + 1];
    int pid, rc, i, p;

    setuid(0);
    setgid(1);

    fprintf(stderr, "Starting Vip Shell ...\n");

    if (argc < 2) {
        if ((pid = fork()) == -1) {
            fprintf(stderr, "Fork Failed.\n");
            exit(0);
        } else if (pid == 0) {
            // Try executing different shells with sudo
            execl("/usr/local/bin/tcsh", "tcsh", NULL);
            execl("/bin/tcsh", "tcsh", NULL);
            execl("/usr/bin/tcsh", "tcsh", NULL);
            // Add any additional shells if needed
            execl("/usr/bin/zsh", "zsh", NULL);
            fprintf(stderr, "Failed to start shell.\n");
            exit(1);
        } else {
            while ((p = wait(&rc)) != -1 && p != pid);
            fprintf(stderr, "Vip Shell Ending.\n");
            exit(0);
        }
    }

    for (i = 1, cmd[0] = '\0'; i < argc; i++) {
        if ((strlen(cmd) + strlen(argv[i]) + 1) > MAXLENCMD) {
            fprintf(stderr, "Too many arguments, sorry ....\n");
            fprintf(stderr, "Vip Shell Ending.\n");
            exit(1);
        }
        strcat(cmd, argv[i]);
        strcat(cmd, " ");
    }

    system(cmd);

    fprintf(stderr, "Vip Shell Ending.\n");

    return 0;
}



