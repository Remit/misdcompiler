%option outfile="flex-misdcompiler.cpp"
%option header-file="../include/flex-misdcompiler.h"

%option noyywrap
%option nounput

%option bison-bridge
%option bison-locations

%{
#include <iostream>
#include "../include/bison-misdcompiler.h"

static int  processIdentifier();
static int  processStructIdentifier();
static int  processStringLiteral(const char* q, int type);
%}

digit            	[0-9]
letter           	[_a-zA-Z]
ident            	{letter}({letter}|{digit})*

exponent         	[Ee][\+\-]?{digit}+
floatLiteral     	{digit}+"."{exponent}

%%
{digit}+			return NUMLITERAL;
{floatLiteral}		return NUMLITERAL;
int					return TINT;
char				return TCHAR;
long 				return TLONG;
float				return TFLOAT;
if					return TIF;
then				return TTHEN;
else				return TELSE;
while				return TWHILE;
do					return TDO;
for					return TFOR;
spu_mem				return TMEMTYPESPU;
cpu_mem				return TMEMTYPECPU;
_misdop_SEARCH_STR	return TMISDOPSEARCHSTR;
_misdop_SEARCH_SML_STR	return TMISDOPSEARCHSMLSTR;
_misdop_SEARCH_GRT_STR	return TMISDOPSEARCHGRTSTR;
_misdop_INSERT_STR	return TMISDOPINSERTSTR;
_misdop_DELETE_FROM_STR	return TMISDOPDELETEFROMSTR;
_misdop_NEXT_STR	return TMISDOPNEXTSTR;
_misdop_DELETE_STR	return TMISDOPDELETESTR;
_misdop_MAX_STR		return TMISDOPMAXSTR;
_misdop_MIN_STR		return TMISDOPMINSTR;
_misdop_POWER_STR	return TMISDOPPOWERSTR;
_misdop_UNION_STR	return TMISDOPUNIONSTR;
_misdop_INTERSECT_STR	return TMISDOPINTERSECTSTR;
_misdop_NOT_STR		return TMISDOPNOTSTR;
_misdop_GT_STR		return TMISDOPGTSTR;
_misdop_LT_STR		return TMISDOPLTSTR;
_misdop_LTE_STR		return TMISDOPLTESTR;
_misdop_GTE_STR		return TMISDOPGTESTR;
_misdop_SEND_TO_SPU	return TMISDOPSENDTOSPU;
_misdop_SEND_TO_CPU	return TMISDOPSENDTOCPU;
_misdop_RECEIVE_FROM_SPU	return TMISDOPRECEIVEFROMSPU;
_misdop_RECEIVE_FROM_CPU	return TMISDOPRECEIVEFROMCPU;
"+"					return TPLUS;
"-" 				return TMINUS;
"/"					return TDIV;
"*"					return TMUL;
"%" 				return TMOD;
AND					return TAND;
OR					return TOR;
NOT					return TNOT;
"<"					return TLT;
">"					return TGT;
"<="				return TLTE;
">="				return TGTE;
"=="				return TEQ;
","					return TCOMMA;
";"					return TSEMI;
"="					return TASSIGN;
"{"					return TLCBR;
"}"					return TRCBR;
"("					return TLP;
")"					return TRP;
STRUCT1				return processStructIdentifier(yyscanner);
STRUCT2				return processStructIdentifier(yyscanner);
STRUCT3				return processStructIdentifier(yyscanner);
STRUCT4				return processStructIdentifier(yyscanner);
STRUCT5				return processStructIdentifier(yyscanner);
STRUCT6				return processStructIdentifier(yyscanner);
STRUCT7				return processStructIdentifier(yyscanner);
{ident}				return processIdentifier(yyscanner);
"\""             	return STRINGLITERAL; //Placeholder
"\'"             	return STRINGLITERAL; //Placeholder

%%

//Identifiers processing
static int  processIdentifier() {
  YYSTYPE* yyLval = yyget_lval();//danger - possible errors?
  int      retval = TIDENT;

  yyLval->pch = yyget_text();//danger - possible errors? without astr()

  return retval;
}

//Structure identifiers processing
static int  processStructIdentifier() {
  YYSTYPE* yyLval = yyget_lval();//danger - possible errors?
  int      retval = TSTRUCTIDENT;

  yyLval->pch = yyget_text();//danger - possible errors? without astr()

  return retval;
}