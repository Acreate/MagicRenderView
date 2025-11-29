#ifndef STARTNODE_H_H_HEAD__FILE__
#define STARTNODE_H_H_HEAD__FILE__
#pragma once
#include "../../beginNode.h"

class StartNode : public BeginNode {
	Q_OBJECT;
public:
	StartNode( QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) )
		: BeginNode( parent, f ) { }
	bool updateLayout( ) override {
		return true;
	}
public:
	Def_Satatic_NodeTypeName( Node::tr( "起始/开始位置" ) );
};

#endif // STARTNODE_H_H_HEAD__FILE__
