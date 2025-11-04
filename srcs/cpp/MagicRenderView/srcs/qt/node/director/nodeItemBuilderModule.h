#ifndef NODEITEMBUILDERMODULE_H_H_HEAD__FILE__
#define NODEITEMBUILDERMODULE_H_H_HEAD__FILE__
#pragma once
#include <QObject>

#include <alias/type_alias.h>

#include "../../enums/nodeItemEnum.h"

class NodeItemInfo;
class NodeItemBuilderModule : public QObject {
	Q_OBJECT;
protected:
	nodeItemEnum::Node_Item_Builder_Type moduleBuilderStaus;
	QString msg;
	std_vector< NodeItemInfo * > startNodeItemInfoVector;
	std_vector< NodeItemInfo * > runNodeItemInfoVector;
	size_t currentVectorIndex;
	size_t currentVectorCount;
	NodeItemInfo **runNodeItemInfoArrayPtr;
protected:
	NodeItemBuilderModule( ) { }
protected:
	static std_vector< NodeItemInfo * > findEndAtStartNode( NodeItemInfo *end_node_info_ptr );
public:
	static std_vector< NodeItemBuilderModule * > generateNodeItemBuilderModuleVector( const NodeItemInfo **node_item_info_array_ptr, const size_t &node_item_info_array_count );
public:
	virtual nodeItemEnum::Node_Item_Builder_Type getModuleBuilderStaus( ) const { return moduleBuilderStaus; }
	virtual const QString & getMsg( ) const { return msg; }
};

#endif // NODEITEMBUILDERMODULE_H_H_HEAD__FILE__
