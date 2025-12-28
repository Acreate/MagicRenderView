#ifndef GOTONODE_H_H_HEAD__FILE__
#define GOTONODE_H_H_HEAD__FILE__
#pragma once
#include "../../jumpNode.h"

class GotoNode : public JumpNode {
	Q_OBJECT;
public:
	GotoNode( const QString &node_name )
		: JumpNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	Def_Extend_NodeTypeName( Node::tr( "跳转/跳转位置" ) );
};

#endif // GOTONODE_H_H_HEAD__FILE__
