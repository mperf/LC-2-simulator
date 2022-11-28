/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     REGISTER = 258,
     RETS = 259,
     EOF = 260,
     LDST = 261,
     NOT = 262,
     LABEL = 263,
     NUMBERS = 264,
     ORIG = 265,
     COMMENT = 266,
     JUMP = 267,
     COMMA = 268,
     ADDR = 269,
     END = 270,
     BLKW = 271,
     STRINGZ = 272,
     BINARY = 273,
     NUM = 274,
     FILL = 275,
     STR = 276,
     JSR = 277,
     JSRR = 278,
     IMOP = 279,
     BSOP = 280,
     TRAP = 281
   };
#endif
/* Tokens.  */
#define REGISTER 258
#define RETS 259
#define EOF 260
#define LDST 261
#define NOT 262
#define LABEL 263
#define NUMBERS 264
#define ORIG 265
#define COMMENT 266
#define JUMP 267
#define COMMA 268
#define ADDR 269
#define END 270
#define BLKW 271
#define STRINGZ 272
#define BINARY 273
#define NUM 274
#define FILL 275
#define STR 276
#define JSR 277
#define JSRR 278
#define IMOP 279
#define BSOP 280
#define TRAP 281




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

