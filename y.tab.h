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
    ARRAY_ASSOC_T = 266,
    IF = 267,
    ELSE = 268,
    ELSEIF = 269,
    FOR = 270,
    IN = 271,
    CLASS = 272,
    RETURN = 273,
    BREAK = 274,
    CONTINUE = 275,
    LP = 276,
    RP = 277,
    LC = 278,
    RC = 279,
    LB = 280,
    RB = 281,
    SEMICOLON = 282,
    COMMA = 283,
    ASSIGN_T = 284,
    LOGICAL_AND = 285,
    LOGICAL_OR = 286,
    EQ = 287,
    NE = 288,
    GT = 289,
    GE = 290,
    LT = 291,
    LE = 292,
    ADD = 293,
    SUB = 294,
    MUL = 295,
    DIV = 296,
    MOD = 297,
    EXCLAMATION = 298,
    DOT = 299,
    ADD_ASSIGN = 300,
    SUB_ASSIGN = 301,
    MUL_ASSIGN = 302,
    DIV_ASSIGN = 303,
    MOD_ASSIGN = 304,
    INCREMENT = 305,
    DECREMENT = 306
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
#define ARRAY_ASSOC_T 266
#define IF 267
#define ELSE 268
#define ELSEIF 269
#define FOR 270
#define IN 271
#define CLASS 272
#define RETURN 273
#define BREAK 274
#define CONTINUE 275
#define LP 276
#define RP 277
#define LC 278
#define RC 279
#define LB 280
#define RB 281
#define SEMICOLON 282
#define COMMA 283
#define ASSIGN_T 284
#define LOGICAL_AND 285
#define LOGICAL_OR 286
#define EQ 287
#define NE 288
#define GT 289
#define GE 290
#define LT 291
#define LE 292
#define ADD 293
#define SUB 294
#define MUL 295
#define DIV 296
#define MOD 297
#define EXCLAMATION 298
#define DOT 299
#define ADD_ASSIGN 300
#define SUB_ASSIGN 301
#define MUL_ASSIGN 302
#define DIV_ASSIGN 303
#define MOD_ASSIGN 304
#define INCREMENT 305
#define DECREMENT 306

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 8 "newbie.y" /* yacc.c:1909  */

    char                *identifier;
    ParameterList       *parameter_list;
    ArgumentList        *argument_list;
    Expression          *expression;
    Statement           *statement;
    StatementList       *statement_list;
    Block               *block;
    Elseif              *elseif;
    IdentifierList      *identifier_list;

#line 168 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
