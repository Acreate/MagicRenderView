#ifndef WHILENODE_H_H_HEAD__FILE__
#define WHILENODE_H_H_HEAD__FILE__
#pragma once
#include "../node.h"

class WhileNode : public Node {
	Q_OBJECT;
public:
	WhileNode( QWidget *parent = nullptr, const Qt::WindowFlags &f = Qt::WindowFlags( ) )
		: Node( parent, f ) { }
	bool init( QWidget *parent ) override;
	bool updateLayout( ) override;
	Def_Satatic_NodeTypeName( Node::tr( "逻辑/循环" ) );
};

#endif // WHILENODE_H_H_HEAD__FILE__
