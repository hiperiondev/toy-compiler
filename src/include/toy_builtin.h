#ifndef _TOY_BUILTIN_H_
#define _TOY_BUILTIN_H_

#include <stdbool.h>

#include "toy_common.h"
#include "toy_literal.h"
#include "toy_literal_array.h"
#include "toy_literal_dictionary.h"
#include "toy_scope.h"

typedef struct Toy_Interpreter {
    //operation
    Toy_Scope *scope;
    Toy_LiteralArray stack;

    //debug outputs
    Toy_PrintFn printOutput;
    Toy_PrintFn errorOutput;
} Toy_Interpreter;

//the _index function is a historical oddity - it's used whenever a compound is indexed
int Toy_private_index(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments);

//globally available native functions
int Toy_private_set(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments);
int Toy_private_get(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments);
int Toy_private_push(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments);
int Toy_private_pop(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments);
int Toy_private_length(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments);
int Toy_private_clear(Toy_Interpreter *interpreter, Toy_LiteralArray *arguments);

#endif /* _TOY_BUILTIN_H_ */
