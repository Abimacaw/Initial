#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>

#define STACK_FILE "/tmp/dir_stack.txt"
#define MAX_PATH_LENGTH PATH_MAX

void pop_directory() {
    char current_dir[MAX_PATH_LENGTH];
    char stack[MAX_PATH_LENGTH][MAX_PATH_LENGTH];
    int stack_size = 0;

    FILE *file = fopen(STACK_FILE, "r");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while (fgets(stack[stack_size], sizeof(stack[stack_size]), file) != NULL) {
        stack[stack_size][strcspn(stack[stack_size], "\n")] = '\0'; // Remove newline
        stack_size++;
    }
    fclose(file);

    if (stack_size == 0) {
        fprintf(stderr, "Directory stack is empty.\n");
        exit(EXIT_FAILURE);
    }

    if (chdir(stack[stack_size - 1]) != 0) {
        perror("chdir");
        exit(EXIT_FAILURE);
    }

    printf("Directory changed to %s\n", stack[stack_size - 1]);

    file = fopen(STACK_FILE, "w");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < stack_size - 1; i++) {
        fprintf(file, "%s\n", stack[i]);
    }
    fclose(file);
}

int main() {
    pop_directory();
    return 0;
}
