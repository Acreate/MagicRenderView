#ifndef INTARRAYADDNODE_H_H_HEAD__FILE__
#define INTARRAYADDNODE_H_H_HEAD__FILE__
#pragma once
#include "../../cacheNode.h"

class IntArrayAddNode : public CacheNode {
	Q_OBJECT;
public:
	IntArrayAddNode( const QString &node_name )
		: CacheNode( node_name ) { }
	bool updateLayout( ) override;
public:
	Def_Satatic_NodeTypeName( Node::tr( "数组/整数缓存序列" ) );
};

#endif // INTARRAYADDNODE_H_H_HEAD__FILE__
