#ifndef MAKENODE_H_H_HEAD__FILE__
#define MAKENODE_H_H_HEAD__FILE__
#pragma once
#include "../../pointNode.h"

class MakeNode : public PointNode {
	Q_OBJECT;
public:
	MakeNode( const QString &node_name )
		: PointNode( node_name ) { }
	bool updateLayout( ) override;
	bool init(DrawNodeWidget *parent, NodeRefLinkInfo *node_ref_link_info) override;
public:
	Def_Satatic_NodeTypeName( Node::tr( "记录/记录位置" ) );
};

#endif // MAKENODE_H_H_HEAD__FILE__
