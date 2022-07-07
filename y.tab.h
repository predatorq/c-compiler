/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    T_Void = 258,                  /* T_Void  */
    T_Int = 259,                   /* T_Int  */
    T_While = 260,                 /* T_While  */
    T_If = 261,                    /* T_If  */
    T_Else = 262,                  /* T_Else  */
    T_Return = 263,                /* T_Return  */
    T_Break = 264,                 /* T_Break  */
    T_Continue = 265,              /* T_Continue  */
    T_Print = 266,                 /* T_Print  */
    T_ReadInt = 267,               /* T_ReadInt  */
    T_Le = 268,                    /* T_Le  */
    T_Ge = 269,                    /* T_Ge  */
    T_Eq = 270,                    /* T_Eq  */
    T_Ne = 271,                    /* T_Ne  */
    T_And = 272,                   /* T_And  */
    T_Or = 273,                    /* T_Or  */
    T_IntConstant = 274,           /* T_IntConstant  */
    T_StringConstant = 275,        /* T_StringConstant  */
    T_Identifier = 276             /* T_Identifier  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define T_Void 258
#define T_Int 259
#define T_While 260
#define T_If 261
#define T_Else 262
#define T_Return 263
#define T_Break 264
#define T_Continue 265
#define T_Print 266
#define T_ReadInt 267
#define T_Le 268
#define T_Ge 269
#define T_Eq 270
#define T_Ne 271
#define T_And 272
#define T_Or 273
#define T_IntConstant 274
#define T_StringConstant 275
#define T_Identifier 276

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
