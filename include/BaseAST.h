/*
 * BaseAST.h
 *
 *  Created on: 14.08.2016
 *      Author: remit
 */
#ifndef BASEAST_H_
#define BASEAST_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

#ifndef CODEGENERATION_H_
#include "CodeGeneration.h"
#endif

class Base_AST {
public:
	Base_AST();
	virtual ~Base_AST();
	virtual void print(std::ostream * print_stream);
	void setASTLabel(ast_label a_lbl);
	ast_label getASTLabel();
	virtual Base_AST * copyAST();
	virtual Value *generateCode() = 0;
	virtual std::string generateStructCode() = 0;

protected:
	ast_label lbl;

};

#endif /* BASEAST_H_ */
