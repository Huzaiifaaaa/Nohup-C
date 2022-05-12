 #include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <sys/file.h>
#include<sys/types.h>
#include <malloc.h>
#include<unistd.h>
#include <dirent.h>
#include<wchar.h>
#include<fcntl.h>
#include<signal.h>


void handler(int signal)
{
    printf("\nThe process will run in background!");
}

//gcc main.c –o nohup
//nohup test.exe 0 1

 int main(int argc, char *argv[])
 {

    if( argc < 2 )
    {
        char *errormessage = "The Arguments Passed Are Invalid! \n";
        int length = strlen(errormessage);
        int out=write(STDERR_FILENO, errormessage, length);
        return 1;
    }
    else
    {


        int writefile = open("nohup.out", O_RDWR|O_CREAT|O_APPEND, 0600);

        if(writefile==-1)
        {
            char *errormessage = "Unable to write to file! \n";
            int length = strlen(errormessage);
           int out= write(STDERR_FILENO, errormessage, length);
            return 1;
        }

        int error=dup2(writefile,2);
        if(isatty(fileno(stdout)))
        {
            int output=dup2(writefile,1);
        }

        char *filename= argv[1];

        signal(SIGHUP,handler);
        signal(SIGQUIT,handler);

        pid_t pid=fork();
        if (pid==0)
        {
            char *args[5];

            args[1] = argv[2];
            args[2] = argv[3];
            args[3] = NULL;

            execv(filename,*args);
        }
      else if(pid==-1)
        {
          char *errormessage = "Unable to fork! \n";
          int length = strlen(errormessage);
          int out= write(STDERR_FILENO, errormessage, length);
          return 1;
        }

        int out=write(writefile, "\n", 1);
        close(writefile);
    }
     return 0;
 }




































 /*#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <sys/file.h>
#include<sys/types.h>
#include <malloc.h>
#include<unistd.h>
#include <dirent.h>
#include<process.h>
#include<wchar.h>
#include <direct.h>
#include<fcntl.h>
#include<signal.h>

#define SIGHUP  1
#define SIGQUIT 3

void handler(int signal)
{
    printf("\nThe process will run in background!");
}

//gcc main.c –o nohup
//nohup test.exe 0 1

 int main(int argc, char *argv[])
 {

    if( argc < 2 )
    {
        char *errormessage = "The Arguments Passed Are Invalid! \n";
        int length = strlen(errormessage);
        write(STDERR_FILENO, errormessage, length);
        return 1;
    }
    else
    {
        (void)signal(SIGINT, SIG_IGN);
        (void)signal(SIGHUP, SIG_IGN);
        (void)signal(SIGQUIT, SIG_IGN);

        int writefile = open("nohup.out", O_RDWR|O_CREAT|O_APPEND, 0600);

        if(writefile==-1)
        {
            char *errormessage = "Unable to write to file! \n";
            int length = strlen(errormessage);
            write(STDERR_FILENO, errormessage, length);
            return 1;
        }
        write(writefile, "\n", 1);

        if(isatty(fileno(stdout)))
        {
            int output=dup2(writefile,1);
        }

        if(isatty(fileno(stderr)))
        {
            int error=dup2(writefile,2);
        }
        char *filename= argv[1];

        int fid=execlp(filename,filename,argv[2],argv[3],NULL);

 pid_t pid=fork();

        close(writefile);
    }
    sleep(10);
     return 0;
 }*/

