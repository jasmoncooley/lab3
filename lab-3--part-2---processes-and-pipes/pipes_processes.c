
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
void ChildProcess(void); /* child process prototype */
void ParentProcess(void); /* parent process prototype */
int data[2];
int main(void)
{
pid_t pid;
pipe(data);
pid = fork();
if (pid == 0)
ChildProcess();
else
ParentProcess();
return 0;
}
void ChildProcess(void)
{
char readData[80];
// printf("This line is from child\n");
close(data[1]);
/* Read in a string from the pipe */
read(data[0], readData, sizeof(readData));
printf("child Received string: %s", readData);
printf("*** Child process is done ***\n");
}
void ParentProcess(void)
{
printf("This line is from parent\n");
char string[]="Hey, this is Jasmon's code.\n";
printf("%s",string);
close(data[0]);
/* Send "string" through the output side of pipe */
write(data[1], string, (strlen(string)+1));
printf("*** Parent is done ******\n");
printf("\n");
}