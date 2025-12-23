#ifndef IFNODE_H_H_HEAD__FILE__
#define IFNODE_H_H_HEAD__FILE__
#pragma once
#include "../../logicNode.h"

class IfNode : public LogicNode {
	Q_OBJECT;
public:
	IfNode( const QString &node_name )
		: LogicNode( node_name ) { }
	bool initEx( DrawNodeWidget *parent ) override;
	bool updateLayout( ) override;
public:
	Def_Satatic_NodeTypeName( Node::tr( "逻辑/分支" ) );
};

#endif // IFNODE_H_H_HEAD__FILE__
