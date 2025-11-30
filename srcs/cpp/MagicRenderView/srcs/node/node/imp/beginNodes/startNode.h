#ifndef STARTNODE_H_H_HEAD__FILE__
#define STARTNODE_H_H_HEAD__FILE__
#pragma once
#include "../../beginNode.h"

class StartNode : public BeginNode {
	Q_OBJECT;
public:
	StartNode( const QString &node_name )
		: BeginNode( node_name ) { }
	bool init( DrawNodeWidget *parent, NodeRefLinkInfo *node_ref_link_info ) override;
	bool updateLayout( ) override;
public:
	Def_Satatic_NodeTypeName( Node::tr( "起始/开始" ) );
};

#endif // STARTNODE_H_H_HEAD__FILE__
