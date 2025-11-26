#include<stdio.h>
#include <unistd.h>
/* Pipes: 
   echo sneha magi | grep -i sne. => command1 | command2
   When we invoke popen and new process is invoked. We can either read from the new process
   or write from the new process. Pipe will have 2 ends, 1 will be read end and one will be write end.
   Therefore pipe cannot be opened in both read and write mode.
*/

int main()
{
char buf[100] = "sneha magi";
FILE* fp = NULL;
int fd = -1;
/* Opening pipe in read mode.
   Here uname -r will be executed in a new invoked process.
   After executing it, the output can be read from the file pointer fp returned by popen.

   below command is equal to uanme -r  executing on shell.
   The fd returned by the popen function will be some number other than 0,1,2. 0,1,2 belongs to
   STDIN< STDOUT,STDERR.
*/
fp = popen("uname -r", "r");
if(fread(buf,1,100,fp ))
{
   printf("%s", buf);
}

/* Opening pipe in a write mode.
   Here grep -i dolly will be executed. If grep -i dolly is executed on shel.
   then it will be blocked. It waits to get the input.

   But popen will not block. if input is written on the file pointer fp returned by the popen,
   then it will be the input to the command executed bythe new process.

  the below command is equal to:
  echo sneha magi | grep -i dolly

  Parent (your program) ----WRITE----> [PIPE] ----READ----> Child (grep -i dolly)
*/
fp = popen("grep -i dolly", "w");
fwrite(buf,1,100,fp );
fclose(fp);

/* the below command is equal to:
  echo sneha magi | grep -i sneha */
fp = popen("grep -i sneha", "w");
fwrite(buf,1,100,fp );
fclose(fp);

/* the below command is equal to:
  echo sneha magi | od -c */
fp = popen("od -c", "w");
fwrite(buf,1,100,fp );
fclose(fp);

return 0;
}
