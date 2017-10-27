/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "newbie.y" /* yacc.c:339  */


#include "newbie.h"
#include "newbie.tab.h"

extern int lex(void);
static int flag = 0;
int yylex(void)
{
    if (flag == 0)
    {
        flag++;
        return INT_LITERAL;
    }
    else if (flag == 1)
    {
        flag++;
        return SEMICOLON;
    }
    return lex();
}
void yyerror (char const *s)
{
    fprintf (stderr, "%s\n", s);
}

#line 93 "newbie.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "newbie.tab.h".  */
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
    FUNC_T = 283,
    IF = 284,
    ELSE = 285,
    ELSEIF = 286,
    FOR = 287,
    IN = 288,
    CLASS = 289,
    RETURN = 290,
    BREAK = 291,
    CONTINUE = 292,
    LP = 293,
    RP = 294,
    LC = 295,
    RC = 296,
    LB = 297,
    RB = 298,
    SEMICOLON = 299,
    COMMA = 300,
    ASSIGN_T = 301,
    EXCLAMATION = 302,
    DOT = 303,
    ADD_ASSIGN = 304,
    SUB_ASSIGN = 305,
    MUL_ASSIGN = 306,
    DIV_ASSIGN = 307,
    MOD_ASSIGN = 308,
    INCREMENT_T = 309,
    DECREMENT_T = 310,
    PUBLIC = 311,
    PROTECTED = 312,
    PRIVATE = 313
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
#define FUNC_T 283
#define IF 284
#define ELSE 285
#define ELSEIF 286
#define FOR 287
#define IN 288
#define CLASS 289
#define RETURN 290
#define BREAK 291
#define CONTINUE 292
#define LP 293
#define RP 294
#define LC 295
#define RC 296
#define LB 297
#define RB 298
#define SEMICOLON 299
#define COMMA 300
#define ASSIGN_T 301
#define EXCLAMATION 302
#define DOT 303
#define ADD_ASSIGN 304
#define SUB_ASSIGN 305
#define MUL_ASSIGN 306
#define DIV_ASSIGN 307
#define MOD_ASSIGN 308
#define INCREMENT_T 309
#define DECREMENT_T 310
#define PUBLIC 311
#define PROTECTED 312
#define PRIVATE 313

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 27 "newbie.y" /* yacc.c:355  */

    UTF8_String         *identifier;
    Expression          *expression;
    Statement           *statement;
    StatementsList       *statement_list;
    ParametersList       *parameter_list;
    ArgumentsList        *argument_list;

#line 258 "newbie.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_NEWBIE_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 275 "newbie.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  76
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   489

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  59
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  15
/* YYNRULES -- Number of rules.  */
#define YYNRULES  79
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  171

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   313

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    53,    53,    57,    62,    66,    70,    74,    78,    82,
      86,    90,    94,    98,   102,   103,   105,   106,   107,   108,
     109,   110,   111,   115,   121,   124,   126,   130,   134,   138,
     142,   146,   150,   154,   158,   162,   166,   170,   174,   179,
     183,   187,   191,   196,   201,   205,   209,   213,   217,   221,
     225,   229,   233,   237,   241,   245,   250,   254,   258,   262,
     266,   270,   275,   276,   277,   278,   280,   284,   288,   292,
     296,   300,   305,   309,   315,   318,   322,   328,   331,   335
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "LOGICAL_AND", "LOGICAL_OR", "EQ_T",
  "NE_T", "GT_T", "GE_T", "LT_T", "LE_T", "ADD_T", "SUB_T", "MUL_T",
  "DIV_T", "MOD_T", "UMINUS", "INT_LITERAL", "STRING_LITERAL",
  "DOUBLE_LITERAL", "BOOL_LITERAL", "IDENTIFIER", "INT_T", "DOUBLE_T",
  "BOOL_T", "STRING_T", "ARRAY_T", "VAR_T", "FUNC_T", "IF", "ELSE",
  "ELSEIF", "FOR", "IN", "CLASS", "RETURN", "BREAK", "CONTINUE", "LP",
  "RP", "LC", "RC", "LB", "RB", "SEMICOLON", "COMMA", "ASSIGN_T",
  "EXCLAMATION", "DOT", "ADD_ASSIGN", "SUB_ASSIGN", "MUL_ASSIGN",
  "DIV_ASSIGN", "MOD_ASSIGN", "INCREMENT_T", "DECREMENT_T", "PUBLIC",
  "PROTECTED", "PRIVATE", "$accept", "statement_list", "statement",
  "expression", "expression_optional", "binary_expression",
  "unary_expression", "function_call_expression", "declaration_expression",
  "assignment_expression", "primary_expression",
  "function_definition_statement", "block", "argument_list",
  "parameter_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313
};
# endif

#define YYPACT_NINF -143

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-143)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     312,   343,  -143,  -143,  -143,  -143,   373,   -17,    -9,    -6,
       4,    18,    19,    28,    16,    21,    24,    26,    35,   343,
      25,    32,   343,   250,   343,   149,  -143,    23,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,  -143,    49,    82,    83,   111,
     114,  -143,   343,   343,   343,   343,   343,   343,   343,  -143,
    -143,    22,  -143,   391,  -143,   400,  -143,   409,  -143,   418,
    -143,   142,  -143,   104,   343,  -143,   343,   374,    21,    87,
    -143,  -143,   102,  -143,   281,  -143,  -143,  -143,   343,   343,
     343,   343,   343,   343,   343,   343,   343,   343,   343,   343,
     343,  -143,   142,   142,   142,   142,   142,   469,   -28,   469,
     469,   469,   469,   469,   469,   408,   408,   408,   408,   408,
     408,   194,   207,   190,   469,   106,  -143,  -143,  -143,  -143,
     113,   113,   402,   402,   402,   402,   402,   402,   132,   132,
    -143,  -143,  -143,  -143,   343,  -143,   -26,   -25,   -23,    12,
      13,    14,    21,    21,   343,   343,   469,    21,   408,    21,
      21,    21,    21,    21,  -143,  -143,   244,   107,  -143,  -143,
    -143,  -143,  -143,  -143,  -143,    21,   343,  -143,   109,    21,
    -143
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,    62,    64,    63,    65,    23,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     2,     0,    18,    19,
      21,    17,    16,    20,    15,    14,     0,     0,     0,     0,
       0,    39,    74,     0,     0,     0,     0,     0,     0,    41,
      42,    44,    50,    45,    51,    46,    52,    47,    53,    48,
      54,    49,    55,     0,     0,     6,     0,    24,     0,     0,
      12,    11,     0,    73,     0,    40,     1,     3,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     4,    44,    45,    46,    47,    48,    75,     0,    56,
      57,    58,    59,    60,    61,    77,    77,    77,    77,    77,
      77,     0,     0,    23,    25,     0,    13,    10,    22,    72,
      37,    38,    31,    32,    33,    34,    35,    36,    26,    27,
      28,    29,    30,    43,     0,    78,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    24,    76,     0,     0,     0,
       0,     0,     0,     0,     5,     7,     0,     0,    66,    79,
      67,    68,    69,    70,    71,     0,    24,     8,     0,     0,
       9
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -143,   130,   -24,    -1,  -142,  -143,  -143,  -143,  -100,   366,
    -143,  -143,   -13,  -143,   379
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    27,   115,    28,    29,    30,    31,    32,
      33,    34,    35,    98,   136
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      41,    77,    65,   157,    51,   135,   135,   135,   135,   135,
     135,   133,    53,   147,   149,    55,   150,   134,    69,   148,
     148,    72,   148,    75,   168,    57,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,    59,
      61,    97,    99,   100,   101,   102,   103,   104,   159,    63,
      77,   151,   152,   153,    64,   116,    68,   148,   148,   148,
     105,    23,    66,   111,    67,   112,   114,    91,    43,    70,
      92,    44,    45,    46,    47,    48,    71,   120,   121,   122,
     123,   124,   125,   126,   127,   128,   129,   130,   131,   132,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,    93,    94,    78,    79,    80,    81,    82,
      83,    84,    85,    86,    87,    88,    89,    90,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    90,   154,
     155,   117,    95,   146,   158,    96,   160,   161,   162,   163,
     164,   118,   110,   156,   114,    88,    89,    90,   169,    76,
     145,   166,   167,    74,     0,     0,   170,     0,     0,     0,
       0,     1,     0,     0,     0,   114,     2,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      16,    17,     0,    18,    19,    20,    21,    22,    43,    23,
       0,    44,    45,    46,    47,    48,    24,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    90,   144,     0,     0,     0,     0,    42,     0,
       0,     0,     0,   142,     0,     0,    43,     0,     0,    44,
      45,    46,    47,    48,    49,    50,   143,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
       0,     0,     1,     0,     0,     0,     0,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,   165,    18,    19,    20,    21,    22,     0,
      23,    73,     0,     1,     0,     0,     0,    24,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    17,     0,    18,    19,    20,    21,    22,
       0,    23,   119,     0,     1,     0,     0,     0,    24,     2,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    16,    17,     0,    18,    19,    20,    21,
      22,     0,    23,     0,     0,     1,     0,     0,     0,    24,
       2,     3,     4,     5,     6,    36,    37,    38,    39,    40,
      12,     0,     0,    52,    54,    56,    58,    60,    62,     0,
       0,    22,     0,     0,     0,     0,     1,     0,     0,     0,
      24,     2,     3,     4,     5,   113,    36,    37,    38,    39,
      40,    12,    52,    54,    56,    58,    60,     0,     0,     0,
       0,    42,    22,    86,    87,    88,    89,    90,     0,    43,
       0,    24,    44,    45,    46,    47,    48,    49,    50,   106,
      36,    37,    38,    39,    40,    12,     0,    43,   107,     0,
      44,    45,    46,    47,    48,     0,    43,   108,     0,    44,
      45,    46,    47,    48,     0,    43,   109,     0,    44,    45,
      46,    47,    48,     0,    43,     0,     0,    44,    45,    46,
      47,    48,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    87,    88,    89,    90,   137,   138,   139,   140,   141
};

static const yytype_int16 yycheck[] =
{
       1,    25,    15,   145,    21,   105,   106,   107,   108,   109,
     110,    39,    21,    39,    39,    21,    39,    45,    19,    45,
      45,    22,    45,    24,   166,    21,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    21,
      21,    42,    43,    44,    45,    46,    47,    48,   148,    21,
      74,    39,    39,    39,    38,    68,    21,    45,    45,    45,
      38,    40,    38,    64,    38,    66,    67,    44,    46,    44,
      21,    49,    50,    51,    52,    53,    44,    78,    79,    80,
      81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    21,    21,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,    15,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,   142,
     143,    44,    21,   134,   147,    21,   149,   150,   151,   152,
     153,    39,    38,   144,   145,    13,    14,    15,    39,     0,
      44,    44,   165,    23,    -1,    -1,   169,    -1,    -1,    -1,
      -1,    12,    -1,    -1,    -1,   166,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    29,    30,
      31,    32,    -1,    34,    35,    36,    37,    38,    46,    40,
      -1,    49,    50,    51,    52,    53,    47,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
       3,     4,     5,     6,     7,     8,     9,    10,    11,    12,
      13,    14,    15,    33,    -1,    -1,    -1,    -1,    38,    -1,
      -1,    -1,    -1,    39,    -1,    -1,    46,    -1,    -1,    49,
      50,    51,    52,    53,    54,    55,    39,     3,     4,     5,
       6,     7,     8,     9,    10,    11,    12,    13,    14,    15,
      -1,    -1,    12,    -1,    -1,    -1,    -1,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    29,
      30,    31,    32,    39,    34,    35,    36,    37,    38,    -1,
      40,    41,    -1,    12,    -1,    -1,    -1,    47,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      29,    30,    31,    32,    -1,    34,    35,    36,    37,    38,
      -1,    40,    41,    -1,    12,    -1,    -1,    -1,    47,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    29,    30,    31,    32,    -1,    34,    35,    36,    37,
      38,    -1,    40,    -1,    -1,    12,    -1,    -1,    -1,    47,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    -1,    -1,     7,     8,     9,    10,    11,    12,    -1,
      -1,    38,    -1,    -1,    -1,    -1,    12,    -1,    -1,    -1,
      47,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    36,    37,    38,    39,    40,    -1,    -1,    -1,
      -1,    38,    38,    11,    12,    13,    14,    15,    -1,    46,
      -1,    47,    49,    50,    51,    52,    53,    54,    55,    38,
      22,    23,    24,    25,    26,    27,    -1,    46,    38,    -1,
      49,    50,    51,    52,    53,    -1,    46,    38,    -1,    49,
      50,    51,    52,    53,    -1,    46,    38,    -1,    49,    50,
      51,    52,    53,    -1,    46,    -1,    -1,    49,    50,    51,
      52,    53,     3,     4,     5,     6,     7,     8,     9,    10,
      11,    12,    13,    14,    15,   106,   107,   108,   109,   110
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    12,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    34,    35,
      36,    37,    38,    40,    47,    60,    61,    62,    64,    65,
      66,    67,    68,    69,    70,    71,    22,    23,    24,    25,
      26,    62,    38,    46,    49,    50,    51,    52,    53,    54,
      55,    21,    68,    21,    68,    21,    68,    21,    68,    21,
      68,    21,    68,    21,    38,    71,    38,    38,    21,    62,
      44,    44,    62,    41,    60,    62,     0,    61,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    44,    21,    21,    21,    21,    21,    62,    72,    62,
      62,    62,    62,    62,    62,    38,    38,    38,    38,    38,
      38,    62,    62,    21,    62,    63,    71,    44,    39,    41,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    39,    45,    67,    73,    73,    73,    73,
      73,    73,    39,    39,    33,    44,    62,    39,    45,    39,
      39,    39,    39,    39,    71,    71,    62,    63,    71,    67,
      71,    71,    71,    71,    71,    39,    44,    71,    63,    39,
      71
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    59,    60,    60,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    62,    62,    62,    62,
      62,    62,    62,    62,    63,    63,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    65,
      65,    65,    65,    66,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    67,    67,    67,    68,    68,    68,    68,
      68,    68,    69,    69,    69,    69,    70,    70,    70,    70,
      70,    70,    71,    71,    72,    72,    72,    73,    73,    73
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     5,     2,     5,     7,     9,
       3,     2,     2,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     1,     0,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     2,     4,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     3,     3,     3,     3,
       3,     3,     1,     1,     1,     1,     6,     6,     6,     6,
       6,     6,     3,     2,     0,     1,     3,     0,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 54 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement_list) = nb_create_statement_list((yyvsp[0].statement));
        }
#line 1536 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 58 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement_list) = nb_cat_statement_list((yyvsp[-1].statement_list), (yyvsp[0].statement));
        }
#line 1544 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 63 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_expression_statement((yyvsp[-1].expression));
        }
#line 1552 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 67 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_if_statement((yyvsp[-2].expression), (yyvsp[0].statement));
        }
#line 1560 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 71 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_cat_else_statement((yyvsp[0].statement));
        }
#line 1568 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 75 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_cat_elseif_statement((yyvsp[-2].expression), (yyvsp[0].statement));
        }
#line 1576 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 79 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_foreach_statement((yyvsp[-4].identifier), (yyvsp[-2].expression), (yyvsp[0].statement));
        }
#line 1584 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 83 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_for_statement((yyvsp[-6].expression), (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].statement));
        }
#line 1592 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 87 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_return_statement((yyvsp[-1].expression));
        }
#line 1600 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 91 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_continue_statement();
        }
#line 1608 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 95 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_break_statement();
        }
#line 1616 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 99 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_class_definition_statement((yyvsp[-1].identifier), (yyvsp[0].statement));
        }
#line 1624 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 112 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = (yyvsp[-1].expression);
        }
#line 1632 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 116 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_identifier_expression((yyvsp[0].identifier));
        }
#line 1640 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 121 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = NULL;
        }
#line 1648 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 127 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(ADD, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1656 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 131 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(SUB, (yyvsp[-2].expression), (yyvsp[0].expression));            
        }
#line 1664 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 135 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(MUL, (yyvsp[-2].expression), (yyvsp[0].expression));            
        }
#line 1672 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 139 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(DIV, (yyvsp[-2].expression), (yyvsp[0].expression));            
        }
#line 1680 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 143 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(MOD, (yyvsp[-2].expression), (yyvsp[0].expression));            
        }
#line 1688 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 147 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(EQ, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1696 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 151 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(NE, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1704 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 155 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(GT, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1712 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 159 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(GE, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1720 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 163 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(LT, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1728 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 167 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(LE, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1736 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 171 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(AND, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1744 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 175 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(OR, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1752 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 180 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_unary_expression(MINUS, (yyvsp[0].expression));
        }
#line 1760 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 184 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_unary_expression(NOT, (yyvsp[0].expression));
        }
#line 1768 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 188 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_change_expression(INCREMENT, (yyvsp[-1].identifier));
        }
#line 1776 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 192 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_change_expression(DECREMENT, (yyvsp[-1].identifier));
        }
#line 1784 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 197 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_function_call_expression((yyvsp[-3].identifier), (yyvsp[-1].argument_list));
        }
#line 1792 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 202 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(INT, (yyvsp[0].identifier), NULL);
        }
#line 1800 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 206 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(DOUBLE, (yyvsp[0].identifier), NULL);
        }
#line 1808 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 210 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(BOOL, (yyvsp[0].identifier), NULL);
        }
#line 1816 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 214 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(STRING, (yyvsp[0].identifier), NULL);
        }
#line 1824 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 218 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(ARRAY, (yyvsp[0].identifier), NULL);
        }
#line 1832 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 222 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(VARIOUS, (yyvsp[0].identifier), NULL);
        }
#line 1840 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 226 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(INT, NULL, (yyvsp[0].expression));
        }
#line 1848 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 230 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(DOUBLE, NULL, (yyvsp[0].expression));
        }
#line 1856 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 234 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(BOOL, NULL, (yyvsp[0].expression));
        }
#line 1864 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 238 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(STRING, NULL, (yyvsp[0].expression));
        }
#line 1872 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 242 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(ARRAY, NULL, (yyvsp[0].expression));
        }
#line 1880 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 246 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(VARIOUS, NULL, (yyvsp[0].expression));
        }
#line 1888 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 251 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_assignment_expression((yyvsp[-2].identifier), (yyvsp[0].expression));
        }
#line 1896 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 255 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_assignment_expression((yyvsp[-2].identifier), nb_create_binary_expression(ADD, nb_create_identifier_expression(utf8_string_copy_new((yyvsp[-2].identifier))), (yyvsp[0].expression)));
        }
#line 1904 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 259 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_assignment_expression((yyvsp[-2].identifier), nb_create_binary_expression(SUB, nb_create_identifier_expression(utf8_string_copy_new((yyvsp[-2].identifier))), (yyvsp[0].expression)));
        }
#line 1912 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 263 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_assignment_expression((yyvsp[-2].identifier), nb_create_binary_expression(MUL, nb_create_identifier_expression(utf8_string_copy_new((yyvsp[-2].identifier))), (yyvsp[0].expression)));
        }
#line 1920 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 267 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_assignment_expression((yyvsp[-2].identifier), nb_create_binary_expression(DIV, nb_create_identifier_expression(utf8_string_copy_new((yyvsp[-2].identifier))), (yyvsp[0].expression)));
        }
#line 1928 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 271 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_assignment_expression((yyvsp[-2].identifier), nb_create_binary_expression(MOD, nb_create_identifier_expression(utf8_string_copy_new((yyvsp[-2].identifier))), (yyvsp[0].expression)));
        }
#line 1936 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 281 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_function_definition_statement(INT, (yyvsp[-4].identifier), (yyvsp[-2].parameter_list), (yyvsp[0].statement));
        }
#line 1944 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 285 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_function_definition_statement(DOUBLE, (yyvsp[-4].identifier), (yyvsp[-2].parameter_list), (yyvsp[0].statement));
        }
#line 1952 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 289 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_function_definition_statement(BOOL, (yyvsp[-4].identifier), (yyvsp[-2].parameter_list), (yyvsp[0].statement));
        }
#line 1960 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 293 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_function_definition_statement(STRING, (yyvsp[-4].identifier), (yyvsp[-2].parameter_list), (yyvsp[0].statement));
        }
#line 1968 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 297 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_function_definition_statement(ARRAY, (yyvsp[-4].identifier), (yyvsp[-2].parameter_list), (yyvsp[0].statement));
        }
#line 1976 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 301 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_function_definition_statement(VARIOUS, (yyvsp[-4].identifier), (yyvsp[-2].parameter_list), (yyvsp[0].statement));
        }
#line 1984 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 306 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_block_statement((yyvsp[-1].statement_list));
        }
#line 1992 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 310 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_block_statement(NULL);
        }
#line 2000 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 315 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.argument_list) = NULL;
        }
#line 2008 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 319 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.argument_list) = nb_create_argument_list((yyvsp[0].expression));
        }
#line 2016 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 323 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.argument_list) = nb_cat_argument_list((yyvsp[-2].argument_list), (yyvsp[0].expression));
        }
#line 2024 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 328 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.parameter_list) = NULL;
        }
#line 2032 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 332 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.parameter_list) = nb_create_parameter_list((yyvsp[0].expression));
        }
#line 2040 "newbie.tab.c" /* yacc.c:1646  */
    break;

  case 79:
#line 336 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.parameter_list) = nb_cat_parameter_list((yyvsp[-2].parameter_list), (yyvsp[0].expression));
        }
#line 2048 "newbie.tab.c" /* yacc.c:1646  */
    break;


#line 2052 "newbie.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 340 "newbie.y" /* yacc.c:1906  */