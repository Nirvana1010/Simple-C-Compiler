# Simple C Compiler

**Language:** C

**Tools:** Lex (lexical analysis), Yacc (grammar parser)

**Platform:** Visual Studio 2010

## Overview

This is a simple C compiler using Lex & Yacc, which is the course project of Principles of Compilers. The compiler handles following constructs:

- Data type: int, char
- Statements: assignment (=), if, while, for
- Arithmetic operations: +, -, *, / (%, ++, --, &, |, ^, ~, <<, >>)
- Relational operations: ==, >, <, >=, <=, ! =
- Logical operations: && (with), || (or), ! (not)
- Compound statements: statements enclosed by { and }
- Annotation statements
- Simple input and output

**Target:**

Generate x86 assembly language program from a C-program.