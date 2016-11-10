#include "../include/Scope.h"

Scope::Scope()
{
	virtual_scope = false;
	subScopes = NULL;
	variables_in_scope = NULL;
}

Scope::~Scope()
{
	delete[] subScopes;
}

bool Scope::isVirtualScope() {
	return virtual_scope;
}

void Scope::setIsVirtualScope(bool a_virtual_scope) {
	virtual_scope = a_virtual_scope;
	return;
}

std::vector<Scope *> * Scope::getSubScopes() {
	return subScopes;
}

void Scope::addSubScope(Scope * a_subScope) {
	if(subScopes == NULL)
		subScopes = new std::vector<Scope *>;
	
	unsigned int sz = subScopes->size();
	subScopes->reserve(++sz);
	subScopes->push_back(a_subScope);
	return;
}

std::vector<std::string>* Scope::getVariablesInScope() {
	return variables_in_scope;
}

void Scope::addVariablesInScope(std::vector<std::string>* a_variables_in_scope) {
	if(variables_in_scope == NULL)
		variables_in_scope = new std::vector<std::string>;
	
	unsigned int sz = variables_in_scope->size();
	variables_in_scope->reserve(++sz);
	sz = a_variables_in_scope->size();
	std::string tmp_str;
	for(int i = 0; i < sz; i++) {
		tmp_str = (*a_variables_in_scope)[i];
		variables_in_scope->push_back(tmp_str);
	}
	
	return;
}

Scope * Scope::getScopeCopy() {
	Scope * scope_copy = new Scope();
	scope_copy->setIsVirtualScope(isVirtualScope());
	scope_copy->addVariablesInScope(getVariablesInScope());
	if(subScopes != NULL) {
		unsigned int sz = subScopes->size();
		for(unsigned int i = 0; i < sz; i++) {
			Scope * subscope_copy = (*subScopes)[i]->getScopeCopy();
			scope_copy->addSubScope(subscope_copy);
		}
	}
	
	return scope_copy;
}