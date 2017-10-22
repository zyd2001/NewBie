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
    LOGICAL_AND = 258,
    LOGICAL_OR = 259,
    EQ_T = 260,
    NE_T = 261,
    GT_T = 262,
    GE_T = 263,
    LT_T = 264,
    LE_T = 265,
    ADD_T = 266,
    SUB_T = 267,
    MUL_T = 268,
    DIV_T = 269,
    MOD_T = 270,
    UMINUS = 271,
    INT_LITERAL = 272,
    STRING_LITERAL = 273,
    DOUBLE_LITERAL = 274,
    BOOL_LITERAL = 275,
    IDENTIFIER = 276,
    INT_T = 277,
    DOUBLE_T = 278,
    BOOL_T = 279,
    STRING_T = 280,
    ARRAY_T = 281,
    IF = 282,
    ELSE = 283,
    ELSEIF = 284,
    FOR = 285,
    IN = 286,
    CLASS = 287,
    RETURN = 288,
    BREAK = 289,
    CONTINUE = 290,
    LP = 291,
    RP = 292,
    LC = 293,
    RC = 294,
    LB = 295,
    RB = 296,
    SEMICOLON = 297,
    COMMA = 298,
    ASSIGN_T = 299,
    EXCLAMATION = 300,
    DOT = 301,
    ADD_ASSIGN = 302,
    SUB_ASSIGN = 303,
    MUL_ASSIGN = 304,
    DIV_ASSIGN = 305,
    MOD_ASSIGN = 306,
    INCREMENT_T = 307,
    DECREMENT_T = 308
  };
#endif
/* Tokens.  */
#define LOGICAL_AND 258
#define LOGICAL_OR 259
#define EQ_T 260
#define NE_T 261
#define GT_T 262
#define GE_T 263
#define LT_T 264
#define LE_T 265
#define ADD_T 266
#define SUB_T 267
#define MUL_T 268
#define DIV_T 269
#define MOD_T 270
#define UMINUS 271
#define INT_LITERAL 272
#define STRING_LITERAL 273
#define DOUBLE_LITERAL 274
#define BOOL_LITERAL 275
#define IDENTIFIER 276
#define INT_T 277
#define DOUBLE_T 278
#define BOOL_T 279
#define STRING_T 280
#define ARRAY_T 281
#define IF 282
#define ELSE 283
#define ELSEIF 284
#define FOR 285
#define IN 286
#define CLASS 287
#define RETURN 288
#define BREAK 289
#define CONTINUE 290
#define LP 291
#define RP 292
#define LC 293
#define RC 294
#define LB 295
#define RB 296
#define SEMICOLON 297
#define COMMA 298
#define ASSIGN_T 299
#define EXCLAMATION 300
#define DOT 301
#define ADD_ASSIGN 302
#define SUB_ASSIGN 303
#define MUL_ASSIGN 304
#define DIV_ASSIGN 305
#define MOD_ASSIGN 306
#define INCREMENT_T 307
#define DECREMENT_T 308

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 27 "newbie.y" /* yacc.c:1909  */

    UTF8_String         *identifier;
    Expression          *expression;
    Statement           *statement;
    StatementList       *statement_list;
    ParameterList       *parameter_list;
    ArgumentList        *argument_list;

#line 169 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
