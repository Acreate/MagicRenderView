#ifndef MAKENODE_H_H_HEAD__FILE__
#define MAKENODE_H_H_HEAD__FILE__
#pragma once
#include "../../pointNode.h"

class MakeNode : public PointNode {
	Q_OBJECT;
public:
	MakeNode( QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) )
		: PointNode( parent, f ) { }
	bool updateLayout( ) override {
		return true;
	}
public:
	Def_Satatic_NodeTypeName( Node::tr( "跳转/记录位置" ) );
};

#endif // MAKENODE_H_H_HEAD__FILE__
