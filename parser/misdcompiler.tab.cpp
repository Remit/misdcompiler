/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

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
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "misdcompiler.ypp" /* yacc.c:339  */

 #include <stdio.h>
 extern int yylex();
 void yyerror(const char *s) { printf("ERROR: %s\n", s); }

#line 72 "misdcompiler.tab.cpp" /* yacc.c:339  */

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
   by #include "misdcompiler.tab.hpp".  */
#ifndef YY_YY_MISDCOMPILER_TAB_HPP_INCLUDED
# define YY_YY_MISDCOMPILER_TAB_HPP_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 7 "misdcompiler.ypp" /* yacc.c:355  */

  #ifndef _BISON_MISDCOMPILER_DEFINES_0_
  #define _BISON_MISDCOMPILER_DEFINES_0_

  #define YYLEX_NEWLINE                  -1
  #define YYLEX_SINGLE_LINE_COMMENT      -2
  #define YYLEX_BLOCK_COMMENT            -3

  typedef void* yyscan_t;

  //int processNewline(yyscan_t scanner);
  //void stringBufferInit();

  #endif
#line 23 "misdcompiler.ypp" /* yacc.c:355  */

  union  YYSTYPE {
    const char*       pch;
  };

  struct YYLTYPE {
    int         first_line;
    int         first_column;
    int         last_line;
    int         last_column;
    const char* comment;
  };

#line 131 "misdcompiler.tab.cpp" /* yacc.c:355  */

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TIDENT = 258,
    NUMLITERAL = 259,
    TSTRUCTIDENT = 260,
    STRINGLITERAL = 261,
    TINT = 262,
    TCHAR = 263,
    TLONG = 264,
    TFLOAT = 265,
    TIF = 266,
    TTHEN = 267,
    TELSE = 268,
    TWHILE = 269,
    TDO = 270,
    TFOR = 271,
    TMEMTYPESPU = 272,
    TMEMTYPECPU = 273,
    TMISDOPSEARCHSTR = 274,
    TMISDOPSEARCHSMLSTR = 275,
    TMISDOPSEARCHGRTSTR = 276,
    TMISDOPINSERTSTR = 277,
    TMISDOPDELETEFROMSTR = 278,
    TMISDOPNEXTSTR = 279,
    TMISDOPDELETESTR = 280,
    TMISDOPMAXSTR = 281,
    TMISDOPMINSTR = 282,
    TMISDOPPOWERSTR = 283,
    TMISDOPUNIONSTR = 284,
    TMISDOPINTERSECTSTR = 285,
    TMISDOPNOTSTR = 286,
    TMISDOPGTSTR = 287,
    TMISDOPLTSTR = 288,
    TMISDOPLTESTR = 289,
    TMISDOPGTESTR = 290,
    TMISDOPSENDTOSPU = 291,
    TMISDOPSENDTOCPU = 292,
    TMISDOPRECEIVEFROMSPU = 293,
    TMISDOPRECEIVEFROMCPU = 294,
    TPLUS = 295,
    TMINUS = 296,
    TDIV = 297,
    TMUL = 298,
    TMOD = 299,
    TAND = 300,
    TOR = 301,
    TNOT = 302,
    TLT = 303,
    TGT = 304,
    TLTE = 305,
    TGTE = 306,
    TEQ = 307,
    TCOMMA = 308,
    TSEMI = 309,
    TASSIGN = 310,
    TLCBR = 311,
    TRCBR = 312,
    TLP = 313,
    TRP = 314,
    TNOELSE = 315
  };
#endif

/* Value type.  */


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_MISDCOMPILER_TAB_HPP_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 210 "misdcompiler.tab.cpp" /* yacc.c:358  */

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
#define YYFINAL  56
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   255

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  68
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  176

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   315

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
      55,    56,    57,    58,    59,    60
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    81,    81,    85,    86,    90,    91,    92,    93,    94,
      98,    99,   103,   104,   105,   106,   107,   108,   112,   116,
     117,   118,   119,   123,   124,   128,   129,   133,   137,   138,
     139,   143,   144,   145,   146,   150,   151,   152,   153,   157,
     161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   177,   181,   182,   186,
     190,   191,   192,   193,   194,   198,   199,   203,   207
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TIDENT", "NUMLITERAL", "TSTRUCTIDENT",
  "STRINGLITERAL", "TINT", "TCHAR", "TLONG", "TFLOAT", "TIF", "TTHEN",
  "TELSE", "TWHILE", "TDO", "TFOR", "TMEMTYPESPU", "TMEMTYPECPU",
  "TMISDOPSEARCHSTR", "TMISDOPSEARCHSMLSTR", "TMISDOPSEARCHGRTSTR",
  "TMISDOPINSERTSTR", "TMISDOPDELETEFROMSTR", "TMISDOPNEXTSTR",
  "TMISDOPDELETESTR", "TMISDOPMAXSTR", "TMISDOPMINSTR", "TMISDOPPOWERSTR",
  "TMISDOPUNIONSTR", "TMISDOPINTERSECTSTR", "TMISDOPNOTSTR",
  "TMISDOPGTSTR", "TMISDOPLTSTR", "TMISDOPLTESTR", "TMISDOPGTESTR",
  "TMISDOPSENDTOSPU", "TMISDOPSENDTOCPU", "TMISDOPRECEIVEFROMSPU",
  "TMISDOPRECEIVEFROMCPU", "TPLUS", "TMINUS", "TDIV", "TMUL", "TMOD",
  "TAND", "TOR", "TNOT", "TLT", "TGT", "TLTE", "TGTE", "TEQ", "TCOMMA",
  "TSEMI", "TASSIGN", "TLCBR", "TRCBR", "TLP", "TRP", "TNOELSE", "$accept",
  "program", "stmts_ls", "stmt", "stmts_block", "expr_stmt", "def_expr",
  "id_type", "id_ls", "mem_type", "str_delete", "str_bin_expr",
  "str_compare_expr", "str_transmission_expr", "assign_stmt", "expr",
  "if_stmt", "bool_expr", "log_op", "loop_stmt", "count_loop",
  "while_loop", YY_NULLPTR
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
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315
};
# endif

#define YYPACT_NINF -53

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-53)))

#define YYTABLE_NINF -13

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     199,   -52,   -53,   -53,   -53,   -53,   -51,   -27,   -16,    40,
      41,    42,    43,    45,    46,    47,    61,    64,    72,    73,
      75,    74,    86,   162,   -53,   -53,    33,    35,    23,    44,
      48,    60,    62,    63,   -53,   -53,   -53,   -53,     2,     2,
       2,    93,   -53,    68,    69,    70,    71,    76,    84,    85,
     -53,   -53,   -53,   -53,   -53,   125,   -53,   -53,   -53,   -53,
     -53,   -53,    87,    94,   -53,   -53,   -53,   -53,   -53,   -53,
     -53,    95,    96,   110,   120,   121,   122,     2,     2,    -7,
      13,    83,    88,    89,   139,   140,   143,   144,   147,   148,
     161,   -53,    23,   -53,   114,   115,   124,   126,   127,   130,
     -53,   -32,     2,     2,     2,     2,     2,     2,     2,   -53,
     -53,   -53,   -53,   -53,     2,   163,   159,     2,   131,   132,
     133,   135,   136,   137,   150,   201,   202,   208,   209,   211,
     214,   216,   -53,   -14,   -14,   -53,   -53,   -53,    51,   -25,
      -7,   199,   199,   166,   217,   218,   220,   223,   224,   236,
     237,   -53,   -53,   -53,   -53,   168,   -53,   -53,   228,   -53,
      93,   -53,   -53,   -53,   -53,   -53,   -53,   -53,   239,   199,
     189,   -53,   -53,   185,   199,   -53
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      12,     0,    19,    20,    21,    22,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    12,     0,     2,     3,     5,     0,     0,     0,     0,
       0,     0,     0,     0,     8,     9,    65,    66,     0,     0,
       0,     0,    27,     0,     0,     0,     0,     0,     0,     0,
      35,    36,    37,    38,    11,    12,     1,     4,     6,    13,
      25,    26,    18,     0,    14,    15,    16,    17,     7,    55,
      56,     0,     0,     0,     0,     0,     0,     0,     0,    39,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    10,     0,    23,     0,     0,     0,     0,     0,     0,
      48,     0,     0,     0,     0,     0,     0,     0,     0,    60,
      61,    62,    63,    64,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    40,    41,    42,    44,    43,    45,    46,    47,
      59,    12,    12,     0,     0,     0,     0,     0,     0,     0,
       0,    24,    49,    50,    51,     0,    53,    54,    57,    68,
       0,    28,    29,    30,    31,    32,    33,    34,     0,    12,
       0,    52,    58,     0,    12,    67
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -53,   -53,   225,   -23,   -53,   -53,   -53,   -53,   -53,   153,
     -53,   -53,   -53,   -53,   -40,   -34,   -53,   -38,   -53,   -53,
     -53,   -53
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,    22,    23,    24,    25,    26,    27,    28,    62,    63,
      29,    30,    31,    32,    33,    80,    34,    81,   114,    35,
      36,    37
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      57,    83,    82,    38,    79,    69,    70,    39,   102,   103,
     104,   105,   106,   107,   108,   102,   103,   104,   105,   106,
     107,    71,    72,    73,    74,    75,    76,   132,   104,   105,
     106,    40,    57,   102,   103,   104,   105,   106,   107,   108,
      60,    61,    41,   100,   101,    42,    43,    44,    45,    77,
      46,    47,    48,   102,   103,   104,   105,   106,   107,   108,
      78,   109,   110,   111,   112,   113,    49,    50,   133,   134,
     135,   136,   137,   138,   139,    51,    52,     1,    53,   143,
     140,     2,     3,     4,     5,     6,    56,    58,     7,    59,
       8,   102,   103,   104,   105,   106,     1,    93,    64,     9,
      94,    95,    65,    10,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    66,    96,    67,    68,   158,   159,
     170,    84,    85,    86,    87,    97,    98,    99,     1,    88,
      21,    54,     2,     3,     4,     5,     6,    89,    90,     7,
      92,     8,   115,   117,   118,   119,   172,   116,   120,   121,
       9,   175,   122,   123,    10,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,     1,   124,   126,   127,     2,
       3,     4,     5,     6,   142,   141,     7,   128,     8,   129,
     130,    21,    91,   131,   144,   145,   146,     9,   147,   148,
     149,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,     1,   150,   151,   152,     2,     3,     4,     5,
       6,   153,   154,     7,   155,     8,   -12,   156,    21,   157,
     160,   168,   161,   162,     9,   163,   164,   165,    10,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,   166,
     167,   169,   171,   173,   174,   125,    55,     0,     0,     0,
       0,     0,     0,     0,     0,    21
};

static const yytype_int16 yycheck[] =
{
      23,    41,    40,    55,    38,     3,     4,    58,    40,    41,
      42,    43,    44,    45,    46,    40,    41,    42,    43,    44,
      45,    19,    20,    21,    22,    23,    24,    59,    42,    43,
      44,    58,    55,    40,    41,    42,    43,    44,    45,    46,
      17,    18,    58,    77,    78,     5,     5,     5,     5,    47,
       5,     5,     5,    40,    41,    42,    43,    44,    45,    46,
      58,    48,    49,    50,    51,    52,     5,     3,   102,   103,
     104,   105,   106,   107,   108,     3,     3,     3,     3,   117,
     114,     7,     8,     9,    10,    11,     0,    54,    14,    54,
      16,    40,    41,    42,    43,    44,     3,     3,    54,    25,
       5,     5,    54,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    54,     5,    54,    54,   141,   142,
     160,    53,    53,    53,    53,     5,     5,     5,     3,    53,
      56,    57,     7,     8,     9,    10,    11,    53,    53,    14,
      53,    16,    59,    54,     5,     5,   169,    59,     5,     5,
      25,   174,     5,     5,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,     3,     5,    53,    53,     7,
       8,     9,    10,    11,    15,    12,    14,    53,    16,    53,
      53,    56,    57,    53,    53,    53,    53,    25,    53,    53,
      53,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,     3,    53,     3,     3,     7,     8,     9,    10,
      11,     3,     3,    14,     3,    16,    54,     3,    56,     3,
      54,    53,     5,     5,    25,     5,     3,     3,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,     3,
       3,    13,     3,    54,    59,    92,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    56
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     7,     8,     9,    10,    11,    14,    16,    25,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    56,    62,    63,    64,    65,    66,    67,    68,    71,
      72,    73,    74,    75,    77,    80,    81,    82,    55,    58,
      58,    58,     5,     5,     5,     5,     5,     5,     5,     5,
       3,     3,     3,     3,    57,    63,     0,    64,    54,    54,
      17,    18,    69,    70,    54,    54,    54,    54,    54,     3,
       4,    19,    20,    21,    22,    23,    24,    47,    58,    76,
      76,    78,    78,    75,    53,    53,    53,    53,    53,    53,
      53,    57,    53,     3,     5,     5,     5,     5,     5,     5,
      76,    76,    40,    41,    42,    43,    44,    45,    46,    48,
      49,    50,    51,    52,    79,    59,    59,    54,     5,     5,
       5,     5,     5,     5,     5,    70,    53,    53,    53,    53,
      53,    53,    59,    76,    76,    76,    76,    76,    76,    76,
      76,    12,    15,    78,    53,    53,    53,    53,    53,    53,
      53,     3,     3,     3,     3,     3,     3,     3,    64,    64,
      54,     5,     5,     5,     3,     3,     3,     3,    53,    13,
      75,     3,    64,    54,    59,    64
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    61,    62,    63,    63,    64,    64,    64,    64,    64,
      65,    65,    66,    66,    66,    66,    66,    66,    67,    68,
      68,    68,    68,    69,    69,    70,    70,    71,    72,    72,
      72,    73,    73,    73,    73,    74,    74,    74,    74,    75,
      76,    76,    76,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    76,    76,    76,    76,    76,    77,    77,    78,
      79,    79,    79,    79,    79,    80,    80,    81,    82
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     1,     2,     1,     2,     2,     1,     1,
       3,     2,     0,     2,     2,     2,     2,     2,     2,     1,
       1,     1,     1,     2,     4,     1,     1,     2,     6,     6,
       6,     6,     6,     6,     6,     2,     2,     2,     2,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     4,
       4,     4,     6,     4,     4,     1,     1,     6,     8,     3,
       1,     1,     1,     1,     1,     1,     1,    10,     6
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
#line 81 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Syntactical analysis completed successfully\n"); }
#line 1425 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 85 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Statement\n"); }
#line 1431 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 86 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Statements list\n"); }
#line 1437 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 90 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Statements block\n"); }
#line 1443 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 91 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Expression statement\n"); }
#line 1449 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 92 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Assignment statement\n"); }
#line 1455 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 93 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("If statement\n"); }
#line 1461 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 94 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Loop statement\n"); }
#line 1467 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 98 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Non-empty statements block\n"); }
#line 1473 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 99 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Empty statements block\n"); }
#line 1479 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 103 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("NOP\n"); }
#line 1485 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 104 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Definition expression\n"); }
#line 1491 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 105 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Delete structure\n"); }
#line 1497 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 106 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Binary expression\n"); }
#line 1503 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 107 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Compare expression\n"); }
#line 1509 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 108 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Transmission expression\n"); }
#line 1515 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 112 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Type definition\n"); }
#line 1521 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 116 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Integer type\n"); }
#line 1527 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 117 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Char type\n"); }
#line 1533 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 118 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Long type\n"); }
#line 1539 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 119 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Float type\n"); }
#line 1545 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 123 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Memory typization\n"); }
#line 1551 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 124 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Identifiers list\n"); }
#line 1557 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 128 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("SPU memory type\n"); }
#line 1563 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 129 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("CPU memory type\n"); }
#line 1569 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 133 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Deletion of structure\n"); }
#line 1575 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 137 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Structure union\n"); }
#line 1581 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 138 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Structure intersection\n"); }
#line 1587 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 139 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Structure substraction\n"); }
#line 1593 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 143 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Dissect structure by >\n"); }
#line 1599 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 144 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Dissect structure by <\n"); }
#line 1605 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 145 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Dissect structure by <=\n"); }
#line 1611 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 146 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Dissect structure by >=\n"); }
#line 1617 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 150 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Send identifier to SPU\n"); }
#line 1623 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 151 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Send identifier to CPU\n"); }
#line 1629 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 152 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Receive identifier from SPU\n"); }
#line 1635 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 153 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Receive identifier from CPU\n"); }
#line 1641 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 157 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Assignment\n"); }
#line 1647 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 161 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Parenthesized expression\n"); }
#line 1653 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 162 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Sum\n"); }
#line 1659 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 163 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Substraction\n"); }
#line 1665 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 164 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Multiplication\n"); }
#line 1671 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 165 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Division\n"); }
#line 1677 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 166 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Division (remaining num)\n"); }
#line 1683 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 167 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Logical AND\n"); }
#line 1689 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 168 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Logical OR\n"); }
#line 1695 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 169 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Logical NOT\n"); }
#line 1701 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 170 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Structure search\n"); }
#line 1707 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 171 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Structure search smaller than...\n"); }
#line 1713 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 172 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Structure search greater than...\n"); }
#line 1719 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 173 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Insert into structure\n"); }
#line 1725 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 174 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Delete from structure\n"); }
#line 1731 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 175 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Get the next element in structure\n"); }
#line 1737 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 176 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Identifier\n"); }
#line 1743 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 177 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Number or literal\n"); }
#line 1749 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 181 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Pure if-statement\n"); }
#line 1755 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 182 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("If-then-else statement\n"); }
#line 1761 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 186 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Boolean expression\n"); }
#line 1767 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 190 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Less than\n"); }
#line 1773 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 191 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Greater than\n"); }
#line 1779 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 62:
#line 192 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Less than or equal to\n"); }
#line 1785 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 63:
#line 193 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Greater than or equal to\n"); }
#line 1791 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 64:
#line 194 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Equal\n"); }
#line 1797 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 65:
#line 198 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("Count loop\n"); }
#line 1803 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 66:
#line 199 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("While loop\n"); }
#line 1809 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 67:
#line 203 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("For-loop with counter\n"); }
#line 1815 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;

  case 68:
#line 207 "misdcompiler.ypp" /* yacc.c:1646  */
    { printf("While-do loop\n"); }
#line 1821 "misdcompiler.tab.cpp" /* yacc.c:1646  */
    break;


#line 1825 "misdcompiler.tab.cpp" /* yacc.c:1646  */
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
#line 210 "misdcompiler.ypp" /* yacc.c:1906  */

