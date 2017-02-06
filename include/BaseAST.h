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
#include "/usr/include/llvm/IR/DerivedTypes.h"
#include "/usr/include/llvm/IR/LLVMContext.h"
#include "/usr/include/llvm/IR/Module.h"
#include "/usr/include/llvm/IR/Verifier.h"
#include "/usr/include/llvm/IR/IRBuilder.h"
using namespace llvm;

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

static LLVMContext GlobalContext;
static IRBuilder<> Builder(GlobalContext);
static std::unique_ptr<Module> GlobalModule;
static std::map<std::string, AllocaInst *> NamedValues;

class Base_AST {
public:
	Base_AST();
	virtual ~Base_AST();
	virtual void print();
	void setASTLabel(ast_label a_lbl);
	ast_label getASTLabel();
	virtual Base_AST * copyAST();
	virtual Value *generateCode() = 0;

protected:
	ast_label lbl;

};

#endif /* BASEAST_H_ */
