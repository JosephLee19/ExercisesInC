
#define _GNU_SOURCE
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <limits.h>


int main(int argc, char *argv[]) /*accepts an array of char pointers and the number inputs from the command line*/
{
    int fd;
    int len, slen;


    assert(argc == 2);/* makes sure that only 1 argument is passed in (argc is number of args in argv + 1) - prints error if not true


    fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);/* opens the file passed in as the first argument from command line*/
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);/*prints error message if file fails to open*/
    }


    do {
        /*
         * copy stdin to stdout.
         */

        len = tee(STDIN_FILENO, STDOUT_FILENO,
                  INT_MAX, SPLICE_F_NONBLOCK);


        if (len < 0) {
            if (errno == EAGAIN)
                continue;
            perror("tee");
            exit(EXIT_FAILURE);
        } else
            if (len == 0)
                break;


        /*
         * Send stdin by splicing it to a file.
         */
        while (len > 0) {
            slen = splice(STDIN_FILENO, NULL, fd, NULL,
                          len, SPLICE_F_MOVE);
            if (slen < 0) {
                perror("splice");
                break;
            }
            len -= slen;
        }
    } while (1);


    close(fd);
    exit(EXIT_SUCCESS);
}

/* Adapted from code at http://www.tutorialspoint.com/unix_system_calls/tee.htm

3) Reflect: what worked, what slowed you down?  What would you do
differently next time?

	I was able to fairly quickly break down what I needed to do and scratch out some pseudocode to solve this problem
	but I ran into a lot of problems trying to figure out how to actually implement my pseudocode. As I began running
	out of time, I ended up finding an existing program and then going line by line through it to understand how it was
	implemented/how it worked. Next time the main thing I would do differently is break it down into pieces instead of
	trying to do everything at once - i.e. just start out by writing a function that takes command line arguments, then
	copies stdin to stdout, and build from there.


4) Compare your solution to the real thing.  What do you see in
professional code that is not in your solution?

	Not sure where to find the 'professional' code referred to here?
*/

