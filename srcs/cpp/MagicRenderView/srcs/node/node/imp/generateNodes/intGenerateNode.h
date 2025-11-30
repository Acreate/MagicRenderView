#ifndef INTGENERATENODE_H_H_HEAD__FILE__
#define INTGENERATENODE_H_H_HEAD__FILE__
#pragma once
#include "../../generateNode.h"

class IntGenerateNode : public GenerateNode {
	Q_OBJECT;
public:
	IntGenerateNode( const QString &node_name )
		: GenerateNode( node_name ) { }
	bool updateLayout( ) override;
public:
	Def_Satatic_NodeTypeName( Node::tr( "生成/生成整数" ) );

};

#endif // INTGENERATENODE_H_H_HEAD__FILE__
