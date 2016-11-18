#include "../include/StructureExpr.h"

StructureExpr::StructureExpr()
{
	name = "";
}

StructureExpr::StructureExpr(std::string a_name) {
	name = a_name;
}

StructureExpr::~StructureExpr()
{
}

void StructureExpr::setName(std::string a_name) {
	name = a_name;
}

std::string StructureExpr::getName() {
	return name;
}