#ifndef INTADDNODE_H_H_HEAD__FILE__
#define INTADDNODE_H_H_HEAD__FILE__
#pragma once
#include "../../processNode.h"

class IntAddNode : public ProcessNode {
	Q_OBJECT;
public:
	IntAddNode( const QString &node_name )
		: ProcessNode( node_name ) { }
	bool initEx( DrawNodeWidget *parent ) override;
	bool updateLayout( ) override;
public:
	Def_Satatic_NodeTypeName( Node::tr( "数值运算/整数加法" ) );
};

#endif // INTADDNODE_H_H_HEAD__FILE__
