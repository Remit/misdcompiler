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
#define YYPURE 1

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 15 "misdcompiler.ypp" /* yacc.c:339  */

 #define YYPARSE_PARAM scanner
 #define YYLEX_PARAM   scanner

#line 71 "bison-misdcompiler.cpp" /* yacc.c:339  */

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
   by #include "bison-misdcompiler.h".  */
#ifndef YY_YY_INCLUDE_BISON_MISDCOMPILER_H_INCLUDED
# define YY_YY_INCLUDE_BISON_MISDCOMPILER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 1 "misdcompiler.ypp" /* yacc.c:355  */

    
 struct YYLTYPE {
    int         first_line;
    int         first_column;
    int         last_line;
    int         last_column;
    const char* comment;
  };

  #define YYLTYPE_IS_DECLARED 1
  #define YYLTYPE_IS_TRIVIAL  1
#line 20 "misdcompiler.ypp" /* yacc.c:355  */

 #include <stdio.h>
 #include <string>
 #include <vector>
 #include "../include/build.h"
 #include "../include/IRGraph.h"
 
 static
 void yyerror(char *s)
 {
        printf("yyerror: %s\n", s);
 }
 

#line 129 "bison-misdcompiler.cpp" /* yacc.c:355  */

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
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 49 "misdcompiler.ypp" /* yacc.c:355  */
	
 const char* pch;
 
 IR_Graph* graph;
 proc_type ptype;
 int type_int;
 std::string* str;

#line 211 "bison-misdcompiler.cpp" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (void);

#endif /* !YY_YY_INCLUDE_BISON_MISDCOMPILER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 239 "bison-misdcompiler.cpp" /* yacc.c:358  */
/* Unqualified %code blocks.  */
#line 35 "misdcompiler.ypp" /* yacc.c:359  */

 std::vector< std::string > idents; 
 std::vector< std::string > exp_vars_list;
 std::vector< std::string > exp_nums_list;
 extern int yylex( YYSTYPE* yylval_param, YYLTYPE* yylloc_param);

#line 248 "bison-misdcompiler.cpp" /* yacc.c:359  */

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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE) + sizeof (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   196

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  61
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  70
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  140

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
       0,   107,   107,   111,   112,   116,   117,   118,   119,   120,
     124,   125,   129,   130,   131,   132,   133,   134,   135,   139,
     143,   144,   145,   146,   150,   151,   155,   156,   160,   164,
     168,   169,   170,   174,   178,   179,   180,   181,   185,   189,
     193,   194,   198,   199,   200,   201,   205,   209,   213,   214,
     215,   216,   217,   218,   219,   220,   221,   222,   223,   227,
     228,   232,   236,   237,   238,   239,   240,   244,   245,   249,
     253
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
  "str_bin_op", "str_compare_expr", "str_comp_op", "str_insert_to_str",
  "str_delete_from_str", "assign_stmt", "struct_op_acq_elem", "struct",
  "ident", "expr", "if_stmt", "bool_expr", "log_op", "loop_stmt",
  "count_loop", "while_loop", YY_NULLPTR
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

#define YYPACT_NINF -77

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-77)))

#define YYTABLE_NINF -13

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -77,    16,   105,   -77,   -77,   -77,   -77,   -77,   -77,   -35,
     -16,   -12,    13,    13,    13,   -77,   -77,   -77,   -77,   -77,
     -77,   -77,   -33,   -77,   -77,     6,     9,    -5,    14,    15,
      13,    18,    13,    19,    25,    26,    -6,   -77,   -77,   -77,
     -77,     3,     3,    64,   -77,    31,    34,   -77,   -77,    67,
     -77,   -77,   -77,   -77,    38,    90,   -77,   -77,    41,   -77,
      42,   -77,   -77,   -77,     1,   -77,   -77,     3,     3,   136,
      50,    51,    66,    64,    64,   -77,    -5,   -77,    13,    13,
     -77,   -77,   -77,   -77,    13,    11,   -77,   -14,     3,     3,
       3,     3,     3,     3,     3,   -77,   -77,   -77,   -77,   -77,
       3,   106,   102,     3,    69,   -77,   122,    73,    76,    78,
     -77,   -34,   -34,   -77,   -77,   -77,    63,   149,    11,   140,
     140,    79,    64,   -77,    13,    64,    64,   119,   -77,    64,
     -77,   -77,   -77,   -77,   140,    87,   -77,    83,   140,   -77
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       3,     0,     2,     1,    47,    20,    21,    22,    23,     0,
       0,     0,     0,     0,     0,    30,    31,    32,    34,    35,
      36,    37,     3,     4,     5,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     8,     9,    67,
      68,     0,     0,     0,    46,     0,     0,    28,    11,    12,
       6,    13,    26,    27,    19,     0,    14,    15,     0,    16,
       0,    17,    18,     7,     0,    57,    58,     0,     0,     0,
       0,     0,     0,     0,     0,    10,     0,    24,     0,     0,
      42,    43,    44,    45,     0,    40,    56,     0,     0,     0,
       0,     0,     0,     0,     0,    62,    63,    64,    65,    66,
       0,     0,     0,     0,     0,    39,     0,     0,     0,     0,
      48,    49,    50,    52,    51,    53,    54,    55,    61,    12,
      12,     0,     0,    25,     0,     0,     0,    59,    70,     0,
      38,    29,    33,    41,    12,     0,    60,     0,    12,    69
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -77,   -77,   123,   -76,   -77,   -77,   -77,   -77,   -77,    68,
     -77,   -77,   -77,   -77,   -77,   -77,   -77,   -41,   -77,   -13,
     -40,   -53,   -77,   -39,   -77,   -77,   -77,   -77
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    23,    24,    25,    26,    27,    54,    55,
      28,    29,    30,    31,    32,    33,    34,    35,    84,    45,
      36,    69,    37,    70,   100,    38,    39,    40
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      46,    47,    72,    71,    65,    66,    65,    66,    90,    91,
      92,    85,    52,    53,    86,    87,     3,    58,    44,    60,
      80,    81,    82,    41,    48,    83,    88,    89,    90,    91,
      92,    93,    94,   104,   105,   111,   112,   113,   114,   115,
     116,   117,    42,   127,   128,   110,    43,   118,    67,    64,
      67,    88,    89,    90,    91,    92,    93,    94,   136,    68,
      50,    68,   139,    51,   121,   107,   108,     4,    56,    57,
       4,   109,    59,    61,     5,     6,     7,     8,     9,    62,
      63,    10,   130,    11,    73,   132,   133,    74,   135,    12,
      13,    76,    14,    77,    78,    79,    15,    16,    17,    18,
      19,    20,    21,    88,    89,    90,    91,    92,     4,   101,
     102,   131,     5,     6,     7,     8,     9,   120,   119,    10,
     103,    11,   122,    22,    75,   123,   124,    12,    13,   125,
      14,   126,   134,   129,    15,    16,    17,    18,    19,    20,
      21,   137,   138,     4,   106,    49,     0,     5,     6,     7,
       8,     9,     0,     0,    10,     0,    11,     0,     0,   -12,
       0,    22,    12,    13,     0,    14,     0,     0,     0,    15,
      16,    17,    18,    19,    20,    21,    88,    89,    90,    91,
      92,    93,    94,     0,    95,    96,    97,    98,    99,    88,
      89,    90,    91,    92,    93,     0,    22
};

static const yytype_int16 yycheck[] =
{
      13,    14,    43,    42,     3,     4,     3,     4,    42,    43,
      44,    64,    17,    18,    67,    68,     0,    30,     5,    32,
      19,    20,    21,    58,    57,    24,    40,    41,    42,    43,
      44,    45,    46,    73,    74,    88,    89,    90,    91,    92,
      93,    94,    58,   119,   120,    59,    58,   100,    47,    55,
      47,    40,    41,    42,    43,    44,    45,    46,   134,    58,
      54,    58,   138,    54,   103,    78,    79,     3,    54,    54,
       3,    84,    54,    54,     7,     8,     9,    10,    11,    54,
      54,    14,   122,    16,    53,   125,   126,    53,   129,    22,
      23,    53,    25,     3,    53,    53,    29,    30,    31,    32,
      33,    34,    35,    40,    41,    42,    43,    44,     3,    59,
      59,   124,     7,     8,     9,    10,    11,    15,    12,    14,
      54,    16,    53,    56,    57,     3,    53,    22,    23,    53,
      25,    53,    13,    54,    29,    30,    31,    32,    33,    34,
      35,    54,    59,     3,    76,    22,    -1,     7,     8,     9,
      10,    11,    -1,    -1,    14,    -1,    16,    -1,    -1,    54,
      -1,    56,    22,    23,    -1,    25,    -1,    -1,    -1,    29,
      30,    31,    32,    33,    34,    35,    40,    41,    42,    43,
      44,    45,    46,    -1,    48,    49,    50,    51,    52,    40,
      41,    42,    43,    44,    45,    -1,    56
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    62,    63,     0,     3,     7,     8,     9,    10,    11,
      14,    16,    22,    23,    25,    29,    30,    31,    32,    33,
      34,    35,    56,    64,    65,    66,    67,    68,    71,    72,
      73,    74,    75,    76,    77,    78,    81,    83,    86,    87,
      88,    58,    58,    58,     5,    80,    80,    80,    57,    63,
      54,    54,    17,    18,    69,    70,    54,    54,    80,    54,
      80,    54,    54,    54,    55,     3,     4,    47,    58,    82,
      84,    84,    78,    53,    53,    57,    53,     3,    53,    53,
      19,    20,    21,    24,    79,    82,    82,    82,    40,    41,
      42,    43,    44,    45,    46,    48,    49,    50,    51,    52,
      85,    59,    59,    54,    81,    81,    70,    80,    80,    80,
      59,    82,    82,    82,    82,    82,    82,    82,    82,    12,
      15,    84,    53,     3,    53,    53,    53,    64,    64,    54,
      81,    80,    81,    81,    13,    78,    64,    54,    59,    64
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    61,    62,    63,    63,    64,    64,    64,    64,    64,
      65,    65,    66,    66,    66,    66,    66,    66,    66,    67,
      68,    68,    68,    68,    69,    69,    70,    70,    71,    72,
      73,    73,    73,    74,    75,    75,    75,    75,    76,    77,
      78,    78,    79,    79,    79,    79,    80,    81,    82,    82,
      82,    82,    82,    82,    82,    82,    82,    82,    82,    83,
      83,    84,    85,    85,    85,    85,    85,    86,    86,    87,
      88
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     0,     2,     1,     2,     2,     1,     1,
       3,     2,     0,     2,     2,     2,     2,     2,     2,     2,
       1,     1,     1,     1,     2,     4,     1,     1,     2,     6,
       1,     1,     1,     6,     1,     1,     1,     1,     6,     4,
       3,     6,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     3,     3,     2,     1,     1,     6,
       8,     3,     1,     1,     1,     1,     1,     1,     1,    10,
       6
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


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static unsigned
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  unsigned res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  YYUSE (yylocationp);
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
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyoutput, *yylocationp);
  YYFPRINTF (yyoutput, ": ");
  yy_symbol_value_print (yyoutput, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
/* The lookahead symbol.  */
int yychar;


/* The semantic value of the lookahead symbol.  */
/* Default value used for initialization, for pacifying older GCCs
   or non-GCC compilers.  */
YY_INITIAL_VALUE (static YYSTYPE yyval_default;)
YYSTYPE yylval YY_INITIAL_VALUE (= yyval_default);

/* Location data for the lookahead symbol.  */
static YYLTYPE yyloc_default
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
YYLTYPE yylloc = yyloc_default;

    /* Number of syntax errors so far.  */
    int yynerrs;

    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

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

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yyls1, yysize * sizeof (*yylsp),
                    &yystacksize);

        yyls = yyls1;
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
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
      yychar = yylex (&yylval, &yylloc);
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
  *++yylsp = yylloc;
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

  /* Default location.  */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 3:
#line 111 "misdcompiler.ypp" /* yacc.c:1646  */
    { (yyval.graph) = new IR_Graph(); (yyval.graph)->addOperationNode( buildTerminalNode( ) ); }
#line 1544 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 112 "misdcompiler.ypp" /* yacc.c:1646  */
    { (yyvsp[-1].graph)->appendGraph((yyvsp[0].graph)); (yyval.graph) = (yyvsp[-1].graph); }
#line 1550 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 117 "misdcompiler.ypp" /* yacc.c:1646  */
    { (yyval.graph) = (yyvsp[-1].graph); }
#line 1556 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 118 "misdcompiler.ypp" /* yacc.c:1646  */
    { (yyval.graph) = (yyvsp[-1].graph); }
#line 1562 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 124 "misdcompiler.ypp" /* yacc.c:1646  */
    { (yyval.graph) = (yyvsp[-1].graph); }
#line 1568 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 125 "misdcompiler.ypp" /* yacc.c:1646  */
    { (yyval.graph) = NULL; }
#line 1574 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 129 "misdcompiler.ypp" /* yacc.c:1646  */
    { (yyval.graph) = NULL; }
#line 1580 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 130 "misdcompiler.ypp" /* yacc.c:1646  */
    { (yyval.graph) = (yyvsp[-1].graph); }
#line 1586 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 131 "misdcompiler.ypp" /* yacc.c:1646  */
    { (yyval.graph) = (yyvsp[-1].graph); }
#line 1592 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 132 "misdcompiler.ypp" /* yacc.c:1646  */
    { (yyval.graph) = (yyvsp[-1].graph); }
#line 1598 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 133 "misdcompiler.ypp" /* yacc.c:1646  */
    { (yyval.graph) = (yyvsp[-1].graph); }
#line 1604 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 134 "misdcompiler.ypp" /* yacc.c:1646  */
    { (yyval.graph) = (yyvsp[-1].graph); }
#line 1610 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 135 "misdcompiler.ypp" /* yacc.c:1646  */
    { (yyval.graph) = (yyvsp[-1].graph); }
#line 1616 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 139 "misdcompiler.ypp" /* yacc.c:1646  */
    { std::vector<int>::size_type sz = idents.size(); for(unsigned i = 0; i < sz; i++) { updateDataNode_SimpleDataType(idents[i],(yyvsp[-1].type_int)); } (yyval.graph) = NULL; idents.clear(); }
#line 1622 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 150 "misdcompiler.ypp" /* yacc.c:1646  */
    { std::string ident_name(yylval.pch, 0, 1024); buildDataNode(ident_name,(yyvsp[-1].ptype),IR_DATA_SIMPLE); idents.reserve(1024); idents.push_back(ident_name); (yyval.graph) = NULL; }
#line 1628 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 151 "misdcompiler.ypp" /* yacc.c:1646  */
    { std::string ident_name(yylval.pch, 0, 1024); buildDataNode(ident_name,(yyvsp[-1].ptype),IR_DATA_SIMPLE); idents.push_back(ident_name); (yyval.graph) = NULL; }
#line 1634 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 155 "misdcompiler.ypp" /* yacc.c:1646  */
    { (yyval.ptype) = IR_SPU; }
#line 1640 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 156 "misdcompiler.ypp" /* yacc.c:1646  */
    { (yyval.ptype) = IR_CPU; }
#line 1646 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 160 "misdcompiler.ypp" /* yacc.c:1646  */
    { addStructDataNodeToGraph(* (yyvsp[0].str)); IR_OperationNode* op_node = buildAssignNode(IR_DATA_STRUCTURE); (yyval.graph) = new IR_Graph(); (yyval.graph)->addOperationNode(op_node); IR_DataNode* data_node = getStructureNodeByName(* (yyvsp[0].str)); (yyval.graph)->addDataNode(data_node); int op_node_id = (yyval.graph)->getLastOperationID(); int data_node_id = (yyval.graph)->getLastDataID(); if((data_node_id > 0) && (op_node_id > 0)) { (yyval.graph)->addConnection(op_node_id,data_node_id); } }
#line 1652 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 164 "misdcompiler.ypp" /* yacc.c:1646  */
    { addStructDataNodeToGraph(* (yyvsp[-4].str)); addStructDataNodeToGraph(* (yyvsp[-2].str)); addStructDataNodeToGraph(* (yyvsp[0].str)); IR_OperationNode* op_node = buildAssignNode(IR_DATA_STRUCTURE); (yyval.graph) = new IR_Graph(); (yyval.graph)->addOperationNode(op_node); IR_DataNode* data_node_result = getStructureNodeByName(* (yyvsp[-4].str)); IR_DataNode* data_node_1 = getStructureNodeByName(* (yyvsp[-2].str)); IR_DataNode* data_node_2 = getStructureNodeByName(* (yyvsp[0].str)); (yyval.graph)->addDataNode(data_node_result); int data_node_result_id = (yyval.graph)->getLastDataID(); (yyval.graph)->addDataNode(data_node_1); int data_node_1_id = (yyval.graph)->getLastDataID(); (yyval.graph)->addDataNode(data_node_2); int data_node_2_id = (yyval.graph)->getLastDataID(); int op_node_id = (yyval.graph)->getLastOperationID(); if((data_node_result_id > 0) && (op_node_id > 0) && (data_node_1_id > 0) && (data_node_2_id > 0)) { (yyval.graph)->addConnection(op_node_id,data_node_result_id); (yyval.graph)->addConnection(data_node_1_id,op_node_id); (yyval.graph)->addConnection(data_node_2_id,op_node_id); } }
#line 1658 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 174 "misdcompiler.ypp" /* yacc.c:1646  */
    { addStructDataNodeToGraph(* (yyvsp[-4].str)); addStructDataNodeToGraph(* (yyvsp[-2].str)); IR_OperationNode* op_node = buildAssignNode(IR_DATA_STRUCTURE); (yyval.graph) = new IR_Graph(); (yyval.graph)->addOperationNode(op_node); IR_DataNode* data_node_result = getStructureNodeByName(* (yyvsp[-4].str)); IR_DataNode* data_node_1 = getStructureNodeByName(* (yyvsp[-2].str)); IR_DataNode* data_node_2 = getVariableNodeByName(* (yyvsp[0].str)); (yyval.graph)->addDataNode(data_node_result); int data_node_result_id = (yyval.graph)->getLastDataID(); (yyval.graph)->addDataNode(data_node_1); int data_node_1_id = (yyval.graph)->getLastDataID(); (yyval.graph)->addDataNode(data_node_2); int data_node_2_id = (yyval.graph)->getLastDataID(); int op_node_id = (yyval.graph)->getLastOperationID(); if((data_node_result_id > 0) && (op_node_id > 0) && (data_node_1_id > 0) && (data_node_2_id > 0)) { (yyval.graph)->addConnection(op_node_id,data_node_result_id); (yyval.graph)->addConnection(data_node_1_id,op_node_id); (yyval.graph)->addConnection(data_node_2_id,op_node_id); } }
#line 1664 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 185 "misdcompiler.ypp" /* yacc.c:1646  */
    { addStructDataNodeToGraph(* (yyvsp[-4].str)); IR_OperationNode* op_node = buildAssignNode(IR_DATA_STRUCTURE); (yyval.graph) = new IR_Graph(); (yyval.graph)->addOperationNode(op_node); IR_DataNode* data_node_result = getStructureNodeByName(* (yyvsp[-4].str)); IR_DataNode* data_node_1 = getVariableNodeByName(* (yyvsp[-2].str)); IR_DataNode* data_node_2 = getVariableNodeByName(* (yyvsp[0].str)); (yyval.graph)->addDataNode(data_node_result); int data_node_result_id = (yyval.graph)->getLastDataID(); (yyval.graph)->addDataNode(data_node_1); int data_node_1_id = (yyval.graph)->getLastDataID(); (yyval.graph)->addDataNode(data_node_2); int data_node_2_id = (yyval.graph)->getLastDataID(); int op_node_id = (yyval.graph)->getLastOperationID(); if((data_node_result_id > 0) && (op_node_id > 0) && (data_node_1_id > 0) && (data_node_2_id > 0)) { (yyval.graph)->addConnection(op_node_id,data_node_result_id); (yyval.graph)->addConnection(data_node_1_id,op_node_id); (yyval.graph)->addConnection(data_node_2_id,op_node_id); } }
#line 1670 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 189 "misdcompiler.ypp" /* yacc.c:1646  */
    { addStructDataNodeToGraph(* (yyvsp[-2].str)); IR_OperationNode* op_node = buildAssignNode(IR_DATA_STRUCTURE); (yyval.graph) = new IR_Graph(); (yyval.graph)->addOperationNode(op_node); IR_DataNode* data_node_result = getStructureNodeByName(* (yyvsp[-2].str)); IR_DataNode* data_node_1 = getVariableNodeByName(* (yyvsp[0].str)); (yyval.graph)->addDataNode(data_node_result); int data_node_result_id = (yyval.graph)->getLastDataID(); (yyval.graph)->addDataNode(data_node_1); int data_node_1_id = (yyval.graph)->getLastDataID(); int op_node_id = (yyval.graph)->getLastOperationID(); if((data_node_result_id > 0) && (op_node_id > 0) && (data_node_1_id > 0)) { (yyval.graph)->addConnection(op_node_id,data_node_result_id); (yyval.graph)->addConnection(data_node_1_id,op_node_id); } }
#line 1676 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 193 "misdcompiler.ypp" /* yacc.c:1646  */
    { data_type ident_type = getIdentType(* (yyvsp[-2].str)); IR_OperationNode* op_node = buildAssignNode(ident_type); (yyval.graph) = new IR_Graph(); (yyval.graph)->addOperationNode(op_node); int op_node_id = (yyval.graph)->getLastOperationID(); IR_DataNode* data_node_result = getVariableNodeByName(* (yyvsp[-2].str)); (yyval.graph)->addDataNode(data_node_result); int data_node_result_id = (yyval.graph)->getLastDataID(); if((data_node_result_id > 0) && (op_node_id > 0)) { (yyval.graph)->addConnection(op_node_id,data_node_result_id); } int num_of_vars = exp_vars_list.size(); for(int i = 0; i < num_of_vars; i++ ) { std::string variable_name = exp_vars_list[i]; IR_DataNode* data_node_i = getVariableNodeByName(variable_name); (yyval.graph)->addDataNode(data_node_i); int data_node_i_id = (yyval.graph)->getLastDataID(); if((data_node_i_id > 0) && (op_node_id > 0)) { (yyval.graph)->addConnection(data_node_i_id,op_node_id); } } exp_vars_list.clear(); }
#line 1682 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 194 "misdcompiler.ypp" /* yacc.c:1646  */
    { data_type ident_type = getIdentType(* (yyvsp[-5].str)); IR_OperationNode* op_node = buildAssignNode(ident_type); (yyval.graph) = new IR_Graph(); (yyval.graph)->addOperationNode(op_node); int op_node_id = (yyval.graph)->getLastOperationID(); IR_DataNode* data_node_result = getVariableNodeByName(* (yyvsp[-5].str)); (yyval.graph)->addDataNode(data_node_result); int data_node_result_id = (yyval.graph)->getLastDataID(); IR_DataNode* data_node_1 = getStructureNodeByName(* (yyvsp[-2].str)); IR_DataNode* data_node_2 = getVariableNodeByName(* (yyvsp[0].str)); (yyval.graph)->addDataNode(data_node_1); int data_node_1_id = (yyval.graph)->getLastDataID(); (yyval.graph)->addDataNode(data_node_2); int data_node_2_id = (yyval.graph)->getLastDataID(); if((data_node_result_id > 0) && (op_node_id > 0) && (data_node_1_id > 0) && (data_node_2_id > 0)) { (yyval.graph)->addConnection(op_node_id,data_node_result_id); (yyval.graph)->addConnection(data_node_1_id,op_node_id); (yyval.graph)->addConnection(data_node_2_id,op_node_id); } }
#line 1688 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 205 "misdcompiler.ypp" /* yacc.c:1646  */
    { std::string ident_name(yylval.pch, 0, 1024); (yyval.str) = &ident_name; }
#line 1694 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 209 "misdcompiler.ypp" /* yacc.c:1646  */
    { std::string ident_name(yylval.pch, 0, 1024); (yyval.str) = &ident_name; }
#line 1700 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 213 "misdcompiler.ypp" /* yacc.c:1646  */
    { /* Only AST */ }
#line 1706 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 214 "misdcompiler.ypp" /* yacc.c:1646  */
    { /* Only AST */ }
#line 1712 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 215 "misdcompiler.ypp" /* yacc.c:1646  */
    { /* Only AST */ }
#line 1718 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 216 "misdcompiler.ypp" /* yacc.c:1646  */
    { /* Only AST */ }
#line 1724 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 217 "misdcompiler.ypp" /* yacc.c:1646  */
    { /* Only AST */ }
#line 1730 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 218 "misdcompiler.ypp" /* yacc.c:1646  */
    { /* Only AST */ }
#line 1736 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 219 "misdcompiler.ypp" /* yacc.c:1646  */
    { /* Only AST */ }
#line 1742 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 220 "misdcompiler.ypp" /* yacc.c:1646  */
    { /* Only AST */ }
#line 1748 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 221 "misdcompiler.ypp" /* yacc.c:1646  */
    { /* Only AST */ }
#line 1754 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 222 "misdcompiler.ypp" /* yacc.c:1646  */
    { std::string ident_name(yylval.pch, 0, 1024); exp_vars_list.push_back(ident_name); }
#line 1760 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 223 "misdcompiler.ypp" /* yacc.c:1646  */
    { /* Addition to special list and table for numbers? ???exp_vars_list??? */ }
#line 1766 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 227 "misdcompiler.ypp" /* yacc.c:1646  */
    { (yyval.graph) = new IR_Graph(); (yyval.graph)->addOperationNode( buildConditionalBeginBranchNode( ) ); int op_node_id = (yyval.graph)->getLastOperationID(); int num_of_vars = exp_vars_list.size(); for(int i = 0; i < num_of_vars; i++ ) { std::string variable_name = exp_vars_list[i]; IR_DataNode* data_node_i = getVariableNodeByName(variable_name); (yyval.graph)->addDataNode(data_node_i); int data_node_i_id = (yyval.graph)->getLastDataID(); if((data_node_i_id > 0) && (op_node_id > 0)) { (yyval.graph)->addConnection(data_node_i_id,op_node_id); } } exp_vars_list.clear(); (yyval.graph)->appendGraph((yyvsp[0].graph)); int op_last_appended = (yyvsp[0].graph)->getLastOperationID(); (yyval.graph)->addOperationNode( buildEndBranchNode( ) ); int op_end_node_id = (yyval.graph)->getLastOperationID(); (yyval.graph)->addConnection(op_node_id,op_end_node_id); (yyval.graph)->addConnection(op_last_appended,op_end_node_id); }
#line 1772 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 228 "misdcompiler.ypp" /* yacc.c:1646  */
    { (yyval.graph) = new IR_Graph(); (yyval.graph)->addOperationNode( buildConditionalBeginBranchNode( ) ); int op_node_id = (yyval.graph)->getLastOperationID(); int num_of_vars = exp_vars_list.size(); for(int i = 0; i < num_of_vars; i++ ) { std::string variable_name = exp_vars_list[i]; IR_DataNode* data_node_i = getVariableNodeByName(variable_name); (yyval.graph)->addDataNode(data_node_i); int data_node_i_id = (yyval.graph)->getLastDataID(); if((data_node_i_id > 0) && (op_node_id > 0)) { (yyval.graph)->addConnection(data_node_i_id,op_node_id); } } exp_vars_list.clear(); (yyval.graph)->appendGraph((yyvsp[-2].graph)); int op_last_appended_1 = (yyvsp[-2].graph)->getLastOperationID(); (yyval.graph)->appendGraph((yyvsp[0].graph),op_node_id); int op_last_appended_2 = (yyvsp[0].graph)->getLastOperationID(); (yyval.graph)->addOperationNode( buildEndBranchNode( ) ); int op_end_node_id = (yyval.graph)->getLastOperationID(); (yyval.graph)->addConnection(op_last_appended_1,op_end_node_id); (yyval.graph)->addConnection(op_last_appended_2,op_end_node_id); }
#line 1778 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 232 "misdcompiler.ypp" /* yacc.c:1646  */
    { /* Only AST */ }
#line 1784 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 69:
#line 249 "misdcompiler.ypp" /* yacc.c:1646  */
    { (yyval.graph) = new IR_Graph(); (yyval.graph)->appendGraph((yyvsp[-7].graph)); (yyval.graph)->addOperationNode( buildConditionalBeginBranchNode( ) ); int op_node_id = (yyval.graph)->getLastOperationID(); int num_of_vars = exp_vars_list.size(); for(int i = 0; i < num_of_vars; i++ ) { std::string variable_name = exp_vars_list[i]; IR_DataNode* data_node_i = getVariableNodeByName(variable_name); (yyval.graph)->addDataNode(data_node_i); int data_node_i_id = (yyval.graph)->getLastDataID(); if((data_node_i_id > 0) && (op_node_id > 0)) { (yyval.graph)->addConnection(data_node_i_id,op_node_id); } } exp_vars_list.clear(); int op_cnt_assign_id = (yyvsp[-7].graph)->getLastOperationID(); (yyval.graph)->addConnection(op_cnt_assign_id,op_node_id); (yyval.graph)->appendGraph((yyvsp[-3].graph)); (yyval.graph)->appendGraph((yyvsp[0].graph)); int op_last_appended = (yyvsp[0].graph)->getLastOperationID(); (yyval.graph)->addOperationNode( buildEndBranchNode( ) ); int op_end_node_id = (yyval.graph)->getLastOperationID(); (yyval.graph)->addConnection(op_last_appended,op_node_id); (yyval.graph)->addConnection(op_node_id,op_end_node_id); }
#line 1790 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;

  case 70:
#line 253 "misdcompiler.ypp" /* yacc.c:1646  */
    { (yyval.graph) = new IR_Graph(); (yyval.graph)->addOperationNode( buildConditionalBeginBranchNode( ) ); int op_node_id = (yyval.graph)->getLastOperationID(); int num_of_vars = exp_vars_list.size(); for(int i = 0; i < num_of_vars; i++ ) { std::string variable_name = exp_vars_list[i]; IR_DataNode* data_node_i = getVariableNodeByName(variable_name); (yyval.graph)->addDataNode(data_node_i); int data_node_i_id = (yyval.graph)->getLastDataID(); if((data_node_i_id > 0) && (op_node_id > 0)) { (yyval.graph)->addConnection(data_node_i_id,op_node_id); } } exp_vars_list.clear(); (yyval.graph)->appendGraph((yyvsp[0].graph)); int op_last_appended = (yyvsp[0].graph)->getLastOperationID(); (yyval.graph)->addOperationNode( buildEndBranchNode( ) ); int op_end_node_id = (yyval.graph)->getLastOperationID(); (yyval.graph)->addConnection(op_last_appended,op_node_id); (yyval.graph)->addConnection(op_node_id,op_end_node_id); }
#line 1796 "bison-misdcompiler.cpp" /* yacc.c:1646  */
    break;


#line 1800 "bison-misdcompiler.cpp" /* yacc.c:1646  */
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
  *++yylsp = yyloc;

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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

  yyerror_range[1] = yylsp[1-yylen];
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp, yylsp);
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
#line 256 "misdcompiler.ypp" /* yacc.c:1906  */

