/*
 * IRDataNode.h
 *
 *  Created on: 14.08.2016
 *      Author: remit
 */

#ifndef IRDATANODE_H_
#define IRDATANODE_H_

#include "IRNode.h"

class IR_DataNode: public IR_Node {
public:
	IR_DataNode();
	virtual ~IR_DataNode();

	void setDataType(data_type a_dataType);

	data_type getDataType();

private:
	// Link to a corresponding identifier in data table.
	data_type dataType;
};

#endif /* IRDATANODE_H_ */
