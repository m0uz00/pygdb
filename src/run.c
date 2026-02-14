#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <poll.h>

#include "../include/utils.h"

#define READ 0
#define WRITE 1
#define BUFFER_SIZE 4096

int is_prompt(const char *buffer) {
    size_t len = strlen(buffer);
    if (len >= 4) {
        if (strcmp(&buffer[len-4], ">>> ") == 0) return 1;
        if (strcmp(&buffer[len-4], "... ") == 0) return 1;
    }
    return 0;
}

void wait_for_prompt_interactive(int python_out_fd, int python_in_fd) {
    struct pollfd fds[2];
    char buffer[BUFFER_SIZE];
    char accumulator[BUFFER_SIZE * 4] = {0};

    fds[0].fd = python_out_fd;
    fds[0].events = POLLIN;

    fds[1].fd = STDIN_FILENO;
    fds[1].events = POLLIN;

    while (1) {
        int ret = poll(fds, 2, -1); 
        if (ret == -1) { perror("poll"); exit(1); }

        if (fds[0].revents & POLLIN) {
            ssize_t bytes = read(python_out_fd, buffer, sizeof(buffer) - 1);
            if (bytes <= 0) break; 

            buffer[bytes] = '\0';
            // if (strstr(buffer, ">>>") != NULL || strstr(buffer, "...") != NULL){
            //   printf("%s", buffer + 3); 
            // } else {
            //   printf("%s", buffer);
            // }
            printf("%s", buffer);
            fflush(stdout);       

            strncat(accumulator, buffer, sizeof(accumulator) - strlen(accumulator) - 1);
            if (is_prompt(accumulator)) {
                break; 
            }
        }

        if (fds[1].revents & POLLIN) {
            ssize_t bytes = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
            if (bytes > 0) {
                write(python_in_fd, buffer, bytes);
            }
        }
    }
}

void run_file(program* program) {
    int stdin_pipe[2];
    int stdout_pipe[2];
    pid_t pid;

    if (!program || !program->lines || !program->lines->head) {
        fprintf(stderr, "Error: Program is empty.\n");
        return;
    }

    if (pipe(stdin_pipe) < 0 || pipe(stdout_pipe) < 0) return;

    pid = fork();
    if (pid < 0) return;

    if (pid == 0) {
        dup2(stdin_pipe[READ], STDIN_FILENO);
        dup2(stdout_pipe[WRITE], STDOUT_FILENO);
        dup2(stdout_pipe[WRITE], STDERR_FILENO);

        close(stdin_pipe[READ]); close(stdin_pipe[WRITE]);
        close(stdout_pipe[READ]); close(stdout_pipe[WRITE]);

        execlp("python3", "python3", "-i", "-u", NULL);
        exit(1);
    } 

    close(stdin_pipe[READ]);
    close(stdout_pipe[WRITE]);

    wait_for_prompt_interactive(stdout_pipe[READ], stdin_pipe[WRITE]);

    list_item* current = program->lines->head;
    int last_indent = 0;

    while (current != NULL) {
        if (current->line && current->line->line_text) {
            char *text = current->line->line_text;
            
            int current_indent = 0;
            while (text[current_indent] == ' ') current_indent++;

            if (last_indent > 0 && current_indent == 0) {
                 write(stdin_pipe[WRITE], "\n", 1);
                 wait_for_prompt_interactive(stdout_pipe[READ], stdin_pipe[WRITE]);
            }

            write(stdin_pipe[WRITE], text, strlen(text));
            write(stdin_pipe[WRITE], "\n", 1);
            
            last_indent = current_indent;
            
            wait_for_prompt_interactive(stdout_pipe[READ], stdin_pipe[WRITE]);
        }
        current = current->next;
    }

    close(stdin_pipe[WRITE]);
    close(stdout_pipe[READ]);
    waitpid(pid, NULL, 0);
}
