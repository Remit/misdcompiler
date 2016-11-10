#ifndef SCOPE_H
#define SCOPE_H

#ifndef COMMON_TYPES_AND_CONSTANTS
#include "CommonTypesAndConstants.h"
#endif

class Scope
{
public:
	Scope();
	~Scope();
	
	bool isVirtualScope();
	void setIsVirtualScope(bool a_virtual_scope);
	std::vector< Scope * > * getSubScopes();
	void addSubScope(Scope * a_subScope);
	std::vector< std::string > * getVariablesInScope();
	void addVariablesInScope(std::vector< std::string > * a_variables_in_scope);
	Scope * getScopeCopy();

private:
	std::vector< Scope * > * subScopes;
	bool virtual_scope;//The scope is considered to be virtual if it is acquired as a scope on a level of sequence of stmts. Several virtual scopes constitute real scope together.
	std::vector< std::string > * variables_in_scope;
};

#endif // SCOPE_H
