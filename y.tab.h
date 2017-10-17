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
    BOOL_LITERAL = 261,
    IDENTIFIER = 262,
    INT_T = 263,
    DOUBLE_T = 264,
    BOOL_T = 265,
    STRING_T = 266,
    ARRAY_T = 267,
    IF = 268,
    ELSE = 269,
    ELSEIF = 270,
    FOR = 271,
    IN = 272,
    CLASS = 273,
    RETURN_T = 274,
    BREAK = 275,
    CONTINUE = 276,
    LP = 277,
    RP = 278,
    LC = 279,
    RC = 280,
    LB = 281,
    RB = 282,
    SEMICOLON = 283,
    COMMA = 284,
    ASSIGN_T = 285,
    LOGICAL_AND = 286,
    LOGICAL_OR = 287,
    EQ_T = 288,
    NE_T = 289,
    GT_T = 290,
    GE_T = 291,
    LT_T = 292,
    LE_T = 293,
    ADD_T = 294,
    SUB_T = 295,
    MUL_T = 296,
    DIV_T = 297,
    MOD_T = 298,
    EXCLAMATION = 299,
    DOT = 300,
    ADD_ASSIGN = 301,
    SUB_ASSIGN = 302,
    MUL_ASSIGN = 303,
    DIV_ASSIGN = 304,
    MOD_ASSIGN = 305,
    INCREMENT = 306,
    DECREMENT = 307
  };
#endif
/* Tokens.  */
#define INT_LITERAL 258
#define STRING_LITERAL 259
#define DOUBLE_LITERAL 260
#define BOOL_LITERAL 261
#define IDENTIFIER 262
#define INT_T 263
#define DOUBLE_T 264
#define BOOL_T 265
#define STRING_T 266
#define ARRAY_T 267
#define IF 268
#define ELSE 269
#define ELSEIF 270
#define FOR 271
#define IN 272
#define CLASS 273
#define RETURN_T 274
#define BREAK 275
#define CONTINUE 276
#define LP 277
#define RP 278
#define LC 279
#define RC 280
#define LB 281
#define RB 282
#define SEMICOLON 283
#define COMMA 284
#define ASSIGN_T 285
#define LOGICAL_AND 286
#define LOGICAL_OR 287
#define EQ_T 288
#define NE_T 289
#define GT_T 290
#define GE_T 291
#define LT_T 292
#define LE_T 293
#define ADD_T 294
#define SUB_T 295
#define MUL_T 296
#define DIV_T 297
#define MOD_T 298
#define EXCLAMATION 299
#define DOT 300
#define ADD_ASSIGN 301
#define SUB_ASSIGN 302
#define MUL_ASSIGN 303
#define DIV_ASSIGN 304
#define MOD_ASSIGN 305
#define INCREMENT 306
#define DECREMENT 307

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 13 "newbie.y" /* yacc.c:1909  */

    UTF8_String         *identifier;
    Expression          *expression;
    Statement           *statement;
    StatementList       *statement_list;

#line 165 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
