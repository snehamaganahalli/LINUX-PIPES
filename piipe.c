
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main() {
    int pipe_in[2];  // Parent -> Child
    pid_t pid;

    if (pipe(pipe_in) == -1) {
        perror("pipe failed");
        exit(1);
    }

    pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child process
        close(pipe_in[1]);  // Close write end (child only reads)

        char buffer[100];
        read(pipe_in[0], buffer, sizeof(buffer));
        close(pipe_in[0]);

        printf("Child received: %s\n", buffer);

        // Example processing: convert to uppercase
        for (int i = 0; buffer[i]; i++) {
            if (buffer[i] >= 'a' && buffer[i] <= 'z') {
                buffer[i] -= 32;
            }
        }
        printf("Child processed: %s\n", buffer);

        exit(0);
    } else {
        // Parent process
        close(pipe_in[0]);  // Close read end (parent only writes)

        char msg[] = "hello from parent";
        write(pipe_in[1], msg, strlen(msg) + 1);
        close(pipe_in[1]);

        wait(NULL);  // Wait for child to finish
    }

    return 0;
}
