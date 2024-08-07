#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>

#define STACK_FILE "/tmp/dir_stack.txt"
#define MAX_PATH_LENGTH PATH_MAX

void push_directory(const char *new_dir) {
    char current_dir[MAX_PATH_LENGTH];
    if (getcwd(current_dir, sizeof(current_dir)) == NULL) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(STACK_FILE, "a");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    fprintf(file, "%s\n", current_dir);
    fclose(file);

    if (chdir(new_dir) != 0) {
        perror("chdir");
        exit(EXIT_FAILURE);
    }

    printf("Directory changed to %s\n", new_dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <directory>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    push_directory(argv[1]);
    return 0;
}
