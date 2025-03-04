#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "value.h"
#include "vm.h"

extern char outputBuffer[];

static char *readFile(const char *path) {
    FILE *file = fopen(path, "rb");
    if (file == NULL) {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char *buffer = (char*)malloc(fileSize + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
        exit(74);
    }

    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);
    if (bytesRead < fileSize) {
        fprintf(stderr, "Could not read file \"%s\".\n", path);
        exit(74);
    }

    buffer[bytesRead] = '\0';

    fclose(file);
    return buffer;
}

static void runFile(const char *path) {
    char *source = readFile(path);
    InterpretResult result = interpret(source);
    free(source);

    if (result == INTERPRET_COMPILE_ERROR) exit(65);
    if (result == INTERPRET_RUNTIME_ERROR) exit(70);
}

static void repl() {
    char line[1024];
    for (;;) {
        printf("> ");

        if (!fgets(line, sizeof(line), stdin)) {
            printf("\n");
            break;
        }
        interpret(line);
    }
}

char *runCode(const char *source) {
    initVm();
    resetOutput();
    InterpretResult result = interpret(source);
    if (result == INTERPRET_OK) {
        return outputBuffer[0] ? outputBuffer : "OK";
    } else if (result == INTERPRET_COMPILE_ERROR) {
        return "Compile Error";
    } else {
        return "Runtime Error";
    }
    freeVm();
}

int main() {
}

// int main() {
//     writeOutput("Test: %d, %s\n", 123, "hello");
//     printf("%s", outputBuffer);  // Should print "Test: 123, hello\n"
//     return 0;
// }

// int main(int argc, const char *argv[]) {
//     initVm();
//     if (argc == 1) {
//         repl();
//     } else if (argc == 2) {
//         runFile(argv[1]);
//     } else {
//         fprintf(stderr, "Usage: yeager [path]\n");
//         exit(64);
//     }
//     freeVm();
// }

// int main(int argc, const char *argv[]) {
//     initVm();
//     resetOutput();
//     if (argc == 1) {
//         repl();
//     } else if (argc == 2) {
//         runFile(argv[1]);
//     } else {
//         fprintf(stderr, "Usage: yeager [path]\n");
//         exit(64);
//     }
//     freeVm();
// }