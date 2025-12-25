#ifndef RESULTNODE_H_H_HEAD__FILE__
#define RESULTNODE_H_H_HEAD__FILE__
#pragma once
#include "../../endNode.h"

class ResultNode : public EndNode {
	Q_OBJECT;
public:
	ResultNode( const QString &node_name )
		: EndNode( node_name ) { }
	bool initEx( MainWidget *parent ) override;
	bool updateLayout( ) override;
public:
	Def_Satatic_NodeTypeName( Node::tr( "结束/返回" ) );

};

#endif // RESULTNODE_H_H_HEAD__FILE__
