#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "value.h"
#include "vm.h"

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
    char *output;
    if (result == INTERPRET_OK) {
        output = outputBuffer[0] ? outputBuffer : "OK";
    } else if (result == INTERPRET_COMPILE_ERROR) {
        output = "Compile Error";
    } else {
        output = "Runtime Error";
    }
    freeVm();
    return output;
}

// Test function
void testRunCode() {
    // Test cases
    const char *tests[] = {
        "print 42;",                // Should output "42" to outputBuffer
        "var x = 1; print x + 2;", // Should output "3"
        "1 + \"bad\";",            // Should return "Runtime Error"
        "if (true print 5;",       // Should return "Compile Error" (syntax error)
        NULL                        // Sentinel to end the loop
    };

    for (int i = 0; tests[i] != NULL; i++) {
        printf("Test %d: Input: '%s'\n", i + 1, tests[i]);
        char *result = runCode(tests[i]);
        printf("Result: '%s'\n", result);
        if (strcmp(result, outputBuffer) == 0 && result != "OK" && result != "Compile Error" && result != "Runtime Error") {
            printf("Output buffer returned: '%s'\n", outputBuffer);
        } else {
            printf("Static string returned: '%s'\n", result);
        }
        printf("---\n");
    }
}

// Test mode
int main(int argc, char *argv[]) {
    if (argc == 1) {
        // Normal REPL or file mode (your original main logic)
        // ... (keep your existing main code here if desired)
        printf("Running in REPL mode...\n");
    } else if (strcmp(argv[1], "--test") == 0) {
        // Test mode
        testRunCode();
    }
    return 0;
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