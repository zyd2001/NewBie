/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INT_LITERAL = 258,
    STRING_LITERAL = 259,
    DOUBLE_LITERAL = 260,
    IDENTIFIER = 261,
    INT_T = 262,
    DOUBLE_T = 263,
    STRING_T = 264,
    ARRAY_T = 265,
    IF = 266,
    ELSE = 267,
    ELSEIF = 268,
    FOR = 269,
    IN = 270,
    CLASS = 271,
    RETURN_T = 272,
    BREAK = 273,
    CONTINUE = 274,
    LP = 275,
    RP = 276,
    LC = 277,
    RC = 278,
    LB = 279,
    RB = 280,
    SEMICOLON = 281,
    COMMA = 282,
    ASSIGN_T = 283,
    LOGICAL_AND = 284,
    LOGICAL_OR = 285,
    EQ_T = 286,
    NE_T = 287,
    GT_T = 288,
    GE_T = 289,
    LT_T = 290,
    LE_T = 291,
    ADD_T = 292,
    SUB_T = 293,
    MUL_T = 294,
    DIV_T = 295,
    MOD_T = 296,
    EXCLAMATION = 297,
    DOT = 298,
    ADD_ASSIGN = 299,
    SUB_ASSIGN = 300,
    MUL_ASSIGN = 301,
    DIV_ASSIGN = 302,
    MOD_ASSIGN = 303,
    INCREMENT = 304,
    DECREMENT = 305
  };
#endif
/* Tokens.  */
#define INT_LITERAL 258
#define STRING_LITERAL 259
#define DOUBLE_LITERAL 260
#define IDENTIFIER 261
#define INT_T 262
#define DOUBLE_T 263
#define STRING_T 264
#define ARRAY_T 265
#define IF 266
#define ELSE 267
#define ELSEIF 268
#define FOR 269
#define IN 270
#define CLASS 271
#define RETURN_T 272
#define BREAK 273
#define CONTINUE 274
#define LP 275
#define RP 276
#define LC 277
#define RC 278
#define LB 279
#define RB 280
#define SEMICOLON 281
#define COMMA 282
#define ASSIGN_T 283
#define LOGICAL_AND 284
#define LOGICAL_OR 285
#define EQ_T 286
#define NE_T 287
#define GT_T 288
#define GE_T 289
#define LT_T 290
#define LE_T 291
#define ADD_T 292
#define SUB_T 293
#define MUL_T 294
#define DIV_T 295
#define MOD_T 296
#define EXCLAMATION 297
#define DOT 298
#define ADD_ASSIGN 299
#define SUB_ASSIGN 300
#define MUL_ASSIGN 301
#define DIV_ASSIGN 302
#define MOD_ASSIGN 303
#define INCREMENT 304
#define DECREMENT 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 14 "newbie.y" /* yacc.c:1909  */

    UTF8_String         *identifier;
    Expression          *expression;
    Statement           *statement;
    StatementList       *statement_list;

#line 161 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
