#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "toy.h"

#define INPUT_BUFFER_SIZE 2048

#define EP(x) [x] = #x
const char *AST_NODE_STR[] = {
        EP(TOY_AST_NODE_ERROR), //
        EP(TOY_AST_NODE_LITERAL), //
        EP(TOY_AST_NODE_UNARY), //
        EP(TOY_AST_NODE_BINARY), //
        EP(TOY_AST_NODE_TERNARY), //
        EP(TOY_AST_NODE_GROUPING), //
        EP(TOY_AST_NODE_BLOCK), //
        EP(TOY_AST_NODE_COMPOUND), //
        EP(TOY_AST_NODE_PAIR), //
        EP(TOY_AST_NODE_INDEX), //
        EP(TOY_AST_NODE_VAR_DECL), //
        EP(TOY_AST_NODE_FN_DECL), //
        EP(TOY_AST_NODE_FN_COLLECTION), //
        EP(TOY_AST_NODE_FN_CALL), //
        EP(TOY_AST_NODE_FN_RETURN), //
        EP(TOY_AST_NODE_IF), //
        EP(TOY_AST_NODE_WHILE), //
        EP(TOY_AST_NODE_FOR), //
        EP(TOY_AST_NODE_BREAK), //
        EP(TOY_AST_NODE_CONTINUE), //
        EP(TOY_AST_NODE_AND), //
        EP(TOY_AST_NODE_OR), //
        EP(TOY_AST_NODE_PREFIX_INCREMENT), //
        EP(TOY_AST_NODE_POSTFIX_INCREMENT), //
        EP(TOY_AST_NODE_PREFIX_DECREMENT), //
        EP(TOY_AST_NODE_POSTFIX_DECREMENT), //
        EP(TOY_AST_NODE_IMPORT), //
        EP(TOY_AST_NODE_PASS), //
};

char* readFile(const char *path, size_t *fileSize) {
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

    buffer[*fileSize] = '\0';

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

    char *source = readFile("fib-memo.toy", &fileSize);

    Toy_Lexer lexer;
    Toy_Parser parser;
    Toy_Compiler compiler;

    Toy_initLexer(&lexer, source);
    Toy_initParser(&parser, &lexer);
    Toy_initCompiler(&compiler);

    // step 1 - run the parser until the end of the source
    Toy_ASTNode *node = Toy_scanParser(&parser);
    while (node != NULL) {
        printf("%s\n", AST_NODE_STR[node->type]);
        // on error, pack up and leave
        if (node->type == TOY_AST_NODE_ERROR) {
            Toy_freeASTNode(node);
            Toy_freeCompiler(&compiler);
            Toy_freeParser(&parser);
            printf("ERROR!\n");
            return 1;
        }

        Toy_writeCompiler(&compiler, node);
        Toy_freeASTNode(node);
        node = Toy_scanParser(&parser);
    }

    // step 2 - get the bytecode dump
    //unsigned char *tb = Toy_collateCompiler(&compiler, &fileSize);

    // cleanup
    Toy_freeASTNode(node);
    Toy_freeCompiler(&compiler);
    Toy_freeParser(&parser);

    printf("-- end test --\n");

    return 0;
}
