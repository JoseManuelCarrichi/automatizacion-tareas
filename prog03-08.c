#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

void main(void)
{
   pid_t pid;
   int status;

   pid = fork();
   switch(pid)
   {
      case -1:   /* error del fork() */
         exit(-1);
      case 0:    /* proceso hijo */
         execlp("ls","ls","-l",NULL);
         perror("exec");
         break;
      default:   /* padre */
         printf("Proceso padre\n");
         while(pid != wait(&status));
   }
}
