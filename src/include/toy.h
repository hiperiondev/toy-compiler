#ifndef _TOY_H_
#define _TOY_H_

/*!
 # toy.h - A Toy Programming Language

 If you're looking how to use Toy directly, try https://toylang.com/
 Otherwise, this header may help learn how Toy works internally.
 !*/

/*!
 ## Utilities

 These headers define a bunch of useful macros, based on what platform you build for.

 The most important macro is `TOY_API`, which specifies functions intended for the end user.

 * [toy_common.h](toy_common_h.md)
 * [toy_console_colors.h](toy_console_colors_h.md)
 * [toy_memory.h](toy_memory_h.md)
 !*/

#include "toy_common.h"
#include "toy_console_colors.h"
#include "toy_memory.h"

/*!
 ## Core Pipeline

 From source to execution, each step is as follows:

 ```
 source   -> lexer       -> token
 token    -> parser      -> AST
 AST      -> compiler    -> bytecode
 bytecode -> interpreter -> result
 ```

 I should note that the parser -> compiler phase is actually made up of two steps - the write step and the collate step. See `Toy_compileString()` in `repl/repl_tools.c` for an example of how to compile properly.

 * [toy_lexer.h](toy_lexer_h.md)
 * [toy_parser.h](toy_parser_h.md)
 * [toy_compiler.h](toy_compiler_h.md)
 * [toy_interpreter.h](toy_interpreter_h.md)
 !*/

#include "toy_lexer.h"
#include "toy_parser.h"
#include "toy_compiler.h"
#include "toy_literal.h"
#include "toy_literal_array.h"
#include "toy_literal_dictionary.h"

/*!
 ## Other Components

 You probably won't use these directly, but they're a good learning opportunity.

 `Toy_Scope` holds the variables of a specific scope within Toy - be it a script, a function, a block, etc. Scopes are also where the type system lives at runtime. They use identifier literals as keys, exclusively.

 `Toy_RefString` is a utility class that wraps traditional C strings, making them less memory intensive and faster to copy and move. In reality, since strings are considered immutable, multiple variables can point to the same string to save memory, and you can just create a new one of these vars pointing to the original rather than copying entirely for a speed boost. This module has it's own memory allocator system that is plugged into the main memory allocator.

 `Toy_RefFunction` acts similarly to `Toy_RefString`, but instead operates on function bytecode.

 * [toy_scope.h](toy_scope_h.md)
 * [toy_refstring.h](toy_refstring_h.md)
 * [toy_reffunction.h](toy_reffunction_h.md)
 !*/

//#include "toy_scope.h"
//#include "toy_refstring.h"
//#include "toy_reffunction.h"

//#include "toy_interpreter.h"

#endif /* _TOY_H_ */
