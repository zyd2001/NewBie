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

#ifndef YY_YY_NEWBIE_TAB_H_INCLUDED
# define YY_YY_NEWBIE_TAB_H_INCLUDED
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
    VAR_T = 282,
    IF = 283,
    ELSE = 284,
    ELSEIF = 285,
    FOR = 286,
    IN = 287,
    CLASS = 288,
    RETURN = 289,
    BREAK = 290,
    CONTINUE = 291,
    LP = 292,
    RP = 293,
    LC = 294,
    RC = 295,
    LB = 296,
    RB = 297,
    SEMICOLON = 298,
    COMMA = 299,
    ASSIGN_T = 300,
    EXCLAMATION = 301,
    DOT = 302,
    ADD_ASSIGN = 303,
    SUB_ASSIGN = 304,
    MUL_ASSIGN = 305,
    DIV_ASSIGN = 306,
    MOD_ASSIGN = 307,
    INCREMENT_T = 308,
    DECREMENT_T = 309,
    PUBLIC = 310,
    PROTECTED = 311,
    PRIVATE = 312,
    REVERSE = 313
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
#define VAR_T 282
#define IF 283
#define ELSE 284
#define ELSEIF 285
#define FOR 286
#define IN 287
#define CLASS 288
#define RETURN 289
#define BREAK 290
#define CONTINUE 291
#define LP 292
#define RP 293
#define LC 294
#define RC 295
#define LB 296
#define RB 297
#define SEMICOLON 298
#define COMMA 299
#define ASSIGN_T 300
#define EXCLAMATION 301
#define DOT 302
#define ADD_ASSIGN 303
#define SUB_ASSIGN 304
#define MUL_ASSIGN 305
#define DIV_ASSIGN 306
#define MOD_ASSIGN 307
#define INCREMENT_T 308
#define DECREMENT_T 309
#define PUBLIC 310
#define PROTECTED 311
#define PRIVATE 312
#define REVERSE 313

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 27 "newbie.y" /* yacc.c:1909  */

    UTF8_String         *identifier;
    Expression          *expression;
    Statement           *statement;
    StatementsList      *statement_list;
    ParametersList      *parameter_list;
    ArgumentsList       *argument_list;
    ExpressionList      *expression_list;
    NB_ValueType        type;

#line 181 "newbie.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_NEWBIE_TAB_H_INCLUDED  */
