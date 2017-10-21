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
#include "y.tab.h"

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

#line 93 "y.tab.c" /* yacc.c:339  */

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
   by #include "y.tab.h".  */
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
    RETURN = 274,
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
#define RETURN 274
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
#line 27 "newbie.y" /* yacc.c:355  */

    UTF8_String         *identifier;
    Expression          *expression;
    Statement           *statement;
    StatementList       *statement_list;
    ParameterList       *parameter_list;
    ArgumentList        *argument_list;

#line 246 "y.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 263 "y.tab.c" /* yacc.c:358  */

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
#define YYFINAL  62
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   408

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  165

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   307

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
      45,    46,    47,    48,    49,    50,    51,    52
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    49,    49,    53,    58,    62,    66,    70,    74,    78,
      82,    86,    90,    94,    95,    97,    98,    99,   100,   101,
     102,   108,   111,   113,   117,   121,   125,   129,   133,   137,
     141,   145,   149,   153,   158,   163,   167,   171,   175,   179,
     183,   187,   191,   195,   199,   204,   208,   212,   216,   220,
     224,   228,   232,   237,   238,   239,   240,   242,   246,   250,
     254,   258,   263,   267,   272,   276,   282,   285,   289,   293,
     297,   301,   305,   309,   313,   317,   321
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "INT_LITERAL", "STRING_LITERAL",
  "DOUBLE_LITERAL", "BOOL_LITERAL", "IDENTIFIER", "INT_T", "DOUBLE_T",
  "BOOL_T", "STRING_T", "ARRAY_T", "IF", "ELSE", "ELSEIF", "FOR", "IN",
  "CLASS", "RETURN", "BREAK", "CONTINUE", "LP", "RP", "LC", "RC", "LB",
  "RB", "SEMICOLON", "COMMA", "ASSIGN_T", "LOGICAL_AND", "LOGICAL_OR",
  "EQ_T", "NE_T", "GT_T", "GE_T", "LT_T", "LE_T", "ADD_T", "SUB_T",
  "MUL_T", "DIV_T", "MOD_T", "EXCLAMATION", "DOT", "ADD_ASSIGN",
  "SUB_ASSIGN", "MUL_ASSIGN", "DIV_ASSIGN", "MOD_ASSIGN", "INCREMENT",
  "DECREMENT", "$accept", "statement_list", "statement", "expression",
  "expression_optional", "binary_expression", "function_call_expression",
  "declaration_expression", "assignment_expression", "primary_expression",
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
     305,   306,   307
};
# endif

#define YYPACT_NINF -118

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-118)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     276,  -118,  -118,  -118,  -118,   -16,    -2,     0,     4,     5,
       6,    -7,    -8,    -5,    20,    41,    13,    39,   230,   208,
    -118,   328,  -118,  -118,  -118,  -118,  -118,  -118,  -118,    41,
      41,    41,    41,    41,    41,    41,  -118,  -118,   109,  -118,
     118,  -118,   132,  -118,   141,  -118,   155,  -118,    41,  -118,
      41,   396,    61,    62,    69,    70,    72,   344,  -118,  -118,
    -118,   253,  -118,  -118,  -118,    41,    41,    41,    41,    41,
      41,    41,    41,    41,    41,    41,   355,   -21,   355,   355,
     355,   355,   355,   355,    81,    81,    81,    81,    81,   270,
     291,    48,   355,    52,    36,    36,    36,    36,    36,  -118,
    -118,   355,   355,   355,   355,   355,   355,   355,   355,   355,
     355,   355,  -118,    41,    41,    41,    41,    41,    41,   -20,
      85,    88,   100,   120,    -8,    -8,    41,    41,   355,   355,
     355,   355,   355,   355,    -8,   164,    -8,    -8,    -8,    -8,
    -118,  -118,   312,    53,  -118,    41,    41,    41,    41,    41,
    -118,  -118,  -118,  -118,    -8,    41,   355,   355,   355,   355,
     355,  -118,    78,    -8,  -118
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,    53,    55,    54,    56,    20,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       2,     0,    17,    19,    16,    15,    18,    14,    13,     0,
       0,     0,     0,     0,     0,     0,    51,    52,    35,    40,
      36,    41,    37,    42,    38,    43,    39,    44,     0,     6,
       0,    21,     0,     0,     0,     0,     0,     0,    12,    11,
      63,     0,     1,     3,     4,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    64,     0,    45,    46,
      47,    48,    49,    50,    66,    66,    66,    66,    66,     0,
       0,    20,    22,     0,    35,    36,    37,    38,    39,    10,
      62,    28,    29,    30,    31,    32,    33,    23,    24,    25,
      26,    27,    34,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    21,    65,    67,
      68,    69,    70,    71,     0,     0,     0,     0,     0,     0,
       5,     7,     0,     0,    57,     0,     0,     0,     0,     0,
      58,    59,    60,    61,     0,    21,    72,    73,    74,    75,
      76,     8,     0,     0,     9
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
    -118,    91,   -18,   -11,  -117,  -118,  -118,  -118,    19,  -118,
    -118,   -12,  -118,    33
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    19,    20,    21,    93,    22,    23,    24,    25,    26,
      27,    28,    77,   119
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      49,    63,   112,   134,    57,    38,    29,    40,   113,   135,
     143,    42,    44,    46,    30,    48,    18,    50,    76,    78,
      79,    80,    81,    82,    83,    39,    41,    43,    45,    47,
      31,    32,    33,    34,    35,    36,    37,    89,   162,    90,
      92,    58,    51,    63,     1,     2,     3,     4,     5,    52,
      53,    54,    55,    56,   101,   102,   103,   104,   105,   106,
     107,   108,   109,   110,   111,   126,    30,    59,    94,    95,
      29,    39,    41,    43,    45,    47,    96,    97,    30,    98,
     127,   155,    31,    32,    33,    34,    35,    36,    37,   114,
     115,   116,   117,   118,    31,    32,    33,    34,    35,    36,
      37,   163,   128,   129,   130,   131,   132,   133,   136,    61,
       0,   137,   140,   141,   135,   142,    92,   135,   120,   121,
     122,   123,   144,   138,   150,   151,   152,   153,     0,   135,
       0,    84,     0,     0,   156,   157,   158,   159,   160,    30,
      85,     0,   161,   139,    92,     0,     0,     0,    30,   135,
       0,   164,     0,     0,    86,    31,    32,    33,    34,    35,
      36,    37,    30,    87,    31,    32,    33,    34,    35,    36,
      37,    30,   145,   146,   147,   148,   149,    88,    31,    32,
      33,    34,    35,    36,    37,    30,     0,    31,    32,    33,
      34,    35,    36,    37,     0,     0,     0,     0,     0,     0,
       0,    31,    32,    33,    34,    35,    36,    37,    62,     0,
       0,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,     0,     0,    15,    16,    17,
       0,     0,    18,     1,     2,     3,     4,     5,     6,     7,
       8,     9,    10,    11,    12,    13,    14,     0,     0,    15,
      16,    17,     0,     0,    18,    60,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
       0,     0,    15,    16,    17,     0,     0,    18,   100,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,   124,     0,    15,    16,    17,     0,     0,
      18,     0,     0,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,   125,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,   154,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    64,     0,     0,     0,
       0,    65,    66,    67,    68,    69,    70,    71,    72,    73,
      74,    75,    99,     0,     0,     0,     0,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,     1,
       2,     3,     4,    91,    52,    53,    54,    55,    56
};

static const yytype_int16 yycheck[] =
{
      12,    19,    23,    23,    15,     7,    22,     7,    29,    29,
     127,     7,     7,     7,    30,    22,    24,    22,    29,    30,
      31,    32,    33,    34,    35,     6,     7,     8,     9,    10,
      46,    47,    48,    49,    50,    51,    52,    48,   155,    50,
      51,    28,    22,    61,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    17,    30,    28,     7,     7,
      22,    52,    53,    54,    55,    56,     7,     7,    30,     7,
      28,    28,    46,    47,    48,    49,    50,    51,    52,     8,
       9,    10,    11,    12,    46,    47,    48,    49,    50,    51,
      52,    23,   113,   114,   115,   116,   117,   118,    23,    18,
      -1,    23,   124,   125,    29,   126,   127,    29,    85,    86,
      87,    88,   134,    23,   136,   137,   138,   139,    -1,    29,
      -1,    22,    -1,    -1,   145,   146,   147,   148,   149,    30,
      22,    -1,   154,    23,   155,    -1,    -1,    -1,    30,    29,
      -1,   163,    -1,    -1,    22,    46,    47,    48,    49,    50,
      51,    52,    30,    22,    46,    47,    48,    49,    50,    51,
      52,    30,     8,     9,    10,    11,    12,    22,    46,    47,
      48,    49,    50,    51,    52,    30,    -1,    46,    47,    48,
      49,    50,    51,    52,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    47,    48,    49,    50,    51,    52,     0,    -1,
      -1,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    -1,    -1,    19,    20,    21,
      -1,    -1,    24,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,    15,    16,    -1,    -1,    19,
      20,    21,    -1,    -1,    24,    25,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
      -1,    -1,    19,    20,    21,    -1,    -1,    24,    25,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,    15,    16,    23,    -1,    19,    20,    21,    -1,    -1,
      24,    -1,    -1,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    23,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,    23,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    28,    -1,    -1,    -1,
      -1,    33,    34,    35,    36,    37,    38,    39,    40,    41,
      42,    43,    28,    -1,    -1,    -1,    -1,    33,    34,    35,
      36,    37,    38,    39,    40,    41,    42,    43,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,    16,    19,    20,    21,    24,    54,
      55,    56,    58,    59,    60,    61,    62,    63,    64,    22,
      30,    46,    47,    48,    49,    50,    51,    52,     7,    61,
       7,    61,     7,    61,     7,    61,     7,    61,    22,    64,
      22,    22,     8,     9,    10,    11,    12,    56,    28,    28,
      25,    54,     0,    55,    28,    33,    34,    35,    36,    37,
      38,    39,    40,    41,    42,    43,    56,    65,    56,    56,
      56,    56,    56,    56,    22,    22,    22,    22,    22,    56,
      56,     7,    56,    57,     7,     7,     7,     7,     7,    28,
      25,    56,    56,    56,    56,    56,    56,    56,    56,    56,
      56,    56,    23,    29,     8,     9,    10,    11,    12,    66,
      66,    66,    66,    66,    23,    23,    17,    28,    56,    56,
      56,    56,    56,    56,    23,    29,    23,    23,    23,    23,
      64,    64,    56,    57,    64,     8,     9,    10,    11,    12,
      64,    64,    64,    64,    23,    28,    56,    56,    56,    56,
      56,    64,    57,    23,    64
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    53,    54,    54,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    56,    56,    56,    56,    56,
      56,    57,    57,    58,    58,    58,    58,    58,    58,    58,
      58,    58,    58,    58,    59,    60,    60,    60,    60,    60,
      60,    60,    60,    60,    60,    61,    61,    61,    61,    61,
      61,    61,    61,    62,    62,    62,    62,    63,    63,    63,
      63,    63,    64,    64,    65,    65,    66,    66,    66,    66,
      66,    66,    66,    66,    66,    66,    66
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     5,     2,     5,     7,     9,
       3,     2,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     4,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     3,     3,     3,     3,     3,
       3,     2,     2,     1,     1,     1,     1,     6,     6,     6,
       6,     6,     3,     2,     1,     3,     0,     2,     2,     2,
       2,     2,     4,     4,     4,     4,     4
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
#line 50 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement_list) = nb_create_statement_list((yyvsp[0].statement));
        }
#line 1502 "y.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 54 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement_list) = nb_cat_statement_list((yyvsp[-1].statement_list), (yyvsp[0].statement));
        }
#line 1510 "y.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 59 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_expression_statement((yyvsp[-1].expression));
        }
#line 1518 "y.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 63 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_if_statement((yyvsp[-2].expression), (yyvsp[0].statement));
        }
#line 1526 "y.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 67 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_cat_else_statement((yyvsp[0].statement));
        }
#line 1534 "y.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 71 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_cat_elseif_statement((yyvsp[-2].expression), (yyvsp[0].statement));
        }
#line 1542 "y.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 75 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_foreach_statement((yyvsp[-4].identifier), (yyvsp[-2].expression), (yyvsp[0].statement));
        }
#line 1550 "y.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 79 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_for_statement((yyvsp[-6].expression), (yyvsp[-4].expression), (yyvsp[-2].expression), (yyvsp[0].statement));
        }
#line 1558 "y.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 83 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_return_statement((yyvsp[-1].expression));
        }
#line 1566 "y.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 87 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_continue_statement();
        }
#line 1574 "y.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 91 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_break_statement();
        }
#line 1582 "y.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 103 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_identifier_expression((yyvsp[0].identifier));
        }
#line 1590 "y.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 108 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = NULL;
        }
#line 1598 "y.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 114 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(ADD, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1606 "y.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 118 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(SUB, (yyvsp[-2].expression), (yyvsp[0].expression));            
        }
#line 1614 "y.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 122 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(MUL, (yyvsp[-2].expression), (yyvsp[0].expression));            
        }
#line 1622 "y.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 126 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(DIV, (yyvsp[-2].expression), (yyvsp[0].expression));            
        }
#line 1630 "y.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 130 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(MOD, (yyvsp[-2].expression), (yyvsp[0].expression));            
        }
#line 1638 "y.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 134 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(EQ, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1646 "y.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 138 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(NE, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1654 "y.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 142 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(GT, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1662 "y.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 146 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(GE, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1670 "y.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 150 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(LT, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1678 "y.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 154 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_binary_expression(LE, (yyvsp[-2].expression), (yyvsp[0].expression));
        }
#line 1686 "y.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 159 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_function_call_expression((yyvsp[-3].identifier), (yyvsp[-1].argument_list));
        }
#line 1694 "y.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 164 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(INT, (yyvsp[0].identifier), NULL);
        }
#line 1702 "y.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 168 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(DOUBLE, (yyvsp[0].identifier), NULL);
        }
#line 1710 "y.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 172 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(BOOL, (yyvsp[0].identifier), NULL);
        }
#line 1718 "y.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 176 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(STRING, (yyvsp[0].identifier), NULL);
        }
#line 1726 "y.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 180 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(ARRAY, (yyvsp[0].identifier), NULL);
        }
#line 1734 "y.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 184 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(INT, NULL, (yyvsp[0].expression));
        }
#line 1742 "y.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 188 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(DOUBLE, NULL, (yyvsp[0].expression));
        }
#line 1750 "y.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 192 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(BOOL, NULL, (yyvsp[0].expression));
        }
#line 1758 "y.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 196 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(STRING, NULL, (yyvsp[0].expression));
        }
#line 1766 "y.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 200 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_declaration_expression(ARRAY, NULL, (yyvsp[0].expression));
        }
#line 1774 "y.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 205 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_assignment_expression((yyvsp[-2].identifier), (yyvsp[0].expression));
        }
#line 1782 "y.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 209 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_assignment_expression((yyvsp[-2].identifier), nb_create_binary_expression(ADD, nb_create_identifier_expression((yyvsp[-2].identifier)), (yyvsp[0].expression)));
        }
#line 1790 "y.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 213 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_assignment_expression((yyvsp[-2].identifier), nb_create_binary_expression(SUB, nb_create_identifier_expression((yyvsp[-2].identifier)), (yyvsp[0].expression)));
        }
#line 1798 "y.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 217 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_assignment_expression((yyvsp[-2].identifier), nb_create_binary_expression(MUL, nb_create_identifier_expression((yyvsp[-2].identifier)), (yyvsp[0].expression)));
        }
#line 1806 "y.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 221 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_assignment_expression((yyvsp[-2].identifier), nb_create_binary_expression(DIV, nb_create_identifier_expression((yyvsp[-2].identifier)), (yyvsp[0].expression)));
        }
#line 1814 "y.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 225 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_assignment_expression((yyvsp[-2].identifier), nb_create_binary_expression(MOD, nb_create_identifier_expression((yyvsp[-2].identifier)), (yyvsp[0].expression)));
        }
#line 1822 "y.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 229 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_assignment_expression((yyvsp[-1].identifier), nb_create_binary_expression(ADD, nb_create_identifier_expression((yyvsp[-1].identifier)), nb_create_literal_expression(INT, "1")));            
        }
#line 1830 "y.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 233 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.expression) = nb_create_assignment_expression((yyvsp[-1].identifier), nb_create_binary_expression(SUB, nb_create_identifier_expression((yyvsp[-1].identifier)), nb_create_literal_expression(INT, "1")));            
        }
#line 1838 "y.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 243 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_function_definition_statement(INT, (yyvsp[-4].identifier), (yyvsp[-2].parameter_list), (yyvsp[0].statement));
        }
#line 1846 "y.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 247 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_function_definition_statement(DOUBLE, (yyvsp[-4].identifier), (yyvsp[-2].parameter_list), (yyvsp[0].statement));
        }
#line 1854 "y.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 251 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_function_definition_statement(BOOL, (yyvsp[-4].identifier), (yyvsp[-2].parameter_list), (yyvsp[0].statement));
        }
#line 1862 "y.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 255 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_function_definition_statement(STRING, (yyvsp[-4].identifier), (yyvsp[-2].parameter_list), (yyvsp[0].statement));
        }
#line 1870 "y.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 259 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_function_definition_statement(ARRAY, (yyvsp[-4].identifier), (yyvsp[-2].parameter_list), (yyvsp[0].statement));
        }
#line 1878 "y.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 264 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_block_statement((yyvsp[-1].statement_list));
        }
#line 1886 "y.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 268 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.statement) = nb_create_block_statement(NULL);
        }
#line 1894 "y.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 273 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.argument_list) = nb_create_argument_list((yyvsp[0].expression));
        }
#line 1902 "y.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 277 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.argument_list) = nb_cat_argument_list((yyvsp[-2].argument_list), (yyvsp[0].expression));
        }
#line 1910 "y.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 282 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.parameter_list) = nb_create_parameter_list(INT, NULL);
        }
#line 1918 "y.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 286 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.parameter_list) = nb_create_parameter_list(INT, (yyvsp[0].expression));
        }
#line 1926 "y.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 290 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.parameter_list) = nb_create_parameter_list(DOUBLE, (yyvsp[0].expression));
        }
#line 1934 "y.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 294 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.parameter_list) = nb_create_parameter_list(BOOL, (yyvsp[0].expression));
        }
#line 1942 "y.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 298 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.parameter_list) = nb_create_parameter_list(STRING, (yyvsp[0].expression));
        }
#line 1950 "y.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 302 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.parameter_list) = nb_create_parameter_list(ARRAY, (yyvsp[0].expression));
        }
#line 1958 "y.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 306 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.parameter_list) = nb_cat_parameter_list(INT, (yyvsp[-3].parameter_list), (yyvsp[0].expression));
        }
#line 1966 "y.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 310 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.parameter_list) = nb_cat_parameter_list(DOUBLE, (yyvsp[-3].parameter_list), (yyvsp[0].expression));
        }
#line 1974 "y.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 314 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.parameter_list) = nb_cat_parameter_list(BOOL, (yyvsp[-3].parameter_list), (yyvsp[0].expression));
        }
#line 1982 "y.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 318 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.parameter_list) = nb_cat_parameter_list(STRING, (yyvsp[-3].parameter_list), (yyvsp[0].expression));
        }
#line 1990 "y.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 322 "newbie.y" /* yacc.c:1646  */
    {
            (yyval.parameter_list) = nb_cat_parameter_list(ARRAY, (yyvsp[-3].parameter_list), (yyvsp[0].expression));
        }
#line 1998 "y.tab.c" /* yacc.c:1646  */
    break;


#line 2002 "y.tab.c" /* yacc.c:1646  */
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
#line 326 "newbie.y" /* yacc.c:1906  */
