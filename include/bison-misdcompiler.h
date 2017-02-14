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
#line 1 "misdcompiler.ypp" /* yacc.c:1909  */

    
 struct YYLTYPE {
    int         first_line;
    int         first_column;
    int         last_line;
    int         last_column;
    const char* comment;
  };

  #define YYLTYPE_IS_DECLARED 1
  #define YYLTYPE_IS_TRIVIAL  1
#line 20 "misdcompiler.ypp" /* yacc.c:1909  */

 #include <stdio.h>
 #include <string.h>
 #include <vector>
 #include <iostream>
 
 #include "../include/Algorithm.h"
 
 #ifndef BUILD_H_
 #include "../include/build.h"
 #endif
 
 #ifndef IRGRAPH_H_
 #include "../include/IRGraph.h"
 #endif
 
 #ifndef BASEAST_H_
 #include "../include/BaseAST.h"
 #endif
 
 extern int yylineno; 
 
 static
 void yyerror(YYLTYPE* yyloc, IR_Graph& gr, char *s)
 {
        std::cerr << s << " at line " << yylineno << '\n';
 }
 

#line 87 "../include/bison-misdcompiler.h" /* yacc.c:1909  */

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
    TDOUBLE = 263,
    TLONG = 264,
    TFLOAT = 265,
    TBOOL = 266,
    TIF = 267,
    TTHEN = 268,
    TELSE = 269,
    TWHILE = 270,
    TDO = 271,
    TFOR = 272,
    TTRUE = 273,
    TFALSE = 274,
    TMEMTYPESPU = 275,
    TMEMTYPECPU = 276,
    TMISDOPSEARCHSTR = 277,
    TMISDOPSEARCHSMLSTR = 278,
    TMISDOPSEARCHGRTSTR = 279,
    TMISDOPINSERTSTR = 280,
    TMISDOPDELETEFROMSTR = 281,
    TMISDOPNEXTSTR = 282,
    TMISDOPDELETESTR = 283,
    TMISDOPMAXSTR = 284,
    TMISDOPMINSTR = 285,
    TMISDOPPOWERSTR = 286,
    TMISDOPUNIONSTR = 287,
    TMISDOPINTERSECTSTR = 288,
    TMISDOPNOTSTR = 289,
    TMISDOPGTSTR = 290,
    TMISDOPLTSTR = 291,
    TMISDOPLTESTR = 292,
    TMISDOPGTESTR = 293,
    TMISDOPSENDTOSPU = 294,
    TMISDOPSENDTOCPU = 295,
    TMISDOPRECEIVEFROMSPU = 296,
    TMISDOPRECEIVEFROMCPU = 297,
    TPLUS = 298,
    TMINUS = 299,
    TDIV = 300,
    TMUL = 301,
    TMOD = 302,
    TAND = 303,
    TOR = 304,
    TNOT = 305,
    TLT = 306,
    TGT = 307,
    TLTE = 308,
    TGTE = 309,
    TEQ = 310,
    TCOMMA = 311,
    TSEMI = 312,
    TASSIGN = 313,
    TLCBR = 314,
    TRCBR = 315,
    TLP = 316,
    TRP = 317,
    TNOELSE = 318
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 71 "misdcompiler.ypp" /* yacc.c:1909  */
	
 const char* pch;
 
 IR_Graph* graph;
 proc_type ptype;
 int type_int;
 double numerical;
 std::string* str;
 variable_type tov;
 Base_AST * ast;
 LogicalExpression * logic;
 cond_op_types cond;
 structures_proc_op_types struct_op;

#line 178 "../include/bison-misdcompiler.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
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



int yyparse (IR_Graph& gr);

#endif /* !YY_YY_INCLUDE_BISON_MISDCOMPILER_H_INCLUDED  */
