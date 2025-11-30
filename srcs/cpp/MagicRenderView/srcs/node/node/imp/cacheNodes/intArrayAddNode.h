#ifndef INTARRAYADDNODE_H_H_HEAD__FILE__
#define INTARRAYADDNODE_H_H_HEAD__FILE__
#pragma once
#include "../../cacheNode.h"

class IntArrayAddNode : public CacheNode {
	Q_OBJECT;
public:
	IntArrayAddNode( const QString &node_name )
		: CacheNode( node_name ) { }
	bool init( DrawNodeWidget *parent, NodeRefLinkInfo *node_ref_link_info ) override;
	bool updateLayout( ) override;
public:
	Def_Satatic_NodeTypeName( Node::tr( "缓存/整数序列和" ) );
};

#endif // INTARRAYADDNODE_H_H_HEAD__FILE__
