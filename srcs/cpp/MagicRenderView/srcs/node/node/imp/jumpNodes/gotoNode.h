#ifndef GOTONODE_H_H_HEAD__FILE__
#define GOTONODE_H_H_HEAD__FILE__
#pragma once
#include "../../jumpNode.h"

class GotoNode : public JumpNode{
	Q_OBJECT;
public:
	GotoNode( QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) )
		: JumpNode( parent, f ) { }
	bool updateLayout( ) override {
		return true;
	}
public:
	Def_Satatic_NodeTypeName( Node::tr( "跳转/跳转位置" ) );
};

#endif // GOTONODE_H_H_HEAD__FILE__
