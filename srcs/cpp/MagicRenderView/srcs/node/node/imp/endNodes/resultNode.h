#ifndef RESULTNODE_H_H_HEAD__FILE__
#define RESULTNODE_H_H_HEAD__FILE__
#pragma once
#include "../../endNode.h"

class ResultNode : public EndNode {
	Q_OBJECT;
public:
	ResultNode( QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) );
	bool updateLayout( ) override;
public:
	Def_Satatic_NodeTypeName( Node::tr( "结束/返回" ) );

};

#endif // RESULTNODE_H_H_HEAD__FILE__
