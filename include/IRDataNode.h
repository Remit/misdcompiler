/*
 * IRDataNode.h
 *
 *  Created on: 14.08.2016
 *      Author: remit
 */

#ifndef IRDATANODE_H_
#define IRDATANODE_H_

#ifndef IRNODE_H_
#include "IRNode.h"
#endif

class IR_DataNode: public IR_Node {
public:
	IR_DataNode();
	virtual ~IR_DataNode();

	void setDataType(data_type a_dataType);
	void setSimpleType(int a_simple_type);
	void setDataName(std::string a_name);

	data_type getDataType();
	int getSimpleType();
	std::string getDataName();

	// Visualisation
	void print();
	std::string getPicturePath();



private:
//ATTENTION: When adding a field to a node, do not forget to add code to copy method!
	// Link to a corresponding identifier in data table.
	data_type dataType;
	int simple_type;
	std::string name;
};

#endif /* IRDATANODE_H_ */
