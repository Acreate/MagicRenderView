#ifndef INTARRAYADDNODE_H_H_HEAD__FILE__
#define INTARRAYADDNODE_H_H_HEAD__FILE__
#pragma once
#include "../../arrayNode.h"
#include "../../cacheNode.h"

class IntArrayAddNode : public ArrayNode {
	Q_OBJECT;
public:
	IntArrayAddNode( const QString &node_name )
		: ArrayNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	Def_Satatic_NodeTypeName( Node::tr( "缓存/整数序列和" ) );
};

#endif // INTARRAYADDNODE_H_H_HEAD__FILE__
