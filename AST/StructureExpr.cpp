#include "../include/StructureExpr.h"

StructureExpr::StructureExpr()
{
	name = "";
	lbl = AST_STRUCTUREEXPR;
}

StructureExpr::StructureExpr(std::string a_name) {
	name = a_name;
}

StructureExpr::~StructureExpr()
{
}

void StructureExpr::setName(std::string a_name) {
	name = a_name;
	lbl = AST_STRUCTUREEXPR;
}

std::string StructureExpr::getName() {
	return name;
}

Base_AST * StructureExpr::copyAST() {
	StructureExpr * cpy = new StructureExpr(name);
	return cpy;
}

void StructureExpr::print() {
	std::cout << "\n - Structure: " << name;
}

Value * StructureExpr::generateCode() {
	Value * ret = NULL;
	return ret;
}

std::string StructureExpr::generateStructCode() {
	std::string ret = name;
	return ret;
}