/*
 * BaseAST.cpp
 *
 *  Created on: 14.08.2016
 *      Author: remit
 */

#include "../include/BaseAST.h"

Base_AST::Base_AST() {
	lbl = AST_BASE;
}

Base_AST::~Base_AST() {
	// TODO Auto-generated destructor stub
}

void Base_AST::print() {
	std::cout << "BASE" << std::endl;
}

void Base_AST::setASTLabel(ast_label a_lbl) {
	lbl = a_lbl;
}

ast_label Base_AST::getASTLabel() {
	return lbl;
}

Base_AST * Base_AST::copyAST() {
	return NULL;
}