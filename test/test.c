#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "toy.h"

#define INPUT_BUFFER_SIZE 2048

const char* readFile(const char *path, size_t *fileSize) {
    FILE *file = fopen(path, "rb");

    if (file == NULL) {
        fprintf(stderr, TOY_CC_ERROR "Could not open file \"%s\"\n" TOY_CC_RESET, path);
        return NULL;
    }

    fseek(file, 0L, SEEK_END);
    *fileSize = ftell(file);
    rewind(file);

    char *buffer = (char*) malloc(*fileSize + 1);

    if (buffer == NULL) {
        fprintf(stderr, TOY_CC_ERROR "Not enough memory to read \"%s\"\n" TOY_CC_RESET, path);
        return NULL;
    }

    size_t bytesRead = fread(buffer, sizeof(unsigned char), *fileSize, file);

    buffer[*fileSize] = '\0'; //NOTE: fread doesn't append this

    if (bytesRead < *fileSize) {
        fprintf(stderr, TOY_CC_ERROR "Could not read file \"%s\"\n" TOY_CC_RESET, path);
        return NULL;
    }

    fclose(file);

    return buffer;
}

int main(void) {
    printf("-- start test --\n");

    size_t fileSize = 0;

    const char *input = readFile("fib-memo.toy", &fileSize);

    Toy_Lexer lexer;
    Toy_Parser parser;
    Toy_Compiler compiler;

    Toy_initLexer(&lexer, input);
    Toy_private_setComments(&lexer, true);
    Toy_initParser(&parser, &lexer);
    Toy_initCompiler(&compiler);

    //run this iteration
    Toy_ASTNode *node = Toy_scanParser(&parser);
    while (node != NULL) {
        //pack up and restart
        if (node->type == TOY_AST_NODE_ERROR) {
            if (Toy_commandLine.verbose) {
                printf(TOY_CC_ERROR "Error node detected\n" TOY_CC_RESET);
            }
            Toy_freeASTNode(node);
            break;
        }

        Toy_writeCompiler(&compiler, node);
        Toy_freeASTNode(node);
        node = Toy_scanParser(&parser);
    }

    //clean up this iteration
    free(node);
    Toy_freeCompiler(&compiler);
    Toy_freeParser(&parser);

    printf("-- end test --\n");

    return 0;
}
