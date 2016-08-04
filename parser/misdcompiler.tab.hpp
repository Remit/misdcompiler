/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison interface for Yacc-like parsers in C

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
#line 7 "misdcompiler.ypp" /* yacc.c:1909  */

  #ifndef _BISON_MISDCOMPILER_DEFINES_0_
  #define _BISON_MISDCOMPILER_DEFINES_0_

  #define YYLEX_NEWLINE                  -1
  #define YYLEX_SINGLE_LINE_COMMENT      -2
  #define YYLEX_BLOCK_COMMENT            -3

  typedef void* yyscan_t;

  //int processNewline(yyscan_t scanner);
  //void stringBufferInit();

  #endif
#line 23 "misdcompiler.ypp" /* yacc.c:1909  */

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

#line 73 "misdcompiler.tab.hpp" /* yacc.c:1909  */

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
